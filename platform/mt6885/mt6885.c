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

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/memblock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>

#include <connectivity_build_in_adapter.h>

#include "osal.h"
#include "consys_hw.h"
#include "consys_reg_util.h"
#include "mt6885.h"
#include "emi_mng.h"
#include "mt6885_emi.h"
#include "mt6885_consys_reg.h"
#include "mt6885_pos.h"

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define CONSYS_PWR_SPM_CTRL 1
#define PLATFORM_SOC_CHIP 0x6885

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

static int consys_clk_get_from_dts(struct platform_device *pdev);
static int consys_clock_buffer_ctrl(unsigned int enable);
static unsigned int consys_soc_chipid_get(void);
static void consys_clock_fail_dump(void);

static unsigned int consys_read_cpupcr(void);
static void consys_resume_dump_info(void);
//static void consys_set_pdma_axi_rready_force_high(unsigned int enable);

//static int consys_co_clock_type(void);
//static void consys_sw_reset_bit_set(unsigned int enable);
//static void consys_hw_axi_bus_enable(unsigned int enable);
//static void consys_afe_reg_setting(void);


/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
struct consys_hw_ops_struct g_consys_hw_ops = {
	/* load from dts */
	/* TODO: mtcmos should move to a independent module */
	.consys_plt_clk_get_from_dts = consys_clk_get_from_dts,

	/* clock */
	.consys_plt_clock_buffer_ctrl = consys_clock_buffer_ctrl,
	//.consys_plt_co_clock_type = consys_co_clock_type,

	/* POS */
	.consys_plt_conninfra_on_power_ctrl = consys_conninfra_on_power_ctrl,
	.consys_plt_set_if_pinmux = consys_set_if_pinmux,

	.consys_plt_polling_consys_chipid = consys_polling_chipid,
	.consys_plt_d_die_cfg = connsys_d_die_cfg,
	.consys_plt_spi_master_cfg = connsys_spi_master_cfg,
	.consys_plt_a_die_cfg = connsys_a_die_cfg,
	.consys_plt_afe_wbg_cal = connsys_afe_wbg_cal,
	.consys_plt_low_power_setting = connsys_low_power_setting,
	.consys_plt_soc_chipid_get = consys_soc_chipid_get,

	/* debug */
	.consys_plt_clock_fail_dump = consys_clock_fail_dump,
	.consys_plt_cread_cpupcr = consys_read_cpupcr,
	/* debug, used by STEP */
	//.consys_plt_is_connsys_reg;

	.consys_plt_resume_dump_info = consys_resume_dump_info,

	/* for reset */
	//.consys_plt_set_pdma_axi_rready_force_high = consys_set_pdma_axi_rready_force_high,
};


struct clk *clk_scp_conn_main;	/*ctrl conn_power_on/off */

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
struct consys_hw_ops_struct* get_consys_platform_ops(void)
{
	return &g_consys_hw_ops;
}

/* mtcmos contorl */
int consys_clk_get_from_dts(struct platform_device *pdev)
{
	clk_scp_conn_main = devm_clk_get(&pdev->dev, "conn");
	if (IS_ERR(clk_scp_conn_main)) {
		pr_err("[CCF]cannot get clk_scp_conn_main clock.\n");
		return PTR_ERR(clk_scp_conn_main);
	}
	pr_debug("[CCF]clk_scp_conn_main=%p\n", clk_scp_conn_main);

	return 0;
}

int consys_clock_buffer_ctrl(unsigned int enable)
{
#if 0
	if (enable)
		KERNEL_clk_buf_ctrl(CLK_BUF_CONN, true);	/*open XO_WCN*/
	else
		KERNEL_clk_buf_ctrl(CLK_BUF_CONN, false);	/*close XO_WCN*/
#endif
	return 0;
}



unsigned int consys_soc_chipid_get(void)
{
	return PLATFORM_SOC_CHIP;
}

void consys_clock_fail_dump(void)
{
}

unsigned int consys_read_cpupcr(void)
{
	//return CONSYS_REG_READ(conn_reg.mcu_conn_hif_on_base + CONSYS_CPUPCR_OFFSET);
	return 0;
}

void consys_resume_dump_info(void)
{
#if 0
	if (conn_reg.mcu_cfg_on_base != 0 &&
	    conn_reg.mcu_top_misc_on_base != 0 &&
	    mtk_consys_check_reg_readable()) {
		stp_dbg_clear_cpupcr_reg_info();
		stp_dbg_poll_cpupcr(5, 0, 1);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_HOST_MAILBOX_MCU_ADDR, 0x1);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_MON_CTL_ADDR, 0x80000001);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_MON_SEL0_ADDR, 0x03020100);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_MON_SEL1_ADDR, 0x07060504);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_MON_SEL2_ADDR, 0x0b0a0908);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_MON_SEL3_ADDR, 0x0f0e0d0c);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_DBGSEL_ADDR, 0x3);
		g_connsys_lp_dump_info[0] = (UINT32)CONN_CFG_ON_CONN_ON_MON_FLAG_RECORD_MAPPING_AP_ADDR;
		g_connsys_lp_dump_info[1] = CONSYS_REG_READ(CONN_CFG_ON_CONN_ON_MON_FLAG_RECORD_ADDR);
		pr_info("0x%08x: 0x%x\n", g_connsys_lp_dump_info[0], g_connsys_lp_dump_info[1]);
		CONSYS_REG_WRITE(CONN_CFG_ON_CONN_ON_HOST_MAILBOX_MCU_ADDR, 0x0);
		return &g_connsys_lp_dump_info[0];
	}
#endif
}


