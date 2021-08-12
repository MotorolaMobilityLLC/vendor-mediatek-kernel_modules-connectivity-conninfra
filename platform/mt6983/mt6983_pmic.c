// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <connectivity_build_in_adapter.h>
#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/timer.h>
#include "osal.h"
#include "consys_hw.h"
#include "consys_reg_util.h"
#include "pmic_mng.h"
#include <linux/regmap.h>
#include "mt6983_pmic.h"
#include "mt6983_consys_reg_offset.h"
#include "mt6983_pos.h"

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
static struct regulator *reg_VCN13;
static struct regulator *reg_VRFIO18; /* MT6363 workaround VCN15 -> VRFIO18 */

static struct regulator *reg_VCN33_1;
static struct regulator *reg_VCN33_2;
static struct regulator *reg_VANT18;

static struct regulator *reg_buckboost;

static struct notifier_block vcn13_nb;

static struct conninfra_dev_cb* g_dev_cb;

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static int consys_plt_pmic_get_from_dts_mt6983(struct platform_device*, struct conninfra_dev_cb*);

static int consys_plt_pmic_common_power_ctrl_mt6983(unsigned int);
static int consys_plt_pmic_common_power_low_power_mode_mt6983(unsigned int);
static int consys_plt_pmic_wifi_power_ctrl_mt6983(unsigned int);
static int consys_plt_pmic_bt_power_ctrl_mt6983(unsigned int);
static int consys_plt_pmic_gps_power_ctrl_mt6983(unsigned int);
static int consys_plt_pmic_fm_power_ctrl_mt6983(unsigned int);
static int consys_pmic_vcn33_1_power_ctl_mt6983_lg(bool);
static int consys_pmic_vcn33_1_power_ctl_mt6983_rc(bool);
static int consys_pmic_vcn33_2_power_ctl_mt6983_lg(bool);
static int consys_pmic_vcn33_2_power_ctl_mt6983_rc(bool);
static int consys_pmic_vant18_power_ctl_mt6983(bool);

#if 0
static int consys_plt_pmic_raise_voltage_mt6983(unsigned int, bool, bool);
static void consys_plt_pmic_raise_voltage_timer_handler_mt6983(timer_handler_arg);
#endif

static int consys_vcn13_oc_notify(struct notifier_block*, unsigned long, void*);
static int consys_plt_pmic_event_notifier_mt6983(unsigned int, unsigned int);

const struct consys_platform_pmic_ops g_consys_platform_pmic_ops_mt6983 = {
	.consys_pmic_get_from_dts = consys_plt_pmic_get_from_dts_mt6983,
	.consys_pmic_common_power_ctrl = consys_plt_pmic_common_power_ctrl_mt6983,
	.consys_pmic_common_power_low_power_mode = consys_plt_pmic_common_power_low_power_mode_mt6983,
	.consys_pmic_wifi_power_ctrl = consys_plt_pmic_wifi_power_ctrl_mt6983,
	.consys_pmic_bt_power_ctrl = consys_plt_pmic_bt_power_ctrl_mt6983,
	.consys_pmic_gps_power_ctrl = consys_plt_pmic_gps_power_ctrl_mt6983,
	.consys_pmic_fm_power_ctrl = consys_plt_pmic_fm_power_ctrl_mt6983,
#if 0
	.consys_pmic_raise_voltage = consys_plt_pmic_raise_voltage_mt6983,
#endif
	.consys_pmic_event_notifier = consys_plt_pmic_event_notifier_mt6983,
};

int consys_plt_pmic_get_from_dts_mt6983(struct platform_device *pdev, struct conninfra_dev_cb* dev_cb)
{
	int ret;

	g_dev_cb = dev_cb;
	reg_VCN13 = devm_regulator_get_optional(&pdev->dev, "mt6363_vcn13");
	if (IS_ERR(reg_VCN13)) { 
		pr_err("Regulator_get VCN_13 fail\n");
		reg_VCN13 = NULL;
	}
	else {
		vcn13_nb.notifier_call = consys_vcn13_oc_notify;
		ret = devm_regulator_register_notifier(reg_VCN13, &vcn13_nb);
		if (ret)
			pr_info("VCN13 regulator notifier request failed\n");
	}

	reg_VRFIO18 = devm_regulator_get(&pdev->dev, "mt6363_vrfio18");
	if (IS_ERR(reg_VRFIO18)) {
		pr_err("Regulator_get VCN_18 fail\n");
		reg_VRFIO18 = NULL;
	}
	reg_VCN33_1 = devm_regulator_get(&pdev->dev, "mt6373_vcn33_1");
	if (IS_ERR(reg_VCN33_1)) {
		pr_err("Regulator_get VCN33_1 fail\n");
		reg_VCN33_1 = NULL;
	}
	reg_VCN33_2 = devm_regulator_get(&pdev->dev, "mt6373_vcn33_2");
	if (IS_ERR(reg_VCN33_2)) {
		pr_err("Regulator_get VCN33_2 fail\n");
		reg_VCN33_2 = NULL;
	}
	reg_VANT18 = devm_regulator_get(&pdev->dev, "mt6373_vant18");
	if (IS_ERR(reg_VANT18)) {
		pr_err("Regulator_get VANT18 fail\n");
		reg_VANT18 = NULL;
	}
	reg_buckboost = devm_regulator_get_optional(&pdev->dev, "rt6160-buckboost");
	if (IS_ERR(reg_buckboost)) {
		pr_info("Regulator_get buckboost fail\n");
		reg_buckboost = NULL;
	}

	return 0;
}

int consys_plt_pmic_common_power_ctrl_mt6983(unsigned int enable)
{
#ifdef CONFIG_FPGA_EARLY_PORTING
	pr_info("[%s] not support on FPGA", __func__);
#else
	int ret;
	int sleep_mode;

	if (enable) {
		/* set PMIC VRFIO18 LDO 1.7V */
		regulator_set_voltage(reg_VRFIO18, 1700000, 1700000);
		/* set PMIC VRFIO18 LDO SW_OP_EN = 1, SW_EN = 1, SW_LP = 0 (SW ON) */
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL); /* SW_LP = 0 */
		ret = regulator_enable(reg_VRFIO18); /* SW_EN = 1 */
		if (ret)
			pr_err("Enable VRFIO18 fail. ret=%d\n", ret);

		/* set PMIC VCN13 LDO 1.35V @Normal mode; 0.95V @LPM */
		/* no need for LPM because 0.95V is default setting. */
		regulator_set_voltage(reg_VCN13, 1350000, 1350000);
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL); /* SW_LP = 0 */
		ret = regulator_enable(reg_VCN13); /* SW_EN = 1 */
		if (ret)
			pr_err("Enable VCN13 fail. ret=%d\n", ret);
	} else {
		/* vant18 is enabled in consys_plt_pmic_common_power_low_power_mode_mt6983 */
		/* Please refer to POS for more information */
		consys_pmic_vant18_power_ctl_mt6983(0);

		/* Add 1ms sleep to delay make sure that VCN13/18 would be turned off later then VCN33. */
		msleep(1);
		/* set PMIC VCN13 LDO SW_EN = 0, SW_LP =0 (sw disable) */
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL);
		regulator_disable(reg_VCN13);
		/* set PMIC VRFIO18 LDO SW_EN = 0, SW_LP =0 (sw disable) */
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL);
		sleep_mode = consys_get_sleep_mode_mt6983();
		if (sleep_mode == 1)
			regulator_disable(reg_VRFIO18);

		/* Set buckboost to 3.45V (for VCN33_1 & VCN33_2) */
		if (reg_buckboost) {
			regulator_set_voltage(reg_buckboost, 3450000, 3450000);
			pr_info("Set buckboost to 3.45V\n");
		}
	}
#endif
	return 0;
}

static void consys_pmic_regmap_set_value(struct regmap *rmap, unsigned int address,
						unsigned int mask, unsigned int value)
{
	int old_value = 0;
	int new_value = 0;

	if (!rmap) {
		pr_err("%s regmap is NULL\n", __func__);
		return;
	}

	regmap_read(rmap, address, &old_value);
	new_value = (old_value & ~mask) | value;
	regmap_write(rmap, address, new_value);
}

int consys_plt_pmic_common_power_low_power_mode_mt6983(unsigned int enable)
{
#ifdef CONFIG_FPGA_EARLY_PORTING
	pr_info("[%s] not support on FPGA", __func__);
#else
	int sleep_mode;
	struct regmap *r = g_regmap_mt6363;

	if (!enable)
		return 0;

	/* Set buckboost to 3.65V (for VCN33_1 & VCN33_2) */
	/* Notice that buckboost might not be enabled. */
	if (reg_buckboost) {
		regulator_set_voltage(reg_buckboost, 3650000, 3650000);
		pr_info("Set buckboost to 3.65V\n");
	}

	if (consys_is_rc_mode_enable_mt6983()) {
		/* 1. set PMIC VRFIO18 LDO PMIC HW mode control by PMRC_EN[9][8][7][6] */
		/* 1.1. set PMIC VRFIO18 LDO op_mode = 0 */
		/* 1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC9_OP_MODE_ADDR, 1 << 1, 0 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC9_OP_EN_ADDR,   1 << 1, 1 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC9_OP_CFG_ADDR,  1 << 1, 0 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC6_OP_MODE_ADDR, 1 << 6, 0 << 6);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC6_OP_EN_ADDR,   1 << 6, 1 << 6);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_RC6_OP_CFG_ADDR,  1 << 6, 0 << 6);

		sleep_mode = consys_get_sleep_mode_mt6983();
		if (sleep_mode == 1) {
			/* set PMIC VRFIO18 LDO SW_EN = 1, SW_LP =1 */
			regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_IDLE);
		} else {
			/* set PMIC VRFIO18 LDO SW_EN = 0, SW_LP =0 */
			regulator_disable(reg_VRFIO18);
			regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL); /* SW_LP = 0 */
		}

		/* 1. set PMIC VCN13 LDO PMIC HW mode control by PMRC_EN[9][8][7][6] */
		/* 1.1. set PMIC VCN13 LDO op_mode = 0 */
		/* 1.2. set PMIC VCN13 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC9_OP_MODE_ADDR, 1 << 1, 0 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC9_OP_EN_ADDR,   1 << 1, 1 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC9_OP_CFG_ADDR,  1 << 1, 0 << 1);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC6_OP_MODE_ADDR, 1 << 6, 0 << 6);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC6_OP_EN_ADDR,   1 << 6, 1 << 6);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_RC6_OP_CFG_ADDR,  1 << 6, 0 << 6);

		/* 2. set PMIC VCN13 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =1 */
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_IDLE);
	} else {
		/* 1. set PMIC VRFIO18 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VRFIO18 LDO op_mode = 1 */ 
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);

		/*  if (A-die sleep mode-2 ){ */
		/*    1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		/*  }else{ //A-die sleep mode-1 */
		/*    1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 1 */
		sleep_mode = consys_get_sleep_mode_mt6983();
		if (sleep_mode == 2) {
			consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
			consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 0 << 0);
		} else {
			consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
			consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 1 << 0);
		}

		/* 2. set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL); /* SW_LP = 0 */

		/* 1. set PMIC VCN13 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VCN13 LDO op_mode = 1 */
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VCN13_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);

		/* 1.2. set PMIC VCN13 LDO HW_OP_EN = 1, HW_OP_CFG = 1 */
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 1 << 0);

		/* 2. set PMIC VCN13 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL); /* SW_LP = 0 */
	}

	if (consys_is_rc_mode_enable_mt6983()) {
		consys_pmic_vcn33_1_power_ctl_mt6983_rc(enable);
		consys_pmic_vcn33_2_power_ctl_mt6983_rc(enable);
	}
	consys_pmic_vant18_power_ctl_mt6983(enable);
#endif
	return 0;
}

int consys_plt_pmic_wifi_power_ctrl_mt6983(unsigned int enable)
{
	int ret;

	/* necessary in legacy mode only */
	if (consys_is_rc_mode_enable_mt6983())
		return 0;

	ret = consys_pmic_vcn33_1_power_ctl_mt6983_lg(enable);
	if (ret)
		pr_info("%s VCN33_1 fail\n", (enable? "Enable" : "Disable"));

	ret = consys_pmic_vcn33_2_power_ctl_mt6983_lg(enable);
	if (ret)
		pr_info("%s VCN33_2 fail\n", (enable? "Enable" : "Disable"));

	return ret;
}

int consys_plt_pmic_bt_power_ctrl_mt6983(unsigned int enable)
{
	/* necessary in legacy mode only */
	if (consys_is_rc_mode_enable_mt6983())
		return 0;
	return consys_pmic_vcn33_1_power_ctl_mt6983_lg(enable);
}

int consys_plt_pmic_gps_power_ctrl_mt6983(unsigned int enable)
{
	return 0;
}

int consys_plt_pmic_fm_power_ctrl_mt6983(unsigned int enable)
{
	return 0;
}

static int consys_pmic_vcn33_1_power_ctl_mt6983_rc(bool enable)
{
	struct regmap *r = g_regmap_mt6373;

	if (!enable)
		return 0;

	/* 1. set PMIC VCN33_1 LDO PMIC HW mode control by PMRC_EN[8][7] */
	/* 1.1. set PMIC VCN33_1 LDO op_mode = 0 */
	/* 1.2. set PMIC VCN33_1 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);

	/* 2. set PMIC VCN33_1 LDO SW_EN = 0, SW_LP =0 (sw disable) */
	regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);

	return 0;
}

static int consys_pmic_vcn33_1_power_ctl_mt6983_lg(bool enable)
{
	struct regmap *r = g_regmap_mt6373;
	static int enable_count = 0;


	/* In legacy mode, VCN33_1 should be turned on either WIFI or BT is on */
	/* we use a counter to record the usage. */
	if (enable)
		enable_count++;
	else
		enable_count--;

	pr_info("%s enable_count %d\n", __func__, enable_count);
	if (enable_count < 0 || enable_count > 2) {
		pr_info("enable_count %d is unexpected!!!\n", enable_count);
		return 0;
	}

	if (enable_count == 0) {
		regulator_disable(reg_VCN33_1);
		return 0;
	}

	/* vcn33_1 is already on in these two cases */
	if (enable_count == 2 || (enable_count == 1 && enable == 0))
		return 0;

	/* !!! Notice that following steps will be executed only when enable_count == 1 !!!*/
	/* 1. set PMIC VCN33_1 LDO PMIC HW mode control by SRCCLKENA0 */
	/* 1.1. set PMIC VCN33_1 LDO op_mode = 1 */
	/* 1.2. set PMIC VCN33_1 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_1_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

	/* 2. set PMIC VCN33_1 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
	regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);
	regulator_enable(reg_VCN33_1);

	return 0;
}


static int consys_pmic_vcn33_2_power_ctl_mt6983_lg(bool enable)
{
	struct regmap *r = g_regmap_mt6373;

	if (!enable)
		regulator_disable(reg_VCN33_2);
	else {
		/* 1. set PMIC VCN33_2 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VCN33_2 LDO op_mode = 1 */
		/* 1.2. set PMIC VCN33_2 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

		/* 2. set PMIC VCN33_2 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);
		regulator_enable(reg_VCN33_2);
	}
	return 0;
}

static int consys_pmic_vcn33_2_power_ctl_mt6983_rc(bool enable)
{
	struct regmap *r = g_regmap_mt6373;

	if (!enable)
		return 0;

	/* 1. set PMIC VCN33_2 LDO PMIC HW mode control by PMRC_EN[8] */
	/* 1.1. set PMIC VCN33_2 LDO op_mode = 0 */
	/* 1.2. set PMIC VCN33_2 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
	consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VCN33_2_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);

	/* 2. set PMIC VCN33_2 LDO SW_EN = 0, SW_LP =0 (sw disable) */
	regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);

	return 0;
}

static int consys_pmic_vant18_power_ctl_mt6983(bool enable)
{
	struct regmap *r = g_regmap_mt6373;

	if (!enable) {
		/* 1. VANT18 will be set to SW_EN=1 only in legacy momde. */
		/* 2. VANT18 might not be enabled because power on fail before low power control is executed. */
		if (consys_is_rc_mode_enable_mt6983() == 0 && regulator_is_enabled(reg_VANT18))
			regulator_disable(reg_VANT18);
		return 0;
	}

	if (consys_is_rc_mode_enable_mt6983()) {
		/* 1. set PMIC VANT18 LDO PMIC HW mode control by PMRC_EN[10][6] */
		/* 1.1. set PMIC VANT18 LDO op_mode = 0 */
		/* 1.2. set PMIC VANT18 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC10_OP_MODE_ADDR, 1 << 2, 0 << 2);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC10_OP_EN_ADDR,   1 << 2, 1 << 2);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC10_OP_CFG_ADDR,  1 << 2, 0 << 2);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC6_OP_MODE_ADDR,  1 << 6, 0 << 6);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC6_OP_EN_ADDR,    1 << 6, 1 << 6);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_RC6_OP_CFG_ADDR,   1 << 6, 0 << 6);
	} else {
		/* 1. set PMIC VANT18 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VANT18 LDO op_mode = 1 */
		/* 1.2. set PMIC VANT18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
		consys_pmic_regmap_set_value(r, MT6373_RG_LDO_VANT18_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

		/* 2. set PMIC VANT18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regulator_set_mode(reg_VANT18, REGULATOR_MODE_NORMAL);
		regulator_enable(reg_VANT18);
	}

	return 0;
}

int consys_vcn13_oc_notify(struct notifier_block *nb, unsigned long event,
				  void *unused)
{
	if (event != REGULATOR_EVENT_OVER_CURRENT)
		return NOTIFY_OK;

	if (g_dev_cb != NULL && g_dev_cb->conninfra_pmic_event_notifier != NULL)
		g_dev_cb->conninfra_pmic_event_notifier(0, 0);
	return NOTIFY_OK;
}

int consys_plt_pmic_event_notifier_mt6983(unsigned int id, unsigned int event)
{
#define LOG_TMP_BUF_SZ 256
#define ATOP_DUMP_NUM 10
#if 0
	static int oc_counter = 0;
	static int oc_dump = 0;
	unsigned int dump1_a, dump1_b, dump2_a, adie_value;
	void __iomem *addr = NULL;
	char tmp[LOG_TMP_BUF_SZ] = {'\0'};
	char tmp_buf[LOG_TMP_BUF_SZ] = {'\0'};
	int ret;
	const unsigned int adie_cr_list[ATOP_DUMP_NUM] = {
		0xa10, 0x90, 0x94, 0xa0,
		0xa18, 0xa1c, 0xc8, 0x3c,
		0x0b4, 0x34c
	};
	int i;

	oc_counter++;
	pr_info("[%s] VCN13 OC times: %d\n", __func__, oc_counter);

	if (oc_counter == 1 || oc_counter == (oc_dump * 100)) {
		oc_dump++;
	} else {
		return NOTIFY_OK;
	}

	/* 1. Dump host csr status
	 * a. 0x1806_02CC 
	 * b. 0x1806_02C8
	 *
	 * 2. Dump R13 status
	 * a. 0x10006110
	 *
	 * 3. Dump RC status
	 * - 0x1000F928, 0x1000F92C, 0x1000F930, 0x1000F934
	 * - trace/timer
	 *
	 * 4. Wake up conninfra
	 *
	 * 5. Dump a-die ck_en
	 * - 0x1800_50a8
	 * - 0x1800_5120/0x1800_5124/0x1800_5128/0x1800_512C/0x1800_5130/0x1800_5134
	 *
	 * 6. Dump a-die status
	 * a. 0xa10
	 * b. 0x090/0x094/0x0a0
	 * c. 0xa18/0xa1c/0x0c8/0x03c
	 *
	 * 7. Make conninfra sleep
	 */
	dump1_a = CONSYS_REG_READ(CONN_HOST_CSR_TOP_DBG_DUMMY_3_ADDR);
	CONSYS_REG_WRITE_HW_ENTRY(
		CONN_HOST_CSR_TOP_CONN_INFRA_CFG_DBG_SEL_CONN_INFRA_CFG_DBG_SEL,
		0x0);
	dump1_b = CONSYS_REG_READ(CONN_HOST_CSR_TOP_DBG_DUMMY_2_ADDR);

	dump2_a = CONSYS_REG_READ(SPM_MD32PCM_SCU_STA0);
	pr_info("0x1806_02CC=[0x%08x] 0x1806_02C8=[0x%08x] 0x1000_6110=[0x%08x]",
		dump1_a, dump1_b, dump2_a);

	addr = ioremap(0x1000F900, 0x100);
	if (addr) {
		pr_info("[rc_status] [0x%08x][0x%08x][0x%08x][0x%08x]",
			CONSYS_REG_READ(addr + 0x28), CONSYS_REG_READ(addr + 0x2c),
			CONSYS_REG_READ(addr + 0x30), CONSYS_REG_READ(addr + 0x34));
		memset(tmp_buf, '\0', LOG_TMP_BUF_SZ);
		for (i = 0x50; i <= 0x94; i+= 4) {
			if (snprintf(tmp, LOG_TMP_BUF_SZ, "[0x%08x]",
				CONSYS_REG_READ(addr + i)) >= 0)
				strncat(tmp_buf, tmp, strlen(tmp));
		}
		pr_info("[rc_trace] %s", tmp_buf);

		memset(tmp_buf, '\0', LOG_TMP_BUF_SZ);
		for (i = 0x98; i <= 0xd4; i += 4) {
			if (snprintf(tmp, LOG_TMP_BUF_SZ, "[0x%08x]",
				CONSYS_REG_READ(addr + i)) >= 0)
				strncat(tmp_buf, tmp, strlen(tmp));
		}
		pr_info("[rc_timer] %s", tmp_buf);
		iounmap(addr);
	} else {
		pr_info("[%s] ioremap 0x1000_F900 fail", __func__);
	}

	ret = consys_hw_force_conninfra_wakeup();
	if (ret) {
		pr_info("[%s] force conninfra wakeup fail\n", __func__);
		return NOTIFY_OK;
	}

	memset(tmp_buf, '\0', LOG_TMP_BUF_SZ);
	for (i = 0x120; i <= 0x134; i+= 4) {
		if (snprintf(tmp, LOG_TMP_BUF_SZ, "[0x%08x]",
			CONSYS_REG_READ(CONN_REG_CONN_WT_SLP_CTL_REG_ADDR + i)) >= 0)
			strncat(tmp_buf, tmp, strlen(tmp));
	}
	pr_info("a-die ck:%s [0x%08x]", tmp_buf, CONSYS_REG_READ(CONN_WT_SLP_CTL_REG_WB_CK_STA_ADDR));

	connsys_adie_top_ck_en_ctl_mt6983(true);
	memset(tmp_buf, '\0', LOG_TMP_BUF_SZ);
	for (i = 0; i < ATOP_DUMP_NUM; i++) {
		consys_spi_read_mt6983(SYS_SPI_TOP, adie_cr_list[i], &adie_value);
		if (snprintf(tmp, LOG_TMP_BUF_SZ, " [0x%04x: 0x%08x]", adie_cr_list[i], adie_value) >= 0)
			strncat(tmp_buf, tmp, strlen(tmp));
	}
	connsys_adie_top_ck_en_ctl_mt6983(false);
	pr_info("ATOP:%s\n", tmp_buf);

	consys_hw_force_conninfra_sleep();
#endif
	return NOTIFY_OK;
}

void consys_pmic_debug_log_mt6983(void)
{
	struct regmap *r = g_regmap_mt6363;
	struct regmap *r2 = g_regmap_mt6373;
	int vcn13, vrfio18, vcn33_1, vcn33_2, vant18;

	if (!r || !r2) {
		pr_notice("%s regmap is NULL\n", __func__);
		return;
	}

	regmap_read(r, MT6363_RG_LDO_VCN13_MON_ADDR, &vcn13);
	regmap_read(r, MT6363_RG_LDO_VRFIO18_MON_ADDR, &vrfio18);
	regmap_read(r2, MT6373_RG_LDO_VCN33_1_MON_ADDR, &vcn33_1);
	regmap_read(r2, MT6373_RG_LDO_VCN33_2_MON_ADDR, &vcn33_2);
	regmap_read(r2, MT6373_RG_LDO_VANT18_MON_ADDR, &vant18);

	pr_info("%s vcn13:0x%x,vrfio18:0x%x,vcn33_1:0x%x,vcn33_2:0x%x,vant18:0x%x\n",
		__func__, vcn13, vrfio18, vcn33_1, vcn33_2, vant18);
}

