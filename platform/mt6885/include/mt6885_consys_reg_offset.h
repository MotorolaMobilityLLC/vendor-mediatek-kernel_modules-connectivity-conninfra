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

#ifndef _PLATFORM_MT6885_CONSYS_REG_OFFSET_H_
#define _PLATFORM_MT6885_CONSYS_REG_OFFSET_H_


/**********************************************************************/
/* Base: infracfg_ao (0x1000_1000) */
/**********************************************************************/
#define INFRA_TOPAXI_PROTECTEN_STA1_OFFSET	0x0228
#define INFRA_TOPAXI_PROTECTEN_SET_OFFSET	0x02a0
#define INFRA_TOPAXI_PROTECTEN_CLR_OFFSET	0x02a4
#define INFRA_TOPAXI_PROTECTEN2_CLR_OFFSET	0x0718
#define INFRA_TOPAXI_PROTECTEN2_SET_OFFSET	0x0714
#define INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET	0x0724

/**********************************************************************/
/* Base: SPM (0x1000_6000) */
/**********************************************************************/
#define SPM_POWERON_CONFIG_EN	0x0000
#define SPM_PWR_STATUS		0x016c
#define SPM_PWR_STATUS_2ND	0x0170
#define SPM_CONN_PWR_CON	0x0304

/**********************************************************************/
/* Base: TOP RGU (0x1000_7000) */
/**********************************************************************/
#define TOP_RGU_WDT_SWSYSRST	0x0018


/**********************************************************************/
/* Base: INFRACFG (0x1020_e000) */
/**********************************************************************/
#define INFRA_AP2MD_GALS_CTL	0x0504

/**********************************************************************/
/* Base: conn_infra_rgu (0x1800_0000) */
/**********************************************************************/
#define CONN_INFRA_RGU_SYSRAM_HWCTL_PDN		0x0038
#define CONN_INFRA_RGU_SYSRAM_HWCTL_SLP		0x003c
#define CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_PDN	0x0050
#define CONN_INFRA_RGU_CO_EXT_MEM_HWCTL_SLP	0x0054

/**********************************************************************/
/* Base: conn_infra_cfg (0x1800_1000) */
/**********************************************************************/
#define CONN_HW_VER_OFFSET		0x0000
#define CONN_CFG_ID_OFFSET		0x0004
#define CONN_INFRA_CFG_PWRCTRL0		0x0860
#define CONN_INFRA_CFG_EMI_CTL_0	0x0c00


#define CONN_HW_VER	0x20010000
#define CONN_CFG_ID	0x3

/**********************************************************************/
/* Base: conn_wt_slp_ctl_reg(0x1800_5000) */
/**********************************************************************/
#define CONN_WT_SLP_CTL_REG_WB_WF_CK_ADDR	0x0070
#define CONN_WT_SLP_CTL_REG_WB_WF_WAKE_ADDR	0x0074
#define CONN_WT_SLP_CTL_REG_WB_WF_ZPS_ADDR	0x0078
#define CONN_WT_SLP_CTL_REG_WB_BT_CK_ADDR	0x007c
#define CONN_WT_SLP_CTL_REG_WB_BT_WAKE_ADDR	0x0080
#define CONN_WT_SLP_CTL_REG_WB_TOP_CK_ADDR	0x0084
#define CONN_WT_SLP_CTL_REG_WB_GPS_CK_ADDR	0x0088
#define CONN_WT_SLP_CTL_REG_WB_WF_B0_CMD_ADDR	0x008c
#define CONN_WT_SLP_CTL_REG_WB_WF_B1_CMD_ADDR	0x0090
#define CONN_WT_SLP_CTL_REG_WB_SLP_CTL		0x0004
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR1		0x0010
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR2		0x0014
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR3		0x0018
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR4		0x001c
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR5		0x0020
#define CONN_WT_SLP_CTL_REG_WB_BG_ADDR6		0x0024
#define CONN_WT_SLP_CTL_REG_WB_BG_ON1		0x0030
#define CONN_WT_SLP_CTL_REG_WB_BG_ON2		0x0034
#define CONN_WT_SLP_CTL_REG_WB_BG_ON3		0x0038
#define CONN_WT_SLP_CTL_REG_WB_BG_ON4		0x003c
#define CONN_WT_SLP_CTL_REG_WB_BG_ON5		0x0040
#define CONN_WT_SLP_CTL_REG_WB_BG_ON6		0x0044
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF1		0x0050
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF2		0x0054
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF3		0x0058
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF4		0x005c
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF5		0x0060
#define CONN_WT_SLP_CTL_REG_WB_BG_OFF6		0x0064


/**********************************************************************/
/* Base: conn_host_csr_top (0x1806_0000) */
/**********************************************************************/
#define CONN_HOST_CSR_TOP_CONN_SLP_PROT_CTRL	0x0184

/* remap */
#define CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET		0x01c4
#define CONN2AP_REMAP_MD_SHARE_EMI_BASE_ADDR_OFFSET	0x01cc
#define CONN2AP_REMAP_GPS_EMI_BASE_ADDR_OFFSET		0x01d0
#define CONN2AP_REMAP_WF_PERI_BASE_ADDR_OFFSET		0x01d4
#define CONN2AP_REMAP_BT_PERI_BASE_ADDR_OFFSET		0x01d8
#define CONN2AP_REMAP_GPS_PERI_BASE_ADDR_OFFSET		0x01dc

#endif				/* _PLATFORM_MT6789_CONSSY_REG_OFFSET_H_ */
