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

#ifndef _PLATFORM_MT6789_H_
#define _PLATFORM_MT6789_H_

#include "osal.h"
/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
/* Base: infracfg_ao (0x1000_1000) */
#define INFRA_TOPAXI_PROTECTEN_STA1_OFFSET	0x0228
#define INFRA_TOPAXI_PROTECTEN_SET_OFFSET	0x02a0
#define INFRA_TOPAXI_PROTECTEN_CLR_OFFSET	0x02a4
#define INFRA_TOPAXI_PROTECTEN2_CLR_OFFSET	0x0718
#define INFRA_TOPAXI_PROTECTEN2_SET_OFFSET	0x0714
#define INFRA_TOPAXI_PROTECTEN2_STA1_OFFSET	0x0724

/* Base: conn_infra_cfg (0x1800_1000) */
#define CONN_HW_VER_OFFSET	0x0000
#define CONN_CFG_ID_OFFSET	0x0004

#define CONN_HW_VER	0x20010000
#define CONN_CFG_ID	0x3

/* Base: SPM (0x1000_6000) */
#define SPM_POWERON_CONFIG_EN	0x0000
#define SPM_PWR_STATUS		0x016c
#define SPM_PWR_STATUS_2ND	0x0170
#define SPM_CONN_PWR_CON	0x0304

/* Base: TOP RGU (0x1000_7000) */
#define TOP_RGU_WDT_SWSYSRST	0x0018

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


/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif				/* _PLATFORM_MT6789_H_ */
