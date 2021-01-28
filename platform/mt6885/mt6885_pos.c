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
/* platform dependent */
#include "plat_def.h"
/* macro for read/write cr */
#include "consys_reg_util.h"
/* cr base address */
#include "mt6885_consys_reg.h"
/* cr offset */
#include "mt6885_consys_reg_offset.h"


unsigned int consys_emi_set_remapping_reg(unsigned int con_emi_base_addr)
{
	/* For direct path */
	//phys_addr_t mdPhy = 0;
	//int size = 0;

	pr_info("[%s]", __func__);

	/* EMI Registers remapping */
	CONSYS_REG_WRITE_OFFSET_RANGE(CON_REG_HOST_CSR_ADDR + CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET,
					  con_emi_base_addr, 0, 16, 20);
	pr_info("CONSYS_EMI_MAPPING dump in restore cb(0x%08x)\n",
			CONSYS_REG_READ(CON_REG_HOST_CSR_ADDR + CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET));

	CONSYS_REG_WRITE_MASK(
		CON_REG_HOST_CSR_ADDR + CONN2AP_REMAP_WF_PERI_BASE_ADDR_OFFSET,
		0x01000, 0xFFFFF);
	CONSYS_REG_WRITE_MASK(
		CON_REG_HOST_CSR_ADDR + CONN2AP_REMAP_BT_PERI_BASE_ADDR_OFFSET,
		0x01000, 0xFFFFF);
	CONSYS_REG_WRITE_MASK(
		CON_REG_HOST_CSR_ADDR + CONN2AP_REMAP_GPS_PERI_BASE_ADDR_OFFSET,
		0x01000, 0xFFFFF);
#if 0
	/*Perisys Configuration Registers remapping*/
	CONSYS_REG_WRITE_OFFSET_RANGE(conn_reg.topckgen_base + CONSYS_EMI_PERI_MAPPING_OFFSET,
					  0x10003000, 0, 16, 20);
	pr_info("PERISYS_MAPPING dump in restore cb(0x%08x)\n",
			CONSYS_REG_READ(conn_reg.topckgen_base + CONSYS_EMI_PERI_MAPPING_OFFSET));

	/*Modem Configuration Registers remapping*/
	mdPhy = get_smem_phy_start_addr(MD_SYS1, SMEM_USER_RAW_MD_CONSYS, &size);
	if (size == 0)
		pr_info("MD direct path is not supported\n");
	else {
		CONSYS_REG_WRITE_OFFSET_RANGE(
			conn_reg.topckgen_base + CONSYS_EMI_AP_MD_OFFSET,
			mdPhy, 0, 16, 20);
		pr_info("MD_MAPPING dump in restore cb(0x%08x)\n",
			CONSYS_REG_READ(conn_reg.topckgen_base + CONSYS_EMI_AP_MD_OFFSET));
	}
	mtk_wcn_emi_addr_info.emi_direct_path_ap_phy_addr = mdPhy;
	mtk_wcn_emi_addr_info.emi_direct_path_size = size;
#endif
	return 0;
}

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
		pr_info("Before write: 0x%08x\n", CONSYS_REG_READ(CON_REG_SPM_BASE_ADDR + SPM_POWERON_CONFIG_EN));
		CONSYS_REG_WRITE_MASK(
			CON_REG_SPM_BASE_ADDR + SPM_POWERON_CONFIG_EN, 0x0b160001, 0xffff0001);
		pr_info("After write: 0x%08x\n", CONSYS_REG_READ(CON_REG_SPM_BASE_ADDR + SPM_POWERON_CONFIG_EN));

		/* Turn on ap2conn host_ck CG (ECO)
		 * Address: INFRA_AP2MD_GALS_CTL[0] (0x1020E504[0])
		 * Value: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_INFRACFG_BASE_ADDR + INFRA_AP2MD_GALS_CTL, 0x1);

		/* Assert "conn_infra_on" primary part power on, set "connsys_on_domain_pwr_on"=1
		 * Address: 0x1000_6304[2]
		 * Data: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x4);
		/* Check "conn_infra_on" primary part power status, check "connsys_on_domain_pwr_ack"=1
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_616C[1]
		 * Data: 1'b1
		 * Action: polling
		 */
		check = 0;
		CONSYS_REG_BIT_POLLING(CON_REG_SPM_BASE_ADDR + SPM_PWR_STATUS, 1, 1, 500, 10, check);
		if (check != 0)
			pr_err("Check conn_infra_on primary power fail. 0x1000_616C is 0x%08x. Expect [1] as 1.\n",
				CONSYS_REG_READ(CON_REG_SPM_BASE_ADDR + SPM_PWR_STATUS));
		/* Assert "conn_infra_on" secondary part power on, set "connsys_on_domain_pwr_on_s"=1
		 * Address: 0x1000_6304[3]
		 * Data: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x8);
		/* Check "conn_infra_on" secondary part power status,
		 * check "connsys_on_domain_pwr_ack_s"=1
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_6170[1]
		 * Data: 1'b1
		 * Action: polling
		 */
		check = 0;
		CONSYS_REG_BIT_POLLING(CON_REG_SPM_BASE_ADDR + SPM_PWR_STATUS_2ND, 1, 1, 500, 10, check);
		if (check != 0)
			pr_err("Check conn_infra_on secondary power fail. 0x1000_6170 is 0x%08x. Expect [1] as 1.\n",
				CONSYS_REG_READ(CON_REG_SPM_BASE_ADDR + SPM_PWR_STATUS_2ND));
		/* Turn on AP-to-CONNSYS bus clock, set "conn_clk_dis"=0
		 * (apply this for bus clock toggling)
		 * Address: 0x1000_6304[4]
		 * Data: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x10);

		/* Wait 1 us */
		udelay(1);

		/* De-assert "conn_infra_on" isolation, set "connsys_iso_en"=0
		 * Address: 0x1000_6304[1]
		 * Data: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x2);

		/* De-assert CONNSYS S/W reset (TOP RGU CR),
		 * set "ap_sw_rst_b"=1
		 * Address: WDT_SWSYSRST[9] (0x1000_7018[9])
		 *          WDT_SWSYSRST[31:24] (0x1000_7018[31:24])
		 * Data: [9]=1'b0
		 *       [31:24]=8'h88 (key)
		 * Action: Write
		 */
		CONSYS_REG_WRITE_MASK(
			CON_REG_TOP_RGU_ADDR + TOP_RGU_WDT_SWSYSRST,0x88000000, 0xff000200);

		/* De-assert CONNSYS S/W reset (SPM CR), set "ap_sw_rst_b"=1
		 * Address: CONN_PWR_CON[0] (0x1000_6304[0])
		 * Data: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x1);

		/* Wait 0.5ms  */
		udelay(500);

		/* Disable AXI bus sleep protect */
		/* Turn off AXI RX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 * Address: 0x1000_1718[31:0] (INFRA_TOPAXI_PROTECTEN2_CLR)
		 * Data: 0x0000_0002
		 * Action: write
		 */
		CONSYS_REG_WRITE(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_CLR_OFFSET,
			0x00000002);

		/* Step 43: Check AHB RX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Data: 1'b0
		 * Action: polling
		 */
		check = 0;
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 0, 10, 500, check);
		if (check != 0)
			pr_err("Polling AHB RX bus sleep protect turn off fail. status=0x%08x\n",
				CONSYS_REG_READ(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET));

		/* Turn off AXI Rx bus sleep protect (CONN2AP AXI Rx Bus protect)
		 * (disable sleep protection when CONNSYS had been turned on)
		 * Note : Should turn off AHB Rx sleep protection first.
		 */
		CONSYS_REG_WRITE(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00004000);
		/* Step 45. Check AXI Rx bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[14] (INFRA_TOPAXI_PROTECTEN_STA1[14])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			14, 0, 10, 50, check);
		if (check != 0)
			pr_err("Polling AXI bus sleep protect turn off fail. Status=0x%08x\n",
				CONSYS_REG_READ(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET));

		/* Turn off AHB TX bus sleep protect (AP2CONN AHB Bus protect)
		 * (apply this for INFRA AHB bus accessing when CONNSYS had been turned on)
		 */
		CONSYS_REG_WRITE(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_CLR_OFFSET,
			0x00002000);

		/* Step 49. Check AHB TX bus sleep protect turn off
		 * (polling "10 times" and each polling interval is "0.5ms")
		 * Address: 0x1000_1228[13] (INFRA_TOPAXI_PROTECTEN_STA1[13])
		 * Data: 1'b0
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
			13, 0, 10, 500, check);
		if (check != 0)
			pr_err("polling AHB TX bus sleep protect turn off fail. Status=0x%08x\n",
				CONSYS_REG_READ(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET));
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
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00002000);

		/* check AHB TX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1228[13]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
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
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_SET_OFFSET,
			0x00004000);

		/* check AXI Rx bus sleep protect turn on
		 * (polling "100 times", polling interval is 1ms)
		 * Address: 0x1000_1228[14]
		 * Data: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET,
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
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_SET_OFFSET,
			0x00000002);
		/* check AHB RX bus sleep protect turn on (polling "10 times")
		 * Address: 0x1000_1724[2] (INFRA_TOPAXI_PROTECTEN2_STA1[2])
		 * Value: 1'b1
		 * Action: polling
		 */
		CONSYS_REG_BIT_POLLING(
			CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET,
			2, 1, 10, 0, check);
		if (check)
			pr_err("Polling AHB RX bus sleep protect turn on fail.");

		/* Assert "conn_infra_on" isolation, set "connsys_iso_en"=1
		 * Address: CONN_PWR_CON[1] (0x1000_6304[1])
		 * Value: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x2);

		/* Assert CONNSYS S/W reset (SPM CR), set "ap_sw_rst_b"=0
		 * Address: CONN_PWR_CON[0] (0x1000_6304[0])
		 * Value: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x1);

		/* Assert CONNSYS S/W reset(TOP RGU CR), set "ap_sw_rst_b"=0
		 * Address: WDT_SWSYSRST[9] (0x1000_7018[9])
		 *          WDT_SWSYSRST[31:24] (0x1000_7018[31:24])
		 * Value: [9]=1'b1
		 *        [31:24]=8'h88 (key)
		 * Action: write
		 * Note: this CR value for reset control is active high (0: not reset, 1: reset)
		 */
		CONSYS_REG_WRITE_MASK(
			CON_REG_TOP_RGU_ADDR + TOP_RGU_WDT_SWSYSRST,
			0x88000200,
			0xff000200);

		/* Turn off AP-to-CONNSYS bus clock, set "conn_clk_dis"=1
		 * (apply this for bus clock gating)
		 * Address: CONN_PWR_CON[4] (0x1000_6304[4])
		 * Value: 1'b1
		 * Action: write
		 */
		CONSYS_SET_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x10);

		/* wait 1us (?) */
		udelay(1);

		/* De-assert "conn_infra_on" primary part power on,
		 * set "connsys_on_domain_pwr_on"=0
		 * Address: CONN_PWR_CON[2] (0x1000_6304[2])
		 * Value: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x4);

		/* De-assert "conn_infra_on" secondary part power on,
		 * set "connsys_on_domain_pwr_on_s"=0
		 * Address: CONN_PWR_CON[3] (0x1000_6304[3])
		 * Value: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_SPM_BASE_ADDR + SPM_CONN_PWR_CON, 0x8);

		/* Turn off ap2conn host_ck CG (ECO)
		 * Address: INFRA_AP2MD_GALS_CTL[0] (0x1020E504[0])
		 * Data: 1'b0
		 * Action: write
		 */
		CONSYS_CLR_BIT(CON_REG_INFRACFG_BASE_ADDR + INFRA_AP2MD_GALS_CTL, 0x1);
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

int consys_polling_chipid(void)
{
	unsigned int retry = 10;
	unsigned int consys_hw_ver = 0;
	unsigned int consys_configuration_id = 0;
	int ret = -1;

	while (retry-- > 0) {
		consys_hw_ver = CONSYS_REG_READ(
					CON_REG_INFRA_CFG_ADDR +
					CONN_HW_VER_OFFSET);
		if (consys_hw_ver == CONN_HW_VER) {
			consys_configuration_id = CONSYS_REG_READ(
				CON_REG_INFRA_CFG_ADDR + CONN_CFG_ID_OFFSET);
			pr_info("Consys HW version id(0x%x) cfg_id=(0x%x)\n",
				consys_hw_ver, consys_configuration_id);
			ret = 0;
			/* !!!!!!!!!!!!!!! for debug !!!!!!!!!!!!!!!!!! */
			pr_info("AXI RX(%x) AHB RX (%x) AHB TX (%x)",
				CONSYS_REG_READ_BIT(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET, 0x1 << 14) >> 14,
				CONSYS_REG_READ_BIT(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET, 0x1 << 2) >> 2,
				CONSYS_REG_READ_BIT(CON_REG_INFRACFG_AO_ADDR + INFRA_TOPAXI_PROTECTEN_STA1_OFFSET, 0x1 << 13) >> 13);
			break;
		}
		pr_err("Read CONSYS version id(0x%08x), retry countdown(%d)",
			consys_hw_ver, retry);
		msleep(20);
	}

	/* !!!!!!!!!!!!!!!!!!!For FPGA workaround start!!!!!!!!!!!!!!!!!!!!!! */
	CONSYS_SET_BIT(CON_REG_INFRA_CFG_ADDR + 0x0c04,
		((0x1 << 1) | (0x1 << 9) | (0x1 << 17) | (0x1 << 25)));
	pr_info("Check %x\n", CON_REG_INFRA_CFG_ADDR + 0x0c04);
	/* !!!!!!!!!!!!!!!!!!!For FPGA workaround end!!!!!!!!!!!!!!!!!!!!!! */

	return ret;
}

int connsys_d_die_cfg(void)
{
	/* read D-die Efuse
	 * Address: AP2CONN_EFUSE_DATA (0x1800_1818)
	 * Data:
	 * Action: read
	 */

	/* conn_infra sysram hw control setting -> disable hw power down
	 * Address: CONN_INFRA_RGU_SYSRAM_HWCTL_PDN_SYSRAM_HWCTL_PDN (0x1800_0038)
	 * Data: 32'h0
	 * Action: write
	 */
	CONSYS_REG_WRITE(CON_REG_INFRA_RGU_ADDR + CONN_INFRA_RGU_SYSRAM_HWCTL_PDN, 0x0);

	/* conn_infra sysram hw control setting -> enable hw sleep
	 * Address: CONN_INFRA_RGU_SYSRAM_HWCTL_SLP_SYSRAM_HWCTL_SLP (0x1800_003C)
	 * Data: 32'h0000_00FF
	 * Action: write
	 */
	CONSYS_REG_WRITE(CON_REG_INFRA_RGU_ADDR + CONN_INFRA_RGU_SYSRAM_HWCTL_SLP, 0x000000ff);

	/* co-ext memory  hw control setting -> disable hw power down
	 * Address: CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_PDN_CO_EXT_MEM_HWCTL_PDN (0x1800_0050)
	 * Data: 32'h0
	 * Action: write
	 */
	CONSYS_REG_WRITE(CON_REG_INFRA_RGU_ADDR + CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_PDN, 0x0);

	/* co-ext memory  hw control setting -> enable hw sleep
	 * Address: CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_SLP_CO_EXT_MEM_HWCTL_SLP (0x1800_0054)
	 * Data: 32'h0000_0001
	 * Action: write
	 */
	CONSYS_REG_WRITE(CON_REG_INFRA_RGU_ADDR + CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_SLP, 0x1);

	return 0;
}

int connsys_spi_master_cfg(void)
{
	/* CONN_WT_SLP_CTL_REG_WB_WF_CK_ADDR_ADDR(0x070) = 0x0AF40A04
	 * CONN_WT_SLP_CTL_REG_WB_WF_WAKE_ADDR_ADDR(0x74) = 0x00A00090
	 * CONN_WT_SLP_CTL_REG_WB_WF_ZPS_ADDR_ADDR(0x78) = 0x009c008
	 * CONN_WT_SLP_CTL_REG_WB_BT_CK_ADDR_ADDR(0x7c[11:0]) = 0xa08
	 * CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR_ADDR(0x80[11:0]) = 0x094
	 * CONN_WT_SLP_CTL_REG_WB_TOP_CK_ADDR_ADDR(0x84[11:0]) = 0xA00
	 * CONN_WT_SLP_CTL_REG_WB_GPS_CK_ADDR_ADDR(0x88[11:0]) = 0x0AFC0A0C
	 * CONN_WT_SLP_CTL_REG_WB_WF_B0_CMD_ADDR_ADDR(0x8c[11:0]) = 0x0F0
	 * CONN_WT_SLP_CTL_REG_WB_WF_B1_CMD_ADDR_ADDR(0x90[11:0])  = 0x0F4
	 */
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_WF_CK_ADDR, 0x0AF40A04);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_WF_WAKE_ADDR, 0x00A00090);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_WF_ZPS_ADDR, 0x009c008);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BT_CK_ADDR,
		0xa08, 0xfff);
	pr_info("Before write: 0x%08x\n"
		, CONSYS_REG_READ(CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR));
	pr_info("CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR_ADDR(0x80[11:0]) = 0x094\n");
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR,
		0x094, 0xfff);
	pr_info("After write: 0x%08x\n"
		, CONSYS_REG_READ(CON_REG_WT_SPL_CTL_ADDR
			+ CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR));
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_TOP_CK_ADDR,
		0xa00, 0xfff);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_GPS_CK_ADDR,
		0x0AFC0A0C);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_WF_B0_CMD_ADDR,
		0x0f0, 0xfff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_WF_B1_CMD_ADDR,
		0x0f4, 0xfff);

	/* CONN_WT_SLP_CTL_REG_WB_SLP_CTL_CMD_LENGTH(0x004[4:0]) = 0x6
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR1_WB_BG_ADDR1(0x10[15:0]) = 0xA03C
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR2_WB_BG_ADDR2(0x14[15:0]) = 0xA03C
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR3_WB_BG_ADDR3(0x18[15:0]) = 0xAA18
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR4_WB_BG_ADDR4(0x1c[15:0]) = 0xAA18
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR5_WB_BG_ADDR5(0x20[15:0]) = 0xAA18
	 * CONN_WT_SLP_CTL_REG_WB_BG_ADDR6_WB_BG_ADDR6(0x24[15:0]) = 0xA0C8
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON1_WB_BG_ON1(0x30)     = 0x00000000
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON2_WB_BG_ON2(0x34)     = 0x00000000
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON3_WB_BG_ON3(0x38)     = 0x74E0FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON4_WB_BG_ON4(0x3c)     = 0x76E0FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON5_WB_BG_ON5(0x40)     = 0x76E8FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_ON6_WB_BG_ON6(0x44)     = 0x00000000
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF1_WB_BG_OFF1(0x50)   = 0x57400000
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF2_WB_BG_OFF2(0x54)   = 0x57400000
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF3_WB_BG_OFF3(0x58)   = 0x44E0FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF4_WB_BG_OFF4(0x5c)   = 0x44E0FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF5_WB_BG_OFF5(0x60)   = 0x44E0FFF5
	 * CONN_WT_SLP_CTL_REG_WB_BG_OFF6_WB_BG_OFF6(0x64)   = 0x00000001
	 */
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_SLP_CTL,
		0x6, 0xf);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR1,
		0xa03c, 0xffff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR2,
		0xa03c, 0xffff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR3,
		0xaa18, 0xffff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR4,
		0xaa18, 0xffff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR5,
		0xaa18, 0xffff);
	CONSYS_REG_WRITE_MASK(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ADDR6,
		0xa0c8, 0xffff);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON1, 0x00000000);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON2, 0x00000000);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON3, 0x74e0fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON4, 0x76e0fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON5, 0x76e8fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_ON6, 0x00000000);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF1, 0x57400000);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF2, 0x57400000);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF3, 0x44e0fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF4, 0x44e0fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF5, 0x44e0fff5);
	CONSYS_REG_WRITE(
		CON_REG_WT_SPL_CTL_ADDR + CONN_WT_SLP_CTL_REG_WB_BG_OFF6, 0x00000001);

	return 0;
}

int connsys_a_die_cfg(void)
{
	return 0;
}

int connsys_afe_wbg_cal(void)
{
	return 0;
}

int connsys_low_power_setting(void)
{
	/* Enable AP2CONN GALS Slave sleep protect en with conn_infra on2off/off2on & wfdma2conn
	 * sleep protect en
	 * Address: CONN_HOST_CSR_TOP_CONN_SLP_PROT_CTRL_WFDMA2CONN_SLP_PROT_AP2CONN_EN_ENABLE
	 *          CONN_HOST_CSR_TOP_CONN_SLP_PROT_CTRL_CONN_INFRA_ON2OFF_SLP_PROT_AP2CONN_EN_ENABLE
	 *          CONN_HOST_CSR_TOP_CONN_SLP_PROT_CTRL_CONN_INFRA_OFF2ON_SLP_PROT_AP2CONN_EN_ENABLE (0x1806_0184[11:9])
	 * Data: 3'b111
	 * Action: write
	 */
	CONSYS_REG_WRITE_MASK(
		CON_REG_HOST_CSR_ADDR + CONN_HOST_CSR_TOP_CONN_SLP_PROT_CTRL,
		0xe00, 0xe00);


	/* Unmask on2off/off2on slpprot_rdy enable checker @conn_infra off power off=> check slpprot_rdy = 1'b1 and go to sleep
	 * Address: CONN_INFRA_CFG_PWRCTRL0_CONN_INFRA_CFG_SLP_RDY_MASK (0x18001860[15:12])
	 * Data: 4'h0
	 * Action: write
	 */
	CONSYS_REG_WRITE_MASK(
		CON_REG_INFRA_CFG_ADDR + CONN_INFRA_CFG_PWRCTRL0,
		0x0, 0xf000);

	/* TBD: osc_ctrl setting/rc mode setting
	 * Action: write
	 * Note: XO VCORE RDY STABLE TIMEXO initial stable timesXO bg stable time
	 */

	/* TBD: clear "source clock enable ack to XO state" mask
	 * Action: write
	 * Note: ack for XO state mask (0: not mask, 1: mask)
	 */

	/* conn_infra low power setting */

	/* conn2ap sleep protect release bypass ddr_en_ack check
	 * Address: CONN_INFRA_CFG_EMI_CTL_0_EMI_SLPPROT_BP_DDR_EN (0x18001C00[18])
	 * Data: 1'b1
	 * Action: write
	 */
	CONSYS_SET_BIT(CON_REG_INFRA_CFG_ADDR + CONN_INFRA_CFG_EMI_CTL_0, 0x40000);

	/* Enable ddr_en timeout, timeout value = 1023 T (Bus clock)
	 * Address: CONN_INFRA_CFG_EMI_CTL_0_DDR_CNT_LIMIT (0x18001C00[14:4])
	 * Data: 11'd1023
	 * Action: write
	 */
	CONSYS_REG_WRITE_MASK(
		CON_REG_INFRA_CFG_ADDR + CONN_INFRA_CFG_EMI_CTL_0,
		0x3ff0, 0x7ff0);

	/* Conn_infra HW_CONTROL => conn_infra enter dsleep mode
	 * Address: CONN_INFRA_CFG_PWRCTRL0_HW_CONTROL (0x1800_1860[0])
	 * Data: 1'b1
	 * Action: write
	 * Note: enable conn_infra off domain as HW control
	 */
	CONSYS_SET_BIT(CON_REG_INFRA_CFG_ADDR + CONN_INFRA_CFG_PWRCTRL0, 0x1);

	return 0;
}
