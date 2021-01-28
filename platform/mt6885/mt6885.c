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
#include "consys_hw_util.h"
#include "mt6885.h"
#include "emi_mng.h"
#include "mt6885_emi.h"

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
static int consys_read_reg_from_dts(struct platform_device *pdev);

static int consys_clock_buffer_ctrl(unsigned int enable);
//static int consys_co_clock_type(void);

//static void consys_sw_reset_bit_set(unsigned int enable);
static int consys_conninfra_on_power_ctrl(unsigned int enable);
//static void consys_hw_axi_bus_enable(unsigned int enable);
static void consys_set_if_pinmux(unsigned int enable);
static int consys_polling_chipid(void);

//static void consys_afe_reg_setting(void);

static unsigned int consys_soc_chipid_get(void);

static int consys_check_reg_readable(void);
static void consys_clock_fail_dump(void);

static unsigned int consys_read_cpupcr(void);
static void consys_resume_dump_info(void);
static void consys_set_pdma_axi_rready_force_high(unsigned int enable);

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
CONSYS_HW_OPS g_consys_hw_ops = {
	/* load from dts */
	.consys_plt_clk_get_from_dts = consys_clk_get_from_dts,
	.consys_plt_read_reg_from_dts = consys_read_reg_from_dts,

	/* clock */
	.consys_plt_clock_buffer_ctrl = consys_clock_buffer_ctrl,
	//.consys_plt_co_clock_type = consys_co_clock_type,

	/* POS */
	.consys_plt_conninfra_on_power_ctrl = consys_conninfra_on_power_ctrl,
	.consys_plt_set_if_pinmux = consys_set_if_pinmux,

	.consys_plt_polling_consys_chipid = consys_polling_chipid,
	//.consys_plt_afe_reg_setting = consys_afe_reg_setting,

	.consys_plt_soc_chipid_get = consys_soc_chipid_get,

	/* debug */
	.consys_plt_check_reg_readable = consys_check_reg_readable,
	.consys_plt_clock_fail_dump = consys_clock_fail_dump,
	.consys_plt_cread_cpupcr = consys_read_cpupcr,
	/* debug, used by STEP */
	//.consys_plt_is_connsys_reg;

	.consys_plt_resume_dump_info = consys_resume_dump_info,

	/* for reset */
	.consys_plt_set_pdma_axi_rready_force_high = consys_set_pdma_axi_rready_force_high,
};


struct clk *clk_scp_conn_main;	/*ctrl conn_power_on/off */
struct CONSYS_BASE_ADDRESS conn_reg;

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
P_CONSYS_HW_OPS get_consys_platform_ops(void)
{
	return &g_consys_hw_ops;
}


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
int consys_read_reg_from_dts(struct platform_device *pdev)
{
	int iRet = -1;
	struct device_node *node = NULL;

	node = pdev->dev.of_node;
	pr_info("[%s] node=[%p]\n", __func__, node);
	if (node) {
		/* registers base address */
		conn_reg.conn_infra_rgu =
			(size_t) of_iomap(node, CONN_INFRA_RGU_BASE_INDEX);
		conn_reg.conn_infra_cfg =
			(size_t) of_iomap(node, CONN_INFRA_CFG_BASE_INDEX);
		conn_reg.conn_host_csr_top_base =
			(size_t) of_iomap(node, CONN_HOST_CSR_TOP_BASE_INDEX);
		pr_info("Get conn_infra_rgu(0x%zx) conn_cfg(0x%zx) conn_host_csr_top(0x%zx)",
			conn_reg.conn_infra_rgu,
			conn_reg.conn_infra_cfg,
			conn_reg.conn_host_csr_top_base);

		conn_reg.infracfg_ao =
			(size_t) of_iomap(node, INFRACFG_AO_BASE_INDEX);
		conn_reg.toprgu_base =
			(size_t) of_iomap(node, TOPRGU_BASE_INDEX);
		conn_reg.spm_base = 0;
		//	(size_t) of_iomap(node, SPM_BASE_INDEX);
		pr_info("Get infracfg_ao(0x%zx) toprgu(0x%zx) spm(0x%zx)",
			conn_reg.infracfg_ao,
			conn_reg.toprgu_base,
			conn_reg.spm_base);
	} else {
		pr_err("[%s] can't find CONSYS compatible node\n", __func__);
		return iRet;
	}
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

#if 0
void consys_sw_reset_bit_set(unsigned int enable)
{
	unsigned int consys_ver_id = 0;
	unsigned int cnt = 0;
	unsigned int pre_ver_id = 0xFFFFFFFF;

	if (enable) {
		/*3.assert CONNSYS CPU SW reset  0x10007018 "[12]=1'b1  [31:24]=8'h88 (key)" */
		CONSYS_REG_WRITE((conn_reg.ap_rgu_base + CONSYS_CPU_SW_RST_OFFSET),
				CONSYS_REG_READ(conn_reg.ap_rgu_base + CONSYS_CPU_SW_RST_OFFSET) |
				CONSYS_CPU_SW_RST_BIT | CONSYS_CPU_SW_RST_CTRL_KEY);
	} else {
		/*16.deassert CONNSYS CPU SW reset 0x10007018 "[12]=1'b0 [31:24] =8'h88 (key)" */
		CONSYS_REG_WRITE(conn_reg.ap_rgu_base + CONSYS_CPU_SW_RST_OFFSET,
				(CONSYS_REG_READ(conn_reg.ap_rgu_base + CONSYS_CPU_SW_RST_OFFSET) &
				 ~CONSYS_CPU_SW_RST_BIT) | CONSYS_CPU_SW_RST_CTRL_KEY);

		consys_ver_id = CONSYS_REG_READ(conn_reg.mcu_base + 0x600);
		while (consys_ver_id != 0x1D1E) {
			if (cnt > 10)
				break;
			consys_ver_id = CONSYS_REG_READ(conn_reg.mcu_base + 0x600);
			if (pre_ver_id != consys_ver_id) {
				pre_ver_id = consys_ver_id;
				pr_info("0x18002600(0x%x), 0x1800216c(0x%x), 0x18007104(0x%x)\n",
						consys_ver_id, CONSYS_REG_READ(conn_reg.mcu_base + 0x16c),
						CONSYS_REG_READ(conn_reg.mcu_conn_hif_on_base + CONSYS_CPUPCR_OFFSET));
			}
			msleep(20);
			cnt++;
		}
	}

}
#endif

int consys_conninfra_on_power_ctrl(unsigned int enable)
{
	int check;
	if (enable) {
		/* Turn on SPM clock (apply this for SPM's CONNSYS power control related CR accessing)
		 * address: 0x1000_6000[0]
		 *          0x1000_6000[31:16]
		 * Data: [0]=1'b1
		 *       [31:16]=16'h0b16 (key)
		 * Action: write
		 */

		/* Assert "conn_infra_on" primary part power on, set "connsys_on_domain_pwr_on"=1
		 * Address: 0x1000_6304[2]
		 * Data: 1'b1
		 * Action: write
		 */

		/* Check "conn_infra_on" primary part power status, check "connsys_on_domain_pwr_ack"=1
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_616C[1]
		 * Data: 1'b1
		 * Action: polling
		 */

		/* Assert "conn_infra_on" secondary part power on, set "connsys_on_domain_pwr_on_s"=1
		 * Address: 0x1000_6304[3]
		 * Data: 1'b1
		 * Action: write
		 */

		/* Check "conn_infra_on" secondary part power status,
		 * check "connsys_on_domain_pwr_ack_s"=1
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_6170[1]
		 * Data: 1'b1
		 * Action: polling
		 */

		/* Turn on AP-to-CONNSYS bus clock, set "conn_clk_dis"=0
		 * (apply this for bus clock toggling)
		 * Address: 0x1000_6304[4]
		 * Data: 1'b0
		 * Action: write
		 */

		/* Wait 1 us */

		/* De-assert "conn_infra_on" isolation, set "connsys_iso_en"=0
		 * Address: 0x1000_6304[1]
		 * Data: 1'b0
		 * Action: write
		 */

		/* De-assert CONNSYS S/W reset (TOP RGU CR),
		 * set "ap_sw_rst_b"=1
		 * Address: WDT_SWSYSRST[9] (0x1000_7018[9])
		 *          WDT_SWSYSRST[31:24] (0x1000_7018[31:24])
		 * Data: [9]=1'b0
		 *       [31:24]=8'h88 (key)
		 * Action: Write
		 */

		/* De-assert CONNSYS S/W reset (SPM CR), set "ap_sw_rst_b"=1
		 * Address: CONN_PWR_CON[0] (0x1000_6304[0])
		 * Data: 1'b1
		 * Action: write
		 */

		/* Wait 0.5ms  */


		/* Disable AXI bus sleep protect */
		/* Turn off AXI RX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 * Address: 0x1000_1718[31:0] (INFRA_TOPAXI_PROTECTEN2_CLR)
		 * Data: 0x0000_0002
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_CLR_OFFSET,
			0x00000002);

		/* Step 43: Check AHB RX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 0, 10, 500, check);
		if (check != 0)
			pr_err("Polling AHB RX bus sleep protect turn off fail. status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET));

		/* Turn off AXI Rx bus sleep protect (CONN2AP AXI Rx Bus protect)
		 * (disable sleep protection when CONNSYS had been turned on)
		 * Note : Should turn off AHB Rx sleep protection first.
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00004000);
		/* Step 45. Check AXI Rx bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[14] (INFRA_TOPAXI_PROTECTEN_STA1[14])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			14, 0, 10, 50, check);
		if (check != 0)
			pr_err("Polling AXI bus sleep protect turn off fail. Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET));

		/* Turn off AHB TX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00002000);

		/* Step 49. Check AHB TX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[13] (INFRA_TOPAXI_PROTECTEN_STA1[13])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			13, 0, 10, 500, check);
		if (check != 0)
			pr_err("polling AHB TX bus sleep protect turn off fail. Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET));
	} else {

		/* Enable AXI bus sleep protect */

		/* Turn on AXI TX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Address: 0x1000_12a0[31:0]
		 * Data: 0x0000_2000
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00002000);

		/* check AHB TX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1228[13]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			13, 1, 0, 500, check);
		if (check)
			pr_err("Polling AHB TX bus sleep protect turn on fail.");

		/* Turn on AXI Rx bus sleep protect (CONN2AP AXI RX Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Note:
		 *	Should turn on AXI Rx sleep protection after
		 *	AXI Tx sleep protection has been turn on.
		 * Address: 0x1000_12A0[31:0]
		 * Data: 0x0000_4000
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00004000);

		/* check AXI Rx bus sleep protect turn on
		 * (polling "100 times", polling interval is 1ms)
		 * Address: 0x1000_1228[14]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			14, 1, 10, 1000, check);
		if (check)
			pr_err("Polling AXI Rx bus sleep protect turn on fail.");

		/* Turn on AXI RX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Address: 0x1000_1714[31:0] (INFRA_TOPAXI_PROTECTEN2_SET)
		 * Data: 0x0000_0002
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_SET_OFFSET,
			0x00000002);
		/* check AHB RX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Value: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 1, 10, 0, check);
		if (check)
			pr_err("Polling AHB RX bus sleep protect turn on fail.");
	}
	return 0;
}

void consys_set_if_pinmux(unsigned int enable)
{
#if 0
	unsigned char *consys_if_pinmux_reg_base = NULL;
	unsigned char *consys_if_pinmux_driving_base = NULL;

	/* Switch D die pinmux for connecting A die */
	consys_if_pinmux_reg_base = ioremap_nocache(CONSYS_IF_PINMUX_REG_BASE, 0x1000);
	if (!consys_if_pinmux_reg_base) {
		pr_err("consys_if_pinmux_reg_base(%x) ioremap fail\n",
				CONSYS_IF_PINMUX_REG_BASE);
		return;
	}

	consys_if_pinmux_driving_base = ioremap_nocache(CONSYS_IF_PINMUX_DRIVING_BASE, 0x100);
	if (!consys_if_pinmux_driving_base) {
		pr_err("consys_if_pinmux_driving_base(%x) ioremap fail\n",
				CONSYS_IF_PINMUX_DRIVING_BASE);
		if (consys_if_pinmux_reg_base)
			iounmap(consys_if_pinmux_reg_base);
		return;
	}

	if (enable) {
		CONSYS_REG_WRITE(consys_if_pinmux_reg_base + CONSYS_IF_PINMUX_01_OFFSET,
				(CONSYS_REG_READ(consys_if_pinmux_reg_base +
				CONSYS_IF_PINMUX_01_OFFSET) &
				CONSYS_IF_PINMUX_01_MASK) | CONSYS_IF_PINMUX_01_VALUE);
		CONSYS_REG_WRITE(consys_if_pinmux_reg_base + CONSYS_IF_PINMUX_02_OFFSET,
				(CONSYS_REG_READ(consys_if_pinmux_reg_base +
				CONSYS_IF_PINMUX_02_OFFSET) &
				CONSYS_IF_PINMUX_02_MASK) | CONSYS_IF_PINMUX_02_VALUE);
		/* set pinmux driving to 2mA */
		CONSYS_REG_WRITE(consys_if_pinmux_driving_base + CONSYS_IF_PINMUX_DRIVING_OFFSET,
				(CONSYS_REG_READ(consys_if_pinmux_driving_base +
				CONSYS_IF_PINMUX_DRIVING_OFFSET) &
				CONSYS_IF_PINMUX_DRIVING_MASK) | CONSYS_IF_PINMUX_DRIVING_VALUE);
	} else {
		CONSYS_REG_WRITE(consys_if_pinmux_reg_base + CONSYS_IF_PINMUX_01_OFFSET,
				CONSYS_REG_READ(consys_if_pinmux_reg_base +
				CONSYS_IF_PINMUX_01_OFFSET) & CONSYS_IF_PINMUX_01_MASK);
		CONSYS_REG_WRITE(consys_if_pinmux_reg_base + CONSYS_IF_PINMUX_02_OFFSET,
				CONSYS_REG_READ(consys_if_pinmux_reg_base +
				CONSYS_IF_PINMUX_02_OFFSET) & CONSYS_IF_PINMUX_02_MASK);
	}

	if (consys_if_pinmux_reg_base)
		iounmap(consys_if_pinmux_reg_base);
	if (consys_if_pinmux_driving_base)
		iounmap(consys_if_pinmux_driving_base);
#endif
}

#if 0
void consys_hw_axi_bus_enable(unsigned int enable)
{
	int check;

	if (enable) {
		/* Turn off AXI RX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 * Address: 0x1000_1718[31:0] (INFRA_TOPAXI_PROTECTEN2_CLR)
		 * Data: 0x0000_0002
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_CLR_OFFSET,
			0x00000002);

		/* Step 43: Check AHB RX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 0, 10, 500, check);
		if (check != 0)
			pr_err("Polling AHB RX bus sleep protect turn off fail.");

		/* Turn off AXI Rx bus sleep protect (CONN2AP AXI Rx Bus protect)
		 * (disable sleep protection when CONNSYS had been turned on)
		 * Note : Should turn off AHB Rx sleep protection first.
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00004000);
		/* Step 45. Check AXI Rx bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[14] (INFRA_TOPAXI_PROTECTEN_STA1[14])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			14, 0, 10, 50, check);
		if (check != 0)
			pr_err("Polling AXI bus sleep protect turn off fail.");

		/* Turn off AHB TX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00002000);

		/* Step 49. Check AHB TX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[13] (INFRA_TOPAXI_PROTECTEN_STA1[13])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			13, 0, 10, 500, check);
		if (check != 0)
			pr_err("polling AHB TX bus sleep protect turn off fail.");
	} else {
		/* Turn on AXI TX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Address: 0x1000_12a0[31:0]
		 * Data: 0x0000_2000
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00002000);

		/* check AHB TX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1228[13]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			13, 1, 0, 500, check);
		if (check)
			pr_err("Polling AHB TX bus sleep protect turn on fail.");

		/* Turn on AXI Rx bus sleep protect (CONN2AP AXI RX Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Note:
		 *	Should turn on AXI Rx sleep protection after
		 *	AXI Tx sleep protection has been turn on.
		 * Address: 0x1000_12A0[31:0]
		 * Data: 0x0000_4000
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00004000);

		/* check AXI Rx bus sleep protect turn on
		 * (polling "100 times", polling interval is 1ms)
		 * Address: 0x1000_1228[14]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			14, 1, 10, 1000, check);
		if (check)
			pr_err("Polling AXI Rx bus sleep protect turn on fail.");

		/* Turn on AXI RX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AXI bus protection to prevent bus hang when
		 * CONNSYS had been turned off)
		 * Address: 0x1000_1714[31:0] (INFRA_TOPAXI_PROTECTEN2_SET)
		 * Data: 0x0000_0002
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_SET_OFFSET,
			0x00000002);
		/* check AHB RX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Value: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 1, 10, 0, check);
		if (check)
			pr_err("Polling AHB RX bus sleep protect turn on fail.");
	}
}
#endif

int consys_polling_chipid(void)
{
	unsigned int retry = 10;
	unsigned int consys_hw_ver = 0;
	unsigned int consys_configuration_id = 0;
	int ret = -1;

	while (retry-- > 0) {
		consys_hw_ver = CONSYS_REG_READ(
					conn_reg.conn_infra_cfg +
					CONN_HW_VER_OFFSET);
		if (consys_hw_ver == CONN_HW_VER) {
			consys_configuration_id = CONSYS_REG_READ(
				conn_reg.conn_infra_cfg + CONN_CFG_ID_OFFSET);
			pr_info("Consys HW version id(0x%x) cfg_id=(0x%x)\n",
				consys_hw_ver, consys_configuration_id);
			ret = 0;
			/* !!!!!!!!!!!!!!! for debug !!!!!!!!!!!!!!!!!! */
			pr_info("AXI RX(%x) AHB RX (%x) AHB TX (%x)",
				CONSYS_REG_READ_BIT(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET, 0x1 << 14) >> 14,
				CONSYS_REG_READ_BIT(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET, 0x1 << 2) >> 2,
				CONSYS_REG_READ_BIT(conn_reg.infracfg_ao + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET, 0x1 << 13) >> 13);
			break;
		}
		pr_err("Read CONSYS version id(0x%08x), retry countdown(%d)",
			consys_hw_ver, retry);
		msleep(20);
	}

	/* !!!!!!!!!!!!!!!!!!!For FPGA workaround start!!!!!!!!!!!!!!!!!!!!!! */
	CONSYS_SET_BIT(conn_reg.conn_infra_cfg + 0x0c04,
		((0x1 << 1) | (0x1 << 9) | (0x1 << 17) | (0x1 << 25)));
	pr_info("Check %x\n", CONSYS_REG_READ(conn_reg.conn_infra_cfg + 0x0c04));
	/* !!!!!!!!!!!!!!!!!!!For FPGA workaround end!!!!!!!!!!!!!!!!!!!!!! */

	return ret;
}

unsigned int consys_soc_chipid_get(void)
{
	return PLATFORM_SOC_CHIP;
}

int consys_check_reg_readable(void)
{
	int flag = 0;
#if 0
	UINT32 value = 0;
	P_DEV_WMT pDev = &gDevWmt;

	if (osal_test_bit(WMT_STAT_PWR, &pDev->state)) {
		/*check connsys clock and sleep status*/
		CONSYS_REG_WRITE(conn_reg.mcu_conn_hif_on_base, CONSYS_CLOCK_CHECK_VALUE);
		udelay(1000);
		value = CONSYS_REG_READ(conn_reg.mcu_conn_hif_on_base);
		if ((value & CONSYS_HCLK_CHECK_BIT) &&
		    (value & CONSYS_OSCCLK_CHECK_BIT))
			flag = 1;
	}

	if (!flag)
		pr_err("connsys clock check fail 0x18007000(0x%x)\n", value);
#endif
	return flag;
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

void consys_set_pdma_axi_rready_force_high(unsigned int enable)
{
}

