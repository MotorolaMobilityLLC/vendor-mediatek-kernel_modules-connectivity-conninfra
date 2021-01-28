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
#ifdef CONFIG_MTK_EMI
#include <mt_emi_api.h>
#endif
#include <linux/of_reserved_mem.h>

#include "osal.h"
#include "mt6885_emi.h"
#include "consys_hw.h"
#include "consys_hw_util.h"

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
#if 0
static P_CONSYS_EMI_ADDR_INFO consys_emi_get_phy_addr(void);
static int consys_emi_mpu_set_region_protection(void);
static unsigned int consys_emi_set_remapping_reg(void);
static int consys_emi_coredump_remapping(unsigned char __iomem **addr, unsigned int enable);
static int consys_reset_emi_coredump(unsigned char __iomem *addr);
#endif
/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
EMI_CTRL_STATE_OFFSET connsys_emi_state_off = {
	.emi_apmem_ctrl_state = EXP_APMEM_CTRL_STATE,
	.emi_apmem_ctrl_host_sync_state = EXP_APMEM_CTRL_HOST_SYNC_STATE,
	.emi_apmem_ctrl_host_sync_num = EXP_APMEM_CTRL_HOST_SYNC_NUM,
#if 0
	.emi_apmem_ctrl_chip_sync_state = EXP_APMEM_CTRL_CHIP_SYNC_STATE,
	.emi_apmem_ctrl_chip_sync_num = EXP_APMEM_CTRL_CHIP_SYNC_NUM,
	.emi_apmem_ctrl_chip_sync_addr = EXP_APMEM_CTRL_CHIP_SYNC_ADDR,
	.emi_apmem_ctrl_chip_sync_len = EXP_APMEM_CTRL_CHIP_SYNC_LEN,
	.emi_apmem_ctrl_chip_print_buff_start = EXP_APMEM_CTRL_CHIP_PRINT_BUFF_START,
	.emi_apmem_ctrl_chip_print_buff_len = EXP_APMEM_CTRL_CHIP_PRINT_BUFF_LEN,
	.emi_apmem_ctrl_chip_print_buff_idx = EXP_APMEM_CTRL_CHIP_PRINT_BUFF_IDX,
	.emi_apmem_ctrl_chip_int_status = EXP_APMEM_CTRL_CHIP_INT_STATUS,
	.emi_apmem_ctrl_chip_paded_dump_end = EXP_APMEM_CTRL_CHIP_PAGED_DUMP_END,
	.emi_apmem_ctrl_host_outband_assert_w1 = EXP_APMEM_CTRL_HOST_OUTBAND_ASSERT_W1,
	.emi_apmem_ctrl_chip_page_dump_num = EXP_APMEM_CTRL_CHIP_PAGE_DUMP_NUM,
	.emi_apmem_ctrl_assert_flag = EXP_APMEM_CTRL_ASSERT_FLAG,
#endif
};


CONSYS_EMI_ADDR_INFO connsys_emi_addr_info = {
	.emi_ap_phy_addr = 0,
	.emi_size = 0
};

CONSYS_PLATFORM_EMI_OPS g_consys_platform_emi_ops = {
	.consys_ic_emi_mpu_set_region_protection = consys_emi_mpu_set_region_protection,
	.consys_ic_emi_set_remapping_reg = consys_emi_set_remapping_reg,
	.consys_ic_emi_get_phy_addr = consys_emi_get_phy_addr,
	/* should be done by subsys */
	.consys_ic_emi_coredump_remapping = consys_emi_coredump_remapping,
	.consys_ic_reset_emi_coredump = consys_reset_emi_coredump,
};


/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

P_CONSYS_PLATFORM_EMI_OPS get_consys_platform_emi_ops(void)
{
	return &g_consys_platform_emi_ops;
}

int consys_emi_mpu_set_region_protection(void)
{
//#ifdef CONFIG_MTK_EMI
#if 0
	struct emi_region_info_t region_info;

	/*set MPU for EMI share Memory */
	pr_info("setting MPU for EMI share memory\n");

	region_info.start = gConEmiPhyBase;
	region_info.end = gConEmiPhyBase + gConEmiSize - 1;
	region_info.region = 25;
	SET_ACCESS_PERMISSION(region_info.apc, LOCK,
			FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN,
			FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN, FORBIDDEN,
			NO_PROTECTION, FORBIDDEN, NO_PROTECTION);
	emi_mpu_set_protection(&region_info);
#endif
	return 0;
}

unsigned int consys_emi_set_remapping_reg(void)
{
	/* For direct path */
	//phys_addr_t mdPhy = 0;
	//int size = 0;

	pr_info("[%s]", __func__);
	connsys_emi_addr_info.emi_ap_phy_addr = gConEmiPhyBase;
	connsys_emi_addr_info.emi_size = gConEmiSize;

	/* EMI Registers remapping */
	CONSYS_REG_WRITE_OFFSET_RANGE(conn_reg.conn_host_csr_top_base + CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET,
					  gConEmiPhyBase, 0, 16, 20);
	pr_info("CONSYS_EMI_MAPPING dump in restore cb(0x%08x)\n",
			CONSYS_REG_READ(conn_reg.conn_host_csr_top_base + CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET));

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

P_CONSYS_EMI_ADDR_INFO consys_emi_get_phy_addr(void)
{
	return &connsys_emi_addr_info;
}

int consys_emi_coredump_remapping(unsigned char __iomem **addr, unsigned int enable)
{
#if 0
	if (enable) {
		*addr = ioremap_nocache(gConEmiPhyBase + CONSYS_EMI_COREDUMP_OFFSET, CONSYS_EMI_MEM_SIZE);
		if (*addr) {
			pr_info("COREDUMP EMI mapping OK virtual(0x%p) physical(0x%x)\n",
					   *addr, (UINT32) gConEmiPhyBase + CONSYS_EMI_COREDUMP_OFFSET);
			memset_io(*addr, 0, CONSYS_EMI_MEM_SIZE);
		} else {
			pr_err("EMI mapping fail\n");
			return -1;
		}
	} else {
		if (*addr) {
			iounmap(*addr);
			*addr = NULL;
		}
	}
#endif
	return 0;
}

int consys_reset_emi_coredump(unsigned char __iomem *addr)
{
#if 0
	if (!addr) {
		pr_err("get virtual address fail\n");
		return -1;
	}
	pr_info("Reset EMI(0xF0068000 ~ 0xF0068400) and (0xF0070400 ~ 0xF0078400)\n");
	/* reset 0xF0068000 ~ 0xF0068400 (1K) */
	memset_io(addr, 0, 0x400);
	/* reset 0xF0070400 ~ 0xF0078400 (32K)  */
	memset_io(addr + CONSYS_EMI_PAGED_DUMP_OFFSET, 0, 0x8000);
#endif
	return 0;
}
