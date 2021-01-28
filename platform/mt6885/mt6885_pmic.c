/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
/*! \file
*    \brief  Declaration of library functions
*
*    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
*/

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <linux/memblock.h>
#include <linux/platform_device.h>
//#ifdef CONFIG_MTK_EMI
//#include <mt_emi_api.h>
//#endif
#include <linux/of_reserved_mem.h>
#include <upmu_common.h>
#include <linux/regulator/consumer.h>

#include "osal.h"
#include "mt6885_pmic.h"
#include "consys_hw.h"

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

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

static int consys_plt_pmic_get_from_dts(struct platform_device *pdev);

static int consys_plt_pmic_common_power_ctrl(unsigned int enable);
static int consys_plt_pmic_wifi_power_ctrl(unsigned int enable);
static int consys_plt_pmic_bt_power_ctrl(unsigned int enable);
static int consys_plt_pmic_gps_power_ctrl(unsigned int enable);
static int consys_plt_pmic_fm_power_ctrl(unsigned int enable);



/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

CONSYS_PLATFORM_PMIC_OPS g_consys_platform_pmic_ops = {
	.consys_pmic_get_from_dts = consys_plt_pmic_get_from_dts,
	/* vcn 18 */
	.consys_pmic_common_power_ctrl = consys_plt_pmic_common_power_ctrl,
	.consys_pmic_wifi_power_ctrl = consys_plt_pmic_wifi_power_ctrl,
	.consys_pmic_bt_power_ctrl = consys_plt_pmic_bt_power_ctrl,
	.consys_pmic_gps_power_ctrl = consys_plt_pmic_gps_power_ctrl,
	.consys_pmic_fm_power_ctrl = consys_plt_pmic_fm_power_ctrl,

};

struct regulator *reg_VCN18;
struct regulator *reg_VCN28;
struct regulator *reg_VCN33_BT;
struct regulator *reg_VCN33_WIFI;


/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

P_CONSYS_PLATFORM_PMIC_OPS get_consys_platform_pmic_ops(void)
{
	return &g_consys_platform_pmic_ops;
}


int consys_plt_pmic_get_from_dts(struct platform_device *pdev)
{
//#if CONSYS_PMIC_CTRL_ENABLE
	reg_VCN18 = regulator_get(&pdev->dev, "vcn18");
	if (!reg_VCN18)
		pr_err("Regulator_get VCN_1V8 fail\n");
	reg_VCN28 = regulator_get(&pdev->dev, "vcn28");
	if (!reg_VCN28)
		pr_err("Regulator_get VCN_2V8 fail\n");
	reg_VCN33_BT = regulator_get(&pdev->dev, "vcn33_bt");
	if (!reg_VCN33_BT)
		pr_err("Regulator_get VCN33_BT fail\n");
	reg_VCN33_WIFI = regulator_get(&pdev->dev, "vcn33_wifi");
	if (!reg_VCN33_WIFI)
		pr_err("Regulator_get VCN33_WIFI fail\n");
//#endif
	return 0;
}

int consys_plt_pmic_common_power_ctrl(unsigned int enable)
{
#if 0
	if (enable) {
		/*Set VCN18_SW_OP_EN as 1*/
		KERNEL_pmic_ldo_vcn18_lp(SW, 1, 1, SW_OFF);
		/*Set VCN18_SW_EN as 1 and set votage as 1V8*/
		if (reg_VCN18) {
			regulator_set_voltage(reg_VCN18, 1800000, 1800000);
			if (regulator_enable(reg_VCN18))
				pr_err("enable VCN18 fail\n");
			else
				pr_debug("enable VCN18 ok\n");
		}
		/*Set VCN18 SW_LP as 0*/
		KERNEL_pmic_set_register_value(PMIC_RG_LDO_VCN18_LP, 0);
		/*Set VCN18 as low-power mode(1), HW0_OP_EN as 1, HW0_OP_CFG as HW_LP(1)*/
		KERNEL_pmic_ldo_vcn18_lp(SRCLKEN0, 1, 1, HW_LP);

		/* delay 300us (VCN18 stable time) */
		udelay(300);
		/*Set VCN13_SW_OP_EN as 1*/
		KERNEL_pmic_ldo_vcn13_lp(SW, 1, 1, SW_OFF);

		/*Set VCN13_SW_EN as 1 and set votage as 1V3*/
		if (reg_VCN13) {
			regulator_set_voltage(reg_VCN13, 1300000, 1300000);
			if (regulator_enable(reg_VCN13))
				pr_err("enable VCN13 fail\n");
			else
				pr_debug("enable VCN13 ok\n");
		}
		/*Set VCN13 SW_LP as 0*/
		KERNEL_pmic_set_register_value(PMIC_RG_LDO_VCN13_LP, 0);
		/*Set VCN13 as low-power mode(1), HW0_OP_EN as 1, HW0_OP_CFG as HW_LP(1)*/
		KERNEL_pmic_ldo_vcn13_lp(SRCLKEN0, 1, 1, HW_LP);
	} else {
		if (reg_VCN13)
			regulator_disable(reg_VCN13);
		/*AP power off MT6351L VCN_1V8 LDO */
		if (reg_VCN18) {
			if (regulator_disable(reg_VCN18))
				pr_err("disable VCN_1V8 fail!\n");
			else
				pr_debug("disable VCN_1V8 ok\n");
		}

	}
#endif

	return 0;
}

int consys_plt_pmic_wifi_power_ctrl(unsigned int enable)
{
#if 0
	if (enable) {
		/*Set VCN33_1_SW_OP_EN as 1*/
		KERNEL_pmic_ldo_vcn33_1_lp(SW, 1, 1, SW_OFF);
		/*Set VCN33_1_SW_EN as 1 and set votage as 3V3*/
		if (reg_VCN33_1_WIFI) {
			regulator_set_voltage(reg_VCN33_1_WIFI, 3300000, 3300000);
			if (regulator_enable(reg_VCN33_1_WIFI))
				pr_err("WMT do WIFI PMIC on fail!\n");
		}
		/*Set VCN33_1 SW_LP as 0*/
		KERNEL_pmic_set_register_value(PMIC_RG_LDO_VCN33_1_LP, 0);
		/*Set VCN33_1 as low-power mode(1), HW0_OP_EN as 1, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_1_lp(SRCLKEN0, 1, 1, HW_OFF);

		/*Set VCN33_2_SW_OP_EN as 1*/
		KERNEL_pmic_ldo_vcn33_2_lp(SW, 1, 1, SW_OFF);
		/*Set VCN33_1_SW_EN as 1 and set votage as 3V3*/
		if (reg_VCN33_2_WIFI) {
			regulator_set_voltage(reg_VCN33_2_WIFI, 3300000, 3300000);
			if (regulator_enable(reg_VCN33_2_WIFI))
				pr_err("WMT do WIFI PMIC on fail!\n");
		}
		/*Set VCN33_2 SW_LP as 0*/
		KERNEL_pmic_set_register_value(PMIC_RG_LDO_VCN33_2_LP, 0);
		/*Set VCN33_2 as low-power mode(1), HW0_OP_EN as 1, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_2_lp(SRCLKEN0, 1, 1, HW_OFF);
		pr_info("WMT do WIFI PMIC on\n");
	} else {
		/*do WIFI PMIC off */
		/*switch WIFI PALDO control from HW mode to SW mode:0x418[14]-->0x0 */
		/*Set VCN33_1 as low-power mode(1), HW0_OP_EN as 0, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_1_lp(SRCLKEN0, 1, 0, HW_OFF);
		if (reg_VCN33_1_WIFI)
			regulator_disable(reg_VCN33_1_WIFI);

		/*Set VCN33_2 as low-power mode(1), HW0_OP_EN as 0, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_2_lp(SRCLKEN0, 1, 0, HW_OFF);
		if (reg_VCN33_2_WIFI)
			regulator_disable(reg_VCN33_2_WIFI);
		pr_info("WMT do WIFI PMIC off\n");
	}
#endif
	return 0;
}

int consys_plt_pmic_bt_power_ctrl(unsigned int enable)
{
#if 0
	if (enable) {
		/*Set VCN33_1_SW_OP_EN as 1*/
		KERNEL_pmic_ldo_vcn33_1_lp(SW, 1, 1, SW_OFF);
		/*Set VCN33_1_SW_EN as 1 and set votage as 3V3*/
		if (reg_VCN33_1_BT) {
			regulator_set_voltage(reg_VCN33_1_BT, 3300000, 3300000);
			if (regulator_enable(reg_VCN33_1_BT))
				pr_err("WMT do BT PMIC on fail!\n");
		}
		/*Set VCN33_1 SW_LP as 0*/
		KERNEL_pmic_set_register_value(PMIC_RG_LDO_VCN33_1_LP, 0);
		/*Set VCN33_1 as low-power mode(1), HW0_OP_EN as 1, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_1_lp(SRCLKEN0, 1, 1, HW_OFF);

		/* request VS2 to 1.4V by VS2 VOTER (use bit 4) */
		KERNEL_pmic_set_register_value(PMIC_RG_BUCK_VS2_VOTER_EN_SET, 0x10);
		/* Set VCN13 to 1.32V */
		KERNEL_pmic_set_register_value(PMIC_RG_VCN13_VOCAL, 0x2);

		pr_debug("WMT do BT PMIC on\n");
	} else {
		/*do BT PMIC off */
		/*switch BT PALDO control from HW mode to SW mode:0x416[5]-->0x0 */
		/*Set VCN33_1 as low-power mode(1), HW0_OP_EN as 0, HW0_OP_CFG as HW_OFF(0)*/
		KERNEL_pmic_ldo_vcn33_1_lp(SRCLKEN0, 1, 0, HW_OFF);
		/* restore VCN13 to 1.3V */
		KERNEL_pmic_set_register_value(PMIC_RG_VCN13_VOCAL, 0);
		/* clear bit 4 of VS2 VOTER then VS2 can restore to 1.35V */
		KERNEL_pmic_set_register_value(PMIC_RG_BUCK_VS2_VOTER_EN_CLR, 0x10);

		if (reg_VCN33_1_BT)
			regulator_disable(reg_VCN33_1_BT);
		pr_debug("WMT do BT PMIC off\n");
	}
#endif
	return 0;
}

int consys_plt_pmic_gps_power_ctrl(unsigned int enable)
{
	return 0;
}

int consys_plt_pmic_fm_power_ctrl(unsigned int enable)
{
	return 0;
}



