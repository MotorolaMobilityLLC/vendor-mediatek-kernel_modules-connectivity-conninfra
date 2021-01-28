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

#include <linux/of_reserved_mem.h>
#include <linux/delay.h>
#include "osal.h"

#include "consys_hw.h"
#include "emi_mng.h"
#include "pmic_mng.h"

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

static int mtk_conninfra_probe(struct platform_device *pdev);
static int mtk_conninfra_remove(struct platform_device *pdev);
static int mtk_conninfra_suspend(struct platform_device *pdev, pm_message_t state);
static int mtk_conninfra_resume(struct platform_device *pdev);

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

#ifdef CONFIG_OF
const struct of_device_id apconninfra_of_ids[] = {
	{.compatible = "mediatek,mt6765-consys",},
	{.compatible = "mediatek,mt6761-consys",},
	{}
};
#endif

static struct platform_driver mtk_conninfra_dev_drv = {
	.probe = mtk_conninfra_probe,
	.remove = mtk_conninfra_remove,
	.suspend = mtk_conninfra_suspend,
	.resume = mtk_conninfra_resume,
	.driver = {
		   .name = "mtk_conninfra",
		   .owner = THIS_MODULE,
#ifdef CONFIG_OF
		   .of_match_table = apconninfra_of_ids,
#endif
		   },
};

P_CONSYS_HW_OPS consys_hw_ops;
struct platform_device *g_pdev;

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
P_CONSYS_HW_OPS __weak get_consys_platform_ops(void)
{
	pr_warn("Does not support on combo\n");
	return NULL;
}


struct platform_device *get_consys_device(void)
{
	return g_pdev;
}


int consys_hw_pwr_off(void)
{
#if 0
	if (wmt_consys_ic_ops->consys_ic_ahb_clock_ctrl)
			wmt_consys_ic_ops->consys_ic_ahb_clock_ctrl(DISABLE);
		if (wmt_consys_ic_ops->consys_ic_hw_power_ctrl)
			wmt_consys_ic_ops->consys_ic_hw_power_ctrl(DISABLE);
		if (co_clock_type) {
			if (wmt_consys_ic_ops->consys_ic_clock_buffer_ctrl)
				wmt_consys_ic_ops->consys_ic_clock_buffer_ctrl(DISABLE);
		}

		if (co_clock_type == 0) {
			if (wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl)
				wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl(DISABLE);
			/*turn off VCN28 LDO (with PMIC_WRAP API)" */
			if (wmt_consys_ic_ops->consys_ic_hw_vcn28_ctrl)
				wmt_consys_ic_ops->consys_ic_hw_vcn28_ctrl(DISABLE);
		}

		if (wmt_consys_ic_ops->consys_ic_set_if_pinmux)
			wmt_consys_ic_ops->consys_ic_set_if_pinmux(DISABLE);

		if (wmt_consys_ic_ops->consys_ic_hw_vcn18_ctrl)
			wmt_consys_ic_ops->consys_ic_hw_vcn18_ctrl(DISABLE);
#endif
	return 0;
}

int consys_hw_pwr_on(void)
{
	int ret;

	ret = pmic_mng_common_power_ctrl(1);

	if (consys_hw_ops->consys_plt_set_if_pinmux)
		consys_hw_ops->consys_plt_set_if_pinmux(1);

	if (consys_hw_ops->consys_plt_clock_buffer_ctrl)
		consys_hw_ops->consys_plt_clock_buffer_ctrl(1);

	udelay(150);
	/* co-clock control */

	/* efuse */

	if (consys_hw_ops->consys_plt_hw_reset_bit_set)
		consys_hw_ops->consys_plt_hw_reset_bit_set(1);

	if (consys_hw_ops->consys_plt_hw_power_ctrl)
		consys_hw_ops->consys_plt_hw_power_ctrl(1);

	udelay(10);

	if (consys_hw_ops->consys_plt_polling_consys_chipid)
		consys_hw_ops->consys_plt_polling_consys_chipid();

	if (consys_hw_ops->consys_plt_hw_reset_bit_set)
		consys_hw_ops->consys_plt_hw_reset_bit_set(1);

#if 0
	if (wmt_consys_ic_ops->consys_ic_reset_emi_coredump)
			wmt_consys_ic_ops->consys_ic_reset_emi_coredump(pEmibaseaddr);

		if (wmt_consys_ic_ops->consys_ic_hw_vcn18_ctrl)
			wmt_consys_ic_ops->consys_ic_hw_vcn18_ctrl(ENABLE);

		if (wmt_consys_ic_ops->consys_ic_set_if_pinmux)
			wmt_consys_ic_ops->consys_ic_set_if_pinmux(ENABLE);

		udelay(150);

		if (co_clock_type) {
			pr_info("co clock type(%d),turn on clk buf\n", co_clock_type);
			if (wmt_consys_ic_ops->consys_ic_clock_buffer_ctrl)
				wmt_consys_ic_ops->consys_ic_clock_buffer_ctrl(ENABLE);
		}

		if (co_clock_type) {
			/*if co-clock mode: */
			/*1.set VCN28 to SW control mode (with PMIC_WRAP API) */
			if (wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl)
				wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl(DISABLE);
		} else {
			/*if NOT co-clock: */
			/*1.set VCN28 to HW control mode (with PMIC_WRAP API) */
			/*2.turn on VCN28 LDO (with PMIC_WRAP API)" */
			if (wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl)
				wmt_consys_ic_ops->consys_ic_vcn28_hw_mode_ctrl(ENABLE);
			if (wmt_consys_ic_ops->consys_ic_hw_vcn28_ctrl)
				wmt_consys_ic_ops->consys_ic_hw_vcn28_ctrl(ENABLE);
		}

		/* turn on VCN28 LDO for reading efuse usage */
		mtk_wcn_consys_hw_efuse_paldo_ctrl(ENABLE, co_clock_type);

		if (wmt_consys_ic_ops->consys_ic_hw_reset_bit_set)
			wmt_consys_ic_ops->consys_ic_hw_reset_bit_set(ENABLE);
		if (wmt_consys_ic_ops->consys_ic_hw_spm_clk_gating_enable)
			wmt_consys_ic_ops->consys_ic_hw_spm_clk_gating_enable();
		if (wmt_consys_ic_ops->consys_ic_hw_power_ctrl)
			wmt_consys_ic_ops->consys_ic_hw_power_ctrl(ENABLE);

		udelay(10);

		if (wmt_consys_ic_ops->consys_ic_ahb_clock_ctrl)
			wmt_consys_ic_ops->consys_ic_ahb_clock_ctrl(ENABLE);

		WMT_STEP_DO_ACTIONS_FUNC(STEP_TRIGGER_POINT_POWER_ON_BEFORE_GET_CONNSYS_ID);

		if (wmt_consys_ic_ops->polling_consys_ic_chipid)
			wmt_consys_ic_ops->polling_consys_ic_chipid();
		if (wmt_consys_ic_ops->update_consys_rom_desel_value)
			wmt_consys_ic_ops->update_consys_rom_desel_value();
		if (wmt_consys_ic_ops->consys_ic_acr_reg_setting)
			wmt_consys_ic_ops->consys_ic_acr_reg_setting();
		if (wmt_consys_ic_ops->consys_ic_afe_reg_setting)
			wmt_consys_ic_ops->consys_ic_afe_reg_setting();
		if (wmt_consys_ic_ops->consys_ic_hw_reset_bit_set)
			wmt_consys_ic_ops->consys_ic_hw_reset_bit_set(DISABLE);
#endif
	return 0;
}

int consys_hw_wifi_power_ctl(unsigned int enable)
{
	return 0;
}

int consys_hw_bt_power_ctl(unsigned int enable)
{
	return 0;
}

int consys_hw_gps_power_ctl(unsigned int enable)
{
	return 0;
}

int consys_hw_fm_power_ctl(unsigned int enable)
{
	return 0;
}

int mtk_conninfra_probe(struct platform_device *pdev)
{
	int ret = -1;

	/* emi mng init */
	ret = emi_mng_init();
	if (ret) {
		pr_err("emi_mng init fail, %d\n", ret);
		return -1;
	}

	ret = pmic_mng_init(pdev);
	if (ret) {
		pr_err("pmic_mng init fail, %d\n", ret);
		return -2;
	}

	if (pdev)
		g_pdev = pdev;

	if (consys_hw_ops->consys_plt_read_reg_from_dts)
		consys_hw_ops->consys_plt_read_reg_from_dts(pdev);
	else {
		pr_err("consys_plt_read_reg_from_dts fail");
		return -3;
	}

	if (consys_hw_ops->consys_plt_clk_get_from_dts)
		consys_hw_ops->consys_plt_clk_get_from_dts(pdev);
	else {
		pr_err("consys_plt_clk_get_from_dtsfail");
		return -4;
	}

#if 0
	if (wmt_consys_ic_ops->consys_ic_clk_get_from_dts)
		iRet = wmt_consys_ic_ops->consys_ic_clk_get_from_dts(pdev);
	else
		iRet = -1;

	if (iRet)
		return iRet;

	if (gConEmiPhyBase) {
		pConnsysEmiStart = ioremap_nocache(gConEmiPhyBase, gConEmiSize);
		pr_info("Clearing Connsys EMI (virtual(0x%p) physical(0x%pa)) %llu bytes\n",
				   pConnsysEmiStart, &gConEmiPhyBase, gConEmiSize);
		memset_io(pConnsysEmiStart, 0, gConEmiSize);
		iounmap(pConnsysEmiStart);
		pConnsysEmiStart = NULL;

		if (wmt_consys_ic_ops->consys_ic_emi_mpu_set_region_protection)
			wmt_consys_ic_ops->consys_ic_emi_mpu_set_region_protection();
		if (wmt_consys_ic_ops->consys_ic_emi_set_remapping_reg)
			wmt_consys_ic_ops->consys_ic_emi_set_remapping_reg();
		if (wmt_consys_ic_ops->consys_ic_emi_coredump_remapping)
			wmt_consys_ic_ops->consys_ic_emi_coredump_remapping(&pEmibaseaddr, 1);
		if (wmt_consys_ic_ops->consys_ic_dedicated_log_path_init)
			wmt_consys_ic_ops->consys_ic_dedicated_log_path_init(pdev);
	} else {
		pr_err("consys emi memory address gConEmiPhyBase invalid\n");
	}

#ifdef CONFIG_MTK_HIBERNATION
	pr_info("register connsys restore cb for complying with IPOH function\n");
	register_swsusp_restore_noirq_func(ID_M_CONNSYS, mtk_wcn_consys_hw_restore, NULL);
#endif

	if (wmt_consys_ic_ops->ic_bt_wifi_share_v33_spin_lock_init)
		wmt_consys_ic_ops->ic_bt_wifi_share_v33_spin_lock_init();


	if (wmt_consys_ic_ops->consys_ic_pmic_get_from_dts)
		wmt_consys_ic_ops->consys_ic_pmic_get_from_dts(pdev);

	consys_pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(consys_pinctrl)) {
		pr_err("cannot find consys pinctrl.\n");
		consys_pinctrl = NULL;
	}


	if (wmt_consys_ic_ops->consys_ic_store_reset_control)
		wmt_consys_ic_ops->consys_ic_store_reset_control(pdev);
#endif
	return 0;
}

int mtk_conninfra_remove(struct platform_device *pdev)
{
#if 0
	if (wmt_consys_ic_ops->consys_ic_need_store_pdev) {
		if (wmt_consys_ic_ops->consys_ic_need_store_pdev() == MTK_WCN_BOOL_TRUE)
			pm_runtime_disable(&pdev->dev);
	}

	if (wmt_consys_ic_ops->consys_ic_dedicated_log_path_deinit)
		wmt_consys_ic_ops->consys_ic_dedicated_log_path_deinit();
	if (wmt_consys_ic_ops->consys_ic_emi_coredump_remapping)
		wmt_consys_ic_ops->consys_ic_emi_coredump_remapping(&pEmibaseaddr, 0);
#endif
	if (g_pdev)
		g_pdev = NULL;

	return 0;
}

int mtk_conninfra_suspend(struct platform_device *pdev, pm_message_t state)
{
	//WMT_STEP_DO_ACTIONS_FUNC(STEP_TRIGGER_POINT_WHEN_AP_SUSPEND);

	return 0;
}

int mtk_conninfra_resume(struct platform_device *pdev)
{
	//WMT_STEP_DO_ACTIONS_FUNC(STEP_TRIGGER_POINT_WHEN_AP_RESUME);

	//if (wmt_consys_ic_ops->consys_ic_resume_dump_info)
	//	wmt_consys_ic_ops->consys_ic_resume_dump_info();

	return 0;
}


int consys_hw_init(void)
{
	int iRet = 0;

	if (consys_hw_ops == NULL)
		consys_hw_ops = get_consys_platform_ops();

	iRet = platform_driver_register(&mtk_conninfra_dev_drv);
	if (iRet)
		pr_err("Conninfra platform driver registered failed(%d)\n", iRet);

	pr_info("[consys_hw_init] result [%d]\n", iRet);
	return iRet;
}

int consys_hw_deinit(void)
{
	platform_driver_unregister(&mtk_conninfra_dev_drv);
	return 0;
}
