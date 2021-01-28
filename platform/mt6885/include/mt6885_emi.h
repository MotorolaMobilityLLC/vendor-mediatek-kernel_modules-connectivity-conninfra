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

#ifndef _PLATFORM_MT6885_H_
#define _PLATFORM_MT6885_H_

#include "osal.h"
#include "emi_mng.h"
/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/* Base: conn_host_csr_top */
#define CONN2AP_REMAP_MCU_EMI_BASE_ADDR_OFFSET	0x000001c4
#define CONN2AP_REMAP_MD_SHARE_EMI_BASE_ADDR_OFFSET	0x000001cc


#define CONSYS_EMI_COREDUMP_OFFSET	(0x68000)
#define CONSYS_EMI_AP_PHY_OFFSET	(0x00000)
#define CONSYS_EMI_AP_PHY_BASE		(0x80068000)
#define CONSYS_EMI_FW_PHY_BASE		(0xf0068000)
#define CONSYS_EMI_PAGED_TRACE_OFFSET	(0x400)
#define CONSYS_EMI_PAGED_DUMP_OFFSET	(0x8400)
#define CONSYS_EMI_FULL_DUMP_OFFSET	(0x10400)
#define CONSYS_EMI_MET_DATA_OFFSET	(0x0)


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
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

P_CONSYS_PLATFORM_EMI_OPS get_consys_platform_emi_ops(void);
P_CONSYS_EMI_ADDR_INFO consys_emi_get_phy_addr(void);
int consys_emi_mpu_set_region_protection(void);
unsigned int consys_emi_set_remapping_reg(void);
int consys_emi_coredump_remapping(unsigned char __iomem **addr, unsigned int enable);
int consys_reset_emi_coredump(unsigned char __iomem *addr);


/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif				/* _PLATFORM_MT6885_H_ */
