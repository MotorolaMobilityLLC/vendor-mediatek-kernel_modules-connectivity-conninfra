// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/regulator/consumer.h>
#include <linux/timer.h>

#include <connectivity_build_in_adapter.h>

#include "../../../../base/include/osal.h"
#include "../include/consys_hw.h"
#include "../include/consys_reg_util.h"
#include "../include/pmic_mng.h"
#include "include/mt6886_consys_reg_offset.h"
#include "include/mt6886_pmic.h"
#include "include/mt6886_pos.h"

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

static struct notifier_block vrfio18_nb;
static struct notifier_block vcn13_nb;

static struct conninfra_dev_cb* g_dev_cb;

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static int consys_plt_pmic_get_from_dts_mt6886(struct platform_device*, struct conninfra_dev_cb*);

static int consys_plt_pmic_common_power_ctrl_mt6886(unsigned int);
static int consys_plt_pmic_common_power_low_power_mode_mt6886(unsigned int);
static int consys_plt_pmic_wifi_power_ctrl_mt6886(unsigned int);
static int consys_plt_pmic_bt_power_ctrl_mt6886(unsigned int);
static int consys_plt_pmic_gps_power_ctrl_mt6886(unsigned int);
static int consys_plt_pmic_fm_power_ctrl_mt6886(unsigned int);
static int consys_pmic_vcn33_1_power_ctl_mt6886_lg(bool);
static int consys_pmic_vcn33_1_power_ctl_mt6886_rc(bool);
static int consys_pmic_vcn33_2_power_ctl_mt6886_lg(bool);
static int consys_pmic_vcn33_2_power_ctl_mt6886_rc(bool);
static int consys_pmic_vant18_power_ctl_mt6886(bool);

#if 0
static int consys_plt_pmic_raise_voltage_mt6886(unsigned int, bool, bool);
static void consys_plt_pmic_raise_voltage_timer_handler_mt6886(timer_handler_arg);
#endif

static int consys_vcn13_oc_notify(struct notifier_block*, unsigned long, void*);
static int consys_vrfio18_oc_notify(struct notifier_block*, unsigned long, void*);
static int consys_plt_pmic_event_notifier_mt6886(unsigned int, unsigned int);

const struct consys_platform_pmic_ops g_consys_platform_pmic_ops_mt6886 = {
	.consys_pmic_get_from_dts = consys_plt_pmic_get_from_dts_mt6886,
	.consys_pmic_common_power_ctrl = consys_plt_pmic_common_power_ctrl_mt6886,
	.consys_pmic_common_power_low_power_mode = consys_plt_pmic_common_power_low_power_mode_mt6886,
	.consys_pmic_wifi_power_ctrl = consys_plt_pmic_wifi_power_ctrl_mt6886,
	.consys_pmic_bt_power_ctrl = consys_plt_pmic_bt_power_ctrl_mt6886,
	.consys_pmic_gps_power_ctrl = consys_plt_pmic_gps_power_ctrl_mt6886,
	.consys_pmic_fm_power_ctrl = consys_plt_pmic_fm_power_ctrl_mt6886,
#if 0
	.consys_pmic_raise_voltage = consys_plt_pmic_raise_voltage_mt6886,
#endif
	.consys_pmic_event_notifier = consys_plt_pmic_event_notifier_mt6886,
};

int consys_plt_pmic_get_from_dts_mt6886(struct platform_device *pdev, struct conninfra_dev_cb* dev_cb)
{
	int ret;

	g_dev_cb = dev_cb;
	reg_VCN13 = devm_regulator_get_optional(&pdev->dev, "mt6363_vcn13");
	if (IS_ERR(reg_VCN13)) {
		pr_err("Regulator_get VCN_13 fail\n");
		reg_VCN13 = NULL;
	} else {
		vcn13_nb.notifier_call = consys_vcn13_oc_notify;
		ret = devm_regulator_register_notifier(reg_VCN13, &vcn13_nb);
		if (ret)
			pr_info("VCN13 regulator notifier request failed\n");
	}

	reg_VRFIO18 = devm_regulator_get(&pdev->dev, "mt6363_vrfio18");
	if (IS_ERR(reg_VRFIO18)) {
		pr_err("Regulator_get VCN_18 fail\n");
		reg_VRFIO18 = NULL;
	} else {
		vrfio18_nb.notifier_call = consys_vrfio18_oc_notify;
		ret = devm_regulator_register_notifier(reg_VRFIO18, &vrfio18_nb);
		if (ret)
			pr_info("VRFIO18 regulator notifier request failed\n");
	}

	reg_VCN33_1 = devm_regulator_get(&pdev->dev, "mt6368_vcn33_1");
	if (IS_ERR(reg_VCN33_1)) {
		pr_err("Regulator_get VCN33_1 fail\n");
		reg_VCN33_1 = NULL;
	}
	reg_VCN33_2 = devm_regulator_get(&pdev->dev, "mt6368_vcn33_2");
	if (IS_ERR(reg_VCN33_2)) {
		pr_err("Regulator_get VCN33_2 fail\n");
		reg_VCN33_2 = NULL;
	}
	reg_VANT18 = devm_regulator_get(&pdev->dev, "mt6368_vant18");
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

int consys_plt_pmic_common_power_ctrl_mt6886(unsigned int enable)
{
	int sleep_mode;
	int ret = 0;
	struct regmap *r = g_regmap_mt6363;

	sleep_mode = consys_get_sleep_mode_mt6886();
	if (enable) {
		/* set PMIC VRFIO18 LDO 1.7V */
		regulator_set_voltage(reg_VRFIO18, 1700000, 1700000);
		/* set PMIC VRFIO18 LDO SW_OP_EN = 1, SW_EN = 1, SW_LP = 0 (SW ON) */
		/*
		 * 1. set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 (SW ON)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 */
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
		ret = regulator_enable(reg_VRFIO18);
		if (ret)
			pr_err("Enable VRFIO18 fail. ret=%d\n", ret);
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL);

		/* set PMIC VCN13 LDO 1.35V @Normal mode; 0.95V @LPM */
		/* no need for LPM because 0.95V is default setting. */
		regulator_set_voltage(reg_VCN13, 1350000, 1350000);
		/*
		 * 1. set PMIC VCN13 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 (SW ON)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 */
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
		ret = regulator_enable(reg_VCN13);
		if (ret)
			pr_err("Enable VCN13 fail. ret=%d\n", ret);
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL);
	} else {
		/* vant18 is enabled in consys_plt_pmic_common_power_low_power_mode_mt6886 */
		/* Please refer to POS for more information */
		consys_pmic_vant18_power_ctl_mt6886(0);

		/* vcn33_1/2 is enabled in consys_plt_pmic_common_power_low_power_mode_mt6886 */
		if (consys_is_rc_mode_enable_mt6886()) {
			consys_pmic_vcn33_2_power_ctl_mt6886_rc(0);
			consys_pmic_vcn33_1_power_ctl_mt6886_rc(0);
		}

		/* wait 1ms for off VCN33_X */
		msleep(1);

		/*
		 * set PMIC VCN13 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 * No need to turn off MT6363_RG_LDO_VCN13_SW_OP_EN_ADDR
		 */
		ret = regulator_disable(reg_VCN13);
		if (ret)
			pr_notice("%s regulator_disable err: %d", __func__, ret);
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL);

		/*
		 * set PMIC VRFIO18 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 */
		/* set PMIC VRFIO18 LDO SW_EN = 0, SW_LP =0 (sw disable)
		 * No need to turn off  MT6363_RG_LDO_VRFIO18_SW_OP_EN_ADDR
		 */
		if (!consys_is_rc_mode_enable_mt6886() || (sleep_mode == 1 || sleep_mode == 3)) {
			ret = regulator_disable(reg_VRFIO18);
			if (ret)
				pr_notice("%s regulator_disable err: %d", __func__, ret);
		}
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL);

		/* Set buckboost to 3.45V (for VCN33_1 & VCN33_2) */
		if (reg_buckboost) {
			regulator_set_voltage(reg_buckboost, 3450000, 3450000);
			pr_info("Set buckboost to 3.45V\n");
		}
	}
	return ret;
}

int consys_plt_pmic_common_power_low_power_mode_mt6886(unsigned int enable)
{
	int ret = 0;
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

	sleep_mode = consys_get_sleep_mode_mt6886();
	/* set PMIC VCN13 LDO 1.35V @Normal mode; 0.95V @LPM */
	/* no need for LPM because 0.95V is default setting. */
	/* sleep mode 3 with LPM voltage 1.05V */
	if (sleep_mode == 3)
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_VOSEL_SLEEP_ADDR, 0x7f, 0x1);

	if (consys_is_rc_mode_enable_mt6886()) {
		/* 1. set PMIC VRFIO18 LDO PMIC HW mode control by PMRC_EN[9][8][7][6] */
		/* 1.1. set PMIC VRFIO18 LDO op_mode = 0 */
		/* 1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC9_OP_MODE_ADDR, 1 << 1, 0 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC9_OP_EN_ADDR,   1 << 1, 1 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC9_OP_CFG_ADDR,  1 << 1, 0 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC6_OP_MODE_ADDR, 1 << 6, 0 << 6);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC6_OP_EN_ADDR,   1 << 6, 1 << 6);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_RC6_OP_CFG_ADDR,  1 << 6, 0 << 6);

		if (sleep_mode == 1 || sleep_mode == 3) {
			/* 2. set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =1 */
			/*
			 * skip set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1
			 * it is set on .consys_pmic_common_power_ctrl
			 */
			regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_IDLE);
		} else {
			/* 2. set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 0, SW_LP =0 */
			regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
			ret = regulator_disable(reg_VRFIO18);
			if (ret)
				pr_notice("%s regulator_disable err: %d", __func__, ret);
			regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL);
		}

		/* 1. set PMIC VCN13 LDO PMIC HW mode control by PMRC_EN[9][8][7][6] */
		/* 1.1. set PMIC VCN13 LDO op_mode = 0 */
		/* 1.2. set PMIC VCN13 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC9_OP_MODE_ADDR, 1 << 1, 0 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC9_OP_EN_ADDR,   1 << 1, 1 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC9_OP_CFG_ADDR,  1 << 1, 0 << 1);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC6_OP_MODE_ADDR, 1 << 6, 0 << 6);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC6_OP_EN_ADDR,   1 << 6, 1 << 6);
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_RC6_OP_CFG_ADDR,  1 << 6, 0 << 6);

		/* 2. set PMIC VCN13 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =1 */
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_IDLE);
	} else {
		/* 1. set PMIC VRFIO18 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VRFIO18 LDO op_mode = 1 */
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);

		/*  if (A-die sleep mode-2 ){ */
		/*    1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		/*  }else{ //A-die sleep mode-1 */
		/*    1.2. set PMIC VRFIO18 LDO HW_OP_EN = 1, HW_OP_CFG = 1 */
		if (sleep_mode == 2) {
			regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
			regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 0 << 0);
		} else {
			regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
			regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 1 << 0);
		}

		/* 2. set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		/*
		 * skip set PMIC VRFIO18 LDO SW_OP_EN =1, SW_EN = 1
		 * it is set on .consys_pmic_common_power_ctrl
		 */
		regulator_set_mode(reg_VRFIO18, REGULATOR_MODE_NORMAL);

		/* 1. set PMIC VCN13 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VCN13 LDO op_mode = 1 */
		regmap_update_bits(r, MT6363_RG_LDO_VCN13_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);

		/* 1.2. set PMIC VCN13 LDO HW_OP_EN = 1, HW_OP_CFG = 1 */
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_EN_ADDR,   1 << 0, 1 << 0);
		regmap_update_bits(r, MT6363_RG_LDO_VRFIO18_HW0_OP_CFG_ADDR,  1 << 0, 1 << 0);

		/* 2. set PMIC VCN13 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		/*
\		 * skip set PMIC reg_VCN13 LDO SW_OP_EN =1, SW_EN = 1
		 * it is set on .consys_pmic_common_power_ctrl
		 */
		regulator_set_mode(reg_VCN13, REGULATOR_MODE_NORMAL);
	}

	if (consys_is_rc_mode_enable_mt6886()) {
		consys_pmic_vcn33_1_power_ctl_mt6886_rc(enable);
		consys_pmic_vcn33_2_power_ctl_mt6886_rc(enable);
	}
	consys_pmic_vant18_power_ctl_mt6886(enable);
	return ret;
}

int consys_plt_pmic_wifi_power_ctrl_mt6886(unsigned int enable)
{
	int ret;

	/* necessary in legacy mode only */
	if (consys_is_rc_mode_enable_mt6886())
		return 0;

	ret = consys_pmic_vcn33_1_power_ctl_mt6886_lg(enable);
	if (ret)
		pr_info("%s VCN33_1 fail\n", (enable? "Enable" : "Disable"));

	ret = consys_pmic_vcn33_2_power_ctl_mt6886_lg(enable);
	if (ret)
		pr_info("%s VCN33_2 fail\n", (enable? "Enable" : "Disable"));

	return ret;
}

int consys_plt_pmic_bt_power_ctrl_mt6886(unsigned int enable)
{
	/* necessary in legacy mode only */
	if (consys_is_rc_mode_enable_mt6886())
		return 0;
	return consys_pmic_vcn33_1_power_ctl_mt6886_lg(enable);
}

int consys_plt_pmic_gps_power_ctrl_mt6886(unsigned int enable)
{
	return 0;
}

int consys_plt_pmic_fm_power_ctrl_mt6886(unsigned int enable)
{
	return 0;
}

static int consys_pmic_vcn33_1_power_ctl_mt6886_rc(bool enable)
{
	int sleep_mode;
	struct regmap *r = g_regmap_mt6368;
	int ret;

	sleep_mode = consys_get_sleep_mode_mt6886();
	if (enable) {
		/* 1. set PMIC VCN33_1 LDO PMIC HW mode control by PMRC_EN[8][7] */
		/* 1.1. set PMIC VCN33_1 LDO op_mode = 0 */
		/* 1.2. set PMIC VCN33_1 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC7_OP_MODE_ADDR, 1 << 7, 0 << 7);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC7_OP_EN_ADDR,   1 << 7, 1 << 7);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_RC7_OP_CFG_ADDR,  1 << 7, 0 << 7);

		if (sleep_mode == 3) {
			/*
			 * 2. set PMIC VCN33_1 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 (sw on)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 */
			regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
			ret = regulator_enable(reg_VCN33_1);
			if (ret)
				pr_notice("%s regulator_enable err: %d", __func__, ret);
			regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);

			/* 3. wait 210us */
			usleep_range(210, 1000);

			/*
			 * 4. set PMIC VCN33_1 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =1 (sw lp)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 */
			regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_IDLE);
		} else {
			/*
			 * 2. set PMIC VCN33_1 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 * No need to turn off MT6368_RG_LDO_VCN33_1_SW_OP_EN_ADDR
			 */
			regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);
		}
	} else {
		/*
		 * set PMIC VCN33_1 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 * No need to turn off MT6368_RG_LDO_VCN33_1_SW_OP_EN_ADDR
		 */
		if (sleep_mode == 3)
			regulator_disable(reg_VCN33_1);
		regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);
	}

	return 0;
}

static int consys_pmic_vcn33_1_power_ctl_mt6886_lg(bool enable)
{
	struct regmap *r = g_regmap_mt6368;
	static int enable_count = 0;
	int ret;

	/* In legacy mode, VCN33_1 should be turned on either WIFI or BT is on */
	/* we use a counter to record the usage. */
	if (enable)
		enable_count++;
	else
		enable_count--;

	pr_info("%s enable_count %d\n", __func__, enable_count);
	if (enable_count < 0 || enable_count >= 2) {
		pr_info("enable_count %d is unexpected!!!\n", enable_count);
		return 0;
	}

	if (enable_count == 0) {
		/*
		 * set PMIC VCN33_1 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 * No need to turn off MT6368_RG_LDO_VCN33_1_SW_OP_EN_ADDR
		 */
		ret = regulator_disable(reg_VCN33_1);
		if (ret)
			pr_notice("%s regulator_disable err: %d", __func__, ret);
		regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);
		return ret;
	}

	/* vcn33_1 is still on */
	if (enable_count == 1 && enable == 0)
		return 0;

	/* !!! Notice that following steps will be executed only when enable_count == 1 !!!*/
	/* 1. set PMIC VCN33_1 LDO PMIC HW mode control by SRCCLKENA0 */
	/* 1.1. set PMIC VCN33_1 LDO op_mode = 1 */
	/* 1.2. set PMIC VCN33_1 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
	regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
	regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
	regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

	/* 2. set PMIC VCN33_1 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
	regmap_update_bits(r, MT6368_RG_LDO_VCN33_1_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
	ret = regulator_enable(reg_VCN33_1);
	if (ret)
		pr_notice("%s regulator_enable err: %d", __func__, ret);
	regulator_set_mode(reg_VCN33_1, REGULATOR_MODE_NORMAL);

	return ret;
}


static int consys_pmic_vcn33_2_power_ctl_mt6886_lg(bool enable)
{
	struct regmap *r = g_regmap_mt6368;
	int ret = 0;

	if (!enable) {
		/*
		 * set PMIC VCN33_2 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 * No need to turn off MT6368_RG_LDO_VCN33_2_SW_OP_EN_ADDR
		 */
		ret = regulator_disable(reg_VCN33_2);
		if (ret)
			pr_notice("%s regulator_disable err: %d", __func__, ret);
		regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);
        } else {
		/* 1. set PMIC VCN33_2 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VCN33_2 LDO op_mode = 1 */
		/* 1.2. set PMIC VCN33_2 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

		/* 2. set PMIC VCN33_2 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
		ret = regulator_enable(reg_VCN33_2);
		if (ret)
			pr_notice("%s regulator_enable err: %d", __func__, ret);
		regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);
	}
	return ret;
}

static int consys_pmic_vcn33_2_power_ctl_mt6886_rc(bool enable)
{
	int sleep_mode;
	struct regmap *r = g_regmap_mt6368;
	int ret;

	sleep_mode = consys_get_sleep_mode_mt6886();
	if (enable) {
		/* 1. set PMIC VCN33_2 LDO PMIC HW mode control by PMRC_EN[8] */
		/* 1.1. set PMIC VCN33_2 LDO op_mode = 0 */
		/* 1.2. set PMIC VCN33_2 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_RC8_OP_MODE_ADDR, 1 << 0, 0 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_RC8_OP_EN_ADDR,   1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_RC8_OP_CFG_ADDR,  1 << 0, 0 << 0);

		if (sleep_mode == 3) {
			/*
			 * 2. set PMIC VCN33_2 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 (sw on)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 */
			regmap_update_bits(r, MT6368_RG_LDO_VCN33_2_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
			ret = regulator_enable(reg_VCN33_2);
			if (ret)
				pr_notice("%s regulator_enable err: %d", __func__, ret);
			regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);

			/* 3. wait 210us */
			usleep_range(210, 1000);

			/*
			 * 4. set PMIC VCN33_2 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =1 (sw lp)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 */
			regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_IDLE);
		} else {
			/*
			 * 2. set PMIC VCN33_2 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
			 * (by ""standard kernal PMIC API"" and ""PMIC table"")
			 * No need to turn off MT6368_RG_LDO_VCN33_2_SW_OP_EN_ADDR
			 */
			regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);
		}
	} else {
		/*
		 * set PMIC VCN33_2 LDO SW_OP_EN =0, SW_EN = 0, SW_LP =0 (sw disable)
		 * (by "standard kernal PMIC API" and "PMIC table")
		 * No need to turn off MT6368_RG_LDO_VCN33_2_SW_OP_EN_ADDR
		 */
		if (sleep_mode == 3)
			regulator_disable(reg_VCN33_2);
		regulator_set_mode(reg_VCN33_2, REGULATOR_MODE_NORMAL);
	}

	return 0;
}

static int consys_pmic_vant18_power_ctl_mt6886(bool enable)
{
	struct regmap *r = g_regmap_mt6368;
	int ret = 0;

	if (!enable) {
		/* 1. VANT18 will be set to SW_EN=1 only in legacy momde. */
		/* 2. VANT18 might not be enabled because power on fail before low power control is executed. */
		if (consys_is_rc_mode_enable_mt6886() == 0 && regulator_is_enabled(reg_VANT18)) {
			ret = regulator_disable(reg_VANT18);
			if (ret)
				pr_notice("%s regulator_disable err:%d", __func__, ret);
		}
		return ret;
	}

	if (consys_is_rc_mode_enable_mt6886()) {
		/* 1. set PMIC VANT18 LDO PMIC HW mode control by PMRC_EN[10][6] */
		/* 1.1. set PMIC VANT18 LDO op_mode = 0 */
		/* 1.2. set PMIC VANT18 LDO  HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC10_OP_MODE_ADDR, 1 << 2, 0 << 2);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC10_OP_EN_ADDR,   1 << 2, 1 << 2);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC10_OP_CFG_ADDR,  1 << 2, 0 << 2);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC6_OP_MODE_ADDR,  1 << 6, 0 << 6);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC6_OP_EN_ADDR,    1 << 6, 1 << 6);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_RC6_OP_CFG_ADDR,   1 << 6, 0 << 6);
	} else {
		/* 1. set PMIC VANT18 LDO PMIC HW mode control by SRCCLKENA0 */
		/* 1.1. set PMIC VANT18 LDO op_mode = 1 */
		/* 1.2. set PMIC VANT18 LDO HW_OP_EN = 1, HW_OP_CFG = 0 */
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_HW0_OP_MODE_ADDR, 1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_HW0_OP_EN_ADDR, 1 << 0, 1 << 0);
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_HW0_OP_CFG_ADDR, 1 << 0, 0 << 0);

		/* 2. set PMIC VANT18 LDO SW_OP_EN =1, SW_EN = 1, SW_LP =0 */
		regmap_update_bits(r, MT6368_RG_LDO_VANT18_SW_OP_EN_ADDR, 1 << 7, 1 << 7);
		ret = regulator_enable(reg_VANT18);
		if (ret)
			pr_notice("%s regulator_enable err: %d", __func__, ret);
		regulator_set_mode(reg_VANT18, REGULATOR_MODE_NORMAL);
	}

	return ret;
}

static void dump_adie_cr(enum sys_spi_subsystem subsystem, const unsigned int *adie_cr, int num, char *title)
{
#define LOG_TMP_BUF_SZ 256
	unsigned int adie_value;
	char tmp[LOG_TMP_BUF_SZ] = {'\0'};
	char tmp_buf[LOG_TMP_BUF_SZ] = {'\0'};
	int i;

	memset(tmp_buf, '\0', LOG_TMP_BUF_SZ);
	for (i = 0; i < num; i++) {
		if (consys_hw_spi_read(subsystem, adie_cr[i], &adie_value) < 0) {
			pr_notice("[%s] consys_hw_spi_read failed\n", __func__);
			continue;
		}
		if (snprintf(tmp, LOG_TMP_BUF_SZ, "[0x%04x: 0x%08x]", adie_cr[i], adie_value) >= 0)
			strncat(tmp_buf, tmp, strlen(tmp));
	}
	pr_info("%s:%s\n", title, tmp_buf);
}

static int consys_plt_pmic_event_notifier_mt6886(unsigned int id, unsigned int event)
{
#define ATOP_DUMP_NUM 12
#define AWF_DUMP_NUM 3
	int ret;
	const unsigned int adie_top_cr_list[ATOP_DUMP_NUM] = {
		0x03C, 0x090, 0x094, 0x0A0,
		0x0C8, 0x0FC, 0xA10, 0xB00,
		0xAFC, 0x160, 0xC54, 0xC58,
	};
	const unsigned int adie_wf_cr_list[AWF_DUMP_NUM] = {
		0xFFF, 0x81, 0x80,
	};


	consys_pmic_debug_log_mt6886();

	ret = consys_hw_force_conninfra_wakeup();
	if (ret) {
		pr_info("[%s] force conninfra wakeup fail\n", __func__);
		return -1;
	}

	/* dump d-die cr */
	consys_hw_is_bus_hang();

	/* dump a-die cr */
	dump_adie_cr(SYS_SPI_TOP, adie_top_cr_list, ATOP_DUMP_NUM, "A-die TOP");
	consys_hw_adie_top_ck_en_on(CONNSYS_ADIE_CTL_HOST_CONNINFRA);
	consys_hw_spi_update_bits(SYS_SPI_TOP, 0x580, 0x00, 0x10);
	consys_hw_adie_top_ck_en_off(CONNSYS_ADIE_CTL_HOST_CONNINFRA);
	dump_adie_cr(SYS_SPI_TOP, adie_top_cr_list, ATOP_DUMP_NUM, "A-die TOP");
	dump_adie_cr(SYS_SPI_WF, adie_wf_cr_list, AWF_DUMP_NUM, "A-die WF0");
	dump_adie_cr(SYS_SPI_WF1, adie_wf_cr_list, AWF_DUMP_NUM, "A-die WF1");

	consys_hw_force_conninfra_sleep();

	return 0;
}

static int consys_vcn13_oc_notify(struct notifier_block *nb, unsigned long event,
				  void *unused)
{
	static int oc_counter = 0;
	static int oc_dump = 0;

	if (event != REGULATOR_EVENT_OVER_CURRENT)
		return NOTIFY_OK;

	oc_counter++;
	pr_info("[%s] VCN13 OC times: %d\n", __func__, oc_counter);

	if (oc_counter <= 30)
		oc_dump = 1;
	else if (oc_counter == (oc_dump * 100))
		oc_dump++;
	else
		return NOTIFY_OK;

	if (g_dev_cb != NULL && g_dev_cb->conninfra_pmic_event_notifier != NULL)
		g_dev_cb->conninfra_pmic_event_notifier(0, 0);

	return NOTIFY_OK;
}

static int consys_vrfio18_oc_notify(struct notifier_block *nb, unsigned long event,
				  void *unused)
{
	static int oc_counter = 0;
	static int oc_dump = 0;

	if (event != REGULATOR_EVENT_OVER_CURRENT)
		return NOTIFY_OK;

	oc_counter++;
	pr_info("[%s] VRFIO18 OC times: %d\n", __func__, oc_counter);

	if (oc_counter <= 30)
		oc_dump = 1;
	else if (oc_counter == (oc_dump * 100))
		oc_dump++;
	else
		return NOTIFY_OK;

	if (g_dev_cb != NULL && g_dev_cb->conninfra_pmic_event_notifier != NULL)
		g_dev_cb->conninfra_pmic_event_notifier(0, 0);

	return NOTIFY_OK;
}

void consys_pmic_debug_log_mt6886(void)
{
	struct regmap *r = g_regmap_mt6363;
	struct regmap *r2 = g_regmap_mt6368;
	int vcn13 = 0, vrfio18 = 0, vcn33_1 = 0, vcn33_2 = 0, vant18 = 0;

	if (!r || !r2) {
		pr_notice("%s regmap is NULL\n", __func__);
		return;
	}

	regmap_read(r, MT6363_RG_LDO_VCN13_MON_ADDR, &vcn13);
	regmap_read(r, MT6363_RG_LDO_VRFIO18_MON_ADDR, &vrfio18);
	regmap_read(r2, MT6368_RG_LDO_VCN33_1_MON_ADDR, &vcn33_1);
	regmap_read(r2, MT6368_RG_LDO_VCN33_2_MON_ADDR, &vcn33_2);
	regmap_read(r2, MT6368_RG_LDO_VANT18_MON_ADDR, &vant18);

	pr_info("%s vcn13:0x%x,vrfio18:0x%x,vcn33_1:0x%x,vcn33_2:0x%x,vant18:0x%x\n",
		__func__, vcn13, vrfio18, vcn33_1, vcn33_2, vant18);
}

