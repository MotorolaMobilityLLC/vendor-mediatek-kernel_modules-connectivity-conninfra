// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2024 MediaTek Inc.
 */

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/math64.h>
#include <linux/of.h>
#include <linux/types.h>
#include <linux/pm_runtime.h>

#include "osal.h"
#include "conninfra_conf.h"
#include "connv3_hw.h"
#include "connv3_clock_mng.h"
#include "connv3_mt6687_reg_def.h"
#include "coredump/connv3_dump_mng.h"


/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define PLATFORM_SOC_CHIP		0x6993
#define CONN_HW_VER			0x6653
#define CONN_ADIE_ID			0x6653

#define MT6653_PLAT_CUSTOM_DATA_SIZE	4

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
extern struct platform_device *g_connv3_pdev;
extern int connv3_plt_pinctrl_is_dfd_pin_init_done_mt6993(void);

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
static u32 g_custom_data_size = 0;
static u8 g_custom_param[MT6653_PLAT_CUSTOM_DATA_SIZE] = {0};
static struct connv3_dev_cb* g_dev_cb;
static bool g_is_co_clock = false;
/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

u32 connv3_soc_get_chipid_mt6993(void);
static u32 connv3_get_adie_chipid_mt6993(void);
static u32 connv3_reset_type_support_mt6993(void);
static u8* connv3_get_custom_option_mt6993(u32 *size);
static u32 connv3_clk_init_mt6993(
	struct platform_device *pdev,
	struct connv3_dev_cb *dev_cb);
static u32 connv3_check_clock_status_mt6993(void);
static u32 connv3_dump_exception_filter(char*);

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

struct connv3_platform_clock_ops g_connv3_clock_ops_mt6993 = {
	.clk_initial_setting = connv3_clk_init_mt6993,
};

struct connv3_hw_ops_struct g_connv3_hw_ops_mt6993 = {
	.connsys_plt_get_chipid = connv3_soc_get_chipid_mt6993,
	.connsys_plt_get_adie_chipid = connv3_get_adie_chipid_mt6993,
	.connsys_plt_reset_type_support = connv3_reset_type_support_mt6993,
	.connsys_plt_get_custom_option = connv3_get_custom_option_mt6993,
	.connsys_plt_check_status = connv3_check_clock_status_mt6993,
};

const struct connv3_coredump_platform_ops g_connv3_dump_ops_mt6993 = {
	.connv3_dump_plt_get_chipid = connv3_get_adie_chipid_mt6993,
	.connv3_dump_plt_exception_filter = connv3_dump_exception_filter,
};

extern struct connv3_hw_ops_struct g_consys_hw_ops_mt6993;
extern struct connv3_platform_pmic_ops g_connv3_platform_pmic_ops_mt6993;
extern struct connv3_platform_pinctrl_ops g_connv3_platform_pinctrl_ops_mt6993;
extern const struct connv3_platform_dbg_ops g_connv3_hw_dbg_mt6653;

const struct connv3_plat_data g_connv3_mt6993_plat_data = {
	.chip_id = PLATFORM_SOC_CHIP,
	.consys_hw_version = CONN_HW_VER,
	.hw_ops = &g_connv3_hw_ops_mt6993,
	.platform_pmic_ops = &g_connv3_platform_pmic_ops_mt6993,
	.platform_pinctrl_ops = &g_connv3_platform_pinctrl_ops_mt6993,
	.platform_coredump_ops = &g_connv3_dump_ops_mt6993,
	.platform_clock_ops = &g_connv3_clock_ops_mt6993,
};


u32 connv3_soc_get_chipid_mt6993(void)
{
	return PLATFORM_SOC_CHIP;
}

u32 connv3_get_adie_chipid_mt6993(void)
{
	return CONN_ADIE_ID;
}

static u32 connv3_reset_type_support_mt6993(void)
{
	return connv3_plt_pinctrl_is_dfd_pin_init_done_mt6993();
}

static u32 connv3_dump_exception_filter(char *exp_log)
{
	int match_idx;

	match_idx = conninfra_conf_exp_filter_check(exp_log);

	if (match_idx >= 0) {
		pr_info("[%s] exp_log = %s, match_idx = %d\n", __func__, exp_log, match_idx);
		return 1;
	}

	return 0;
}

static u32 connv3_clk_init_mt6993(
	struct platform_device *pdev,
	struct connv3_dev_cb *dev_cb)
{
	u32 ret;
	u32 value;
	struct regmap *map = connv3_clock_mng_get_regmap();
	u32 reg0 = 0, reg1 = 0;
	u32 dump1 = 0, dump2 = 0, dump3 = 0, dump4 = 0;

	g_dev_cb = dev_cb;
	ret = of_property_read_u32(pdev->dev.of_node, "co-clock", &value);
	if (ret)
		pr_notice("[%s] read co_clock prop fail\n", __func__);
	else
		g_is_co_clock = (bool)value;
	pr_info("[%s] g_is_co_clock=%d\n", __func__, value);

	/* MT6688 initial setting is done by SW PIC in preloader */
	/* Do mt6687 init flow: use GPIO_VIO_0 to control RFCK1A
	 * 1. RFCK1A bind with ext_req_2
	 * - 0x1cb=0x4
	 * 2. Enable ext_req_2
	 * - 0x1f8=0xb
	 * 3. RFCK1A with RC mode
	 * - 0x7cc[2:0]=0x5
	 * 4. Switch GPIO_VIO_0 to AUX3: EXT_CLK_REQ2
	 * - 0x98=0x3
	 */
	if (map == NULL) {
		pr_notice("[%s] map is null!\n", __func__);
		return ENODEV;
	}

	regmap_read(map, 0x0, &reg0);
	regmap_read(map, 0x1, &reg1);

	pr_info("[%s] Clock info: [0x%x, 0x%x]\n", __func__, reg0, reg1);
	regmap_write(map, MT6687_REG_TOP_XO_BUF_CTL6_4_ADDR, 0x4);
	regmap_write(map, MT6687_REG_PMRC_EXT_REQ_MASK_ADDR, 0xb);
	regmap_update_bits(map, MT6687_REG_DCXO_RFCK1A_ELR_CW0_ADDR, 0x7, 0x5);

	/* Unlock for writting MT6687_REG_GPIO_MODE0_ADDR */
	regmap_write(map, 0x3a9, 0x87);
	regmap_write(map, 0x3aa, 0x66);
	/* Use set/clr for MT6687_REG_GPIO_MODE0_ADDR[3:0] = 0x3 */
	regmap_write(map, MT6687_REG_GPIO_MODE0_CLR, 0xf);
	regmap_write(map, MT6687_REG_GPIO_MODE0_SET, 0x3);
	/* Lock back */
	regmap_write(map, 0x3a9, 0x0);
	regmap_write(map, 0x3aa, 0x0);

	regmap_read(map, MT6687_REG_TOP_XO_BUF_CTL6_4_ADDR, &dump1);
	regmap_read(map, MT6687_REG_PMRC_EXT_REQ_MASK_ADDR, &dump2);
	regmap_read(map, MT6687_REG_DCXO_RFCK1A_ELR_CW0_ADDR, &dump3);
	regmap_read(map, MT6687_REG_GPIO_MODE0_ADDR, &dump4);
	pr_info("[%s] [0x%x, 0x%x, 0x%x, 0x%x]\n", __func__, dump1, dump2, dump3, dump4);

	return 0;
}

u32 connv3_check_clock_status_mt6993(void)
{
	return 0;
}

u8* connv3_get_custom_option_mt6993(u32 *size)
{
	static bool is_init = false;
	static u16 ext_32K_ticks = 32500;
	static u16 pmic_enable_pmic = 0; /* control PMIC_EN1 */
	static u16 pmic_uvlo_level = 0; /* 0: skip, 1: 2.0V, 2: 2.1V, 3: 2.2V*/

	u32 value;
	int ret;

	if (!is_init) {
		ret = of_property_read_u32(g_connv3_pdev->dev.of_node, "ext-32k-ticks", &value);
		if (ret)
			pr_notice("[%s] read co_clock prop fail\n", __func__);
		else
			ext_32K_ticks = (u16)value;

		ret = of_property_read_u32(g_connv3_pdev->dev.of_node, "poweroffble-ap-enable-pmic", &value);
		if (ret)
			pr_notice("[%s] Default: connsys ic control PMIC_EN1\n", __func__);
		else
			pmic_enable_pmic = (u16)value;

		ret = of_property_read_u32(g_connv3_pdev->dev.of_node, "pmic-uvlo-level", &value);
		if (ret)
			pr_notice("[%s] use default PMIC UVLO level\n", __func__);
		else
			pmic_uvlo_level = (u16)value;

		/* Copy data to array */
		memcpy(g_custom_param, &ext_32K_ticks, 2);
		g_custom_param[2] = g_is_co_clock;
		/* g_custom_param[2] bit[1] */
		if (pmic_enable_pmic)
			g_custom_param[2] |= 0x02;
		/* g_custom_param[2] bit[2:3] */
		if (pmic_uvlo_level)
			g_custom_param[2] |= ((pmic_uvlo_level & 0x3) << 2);
		g_custom_data_size = MT6653_PLAT_CUSTOM_DATA_SIZE; /* one byte as reserved. */

		is_init = true;
	}

	if (size == NULL) {
		pr_notice("[%s] input error, size == NULL\n", __func__);
		return NULL;
	}

	*size = g_custom_data_size;
	pr_info("[%s] data size = %d data=[0x%x 0x%x 0x%x 0x%x]\n",
		__func__, *size,
		g_custom_param[0], g_custom_param[1], g_custom_param[2], g_custom_param[3]);
	return g_custom_param;
}
