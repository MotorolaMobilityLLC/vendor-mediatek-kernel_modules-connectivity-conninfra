/*  SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#ifndef _CONNV3_HW_H_
#define _CONNV3_HW_H_

#include <linux/platform_device.h>
#include <linux/types.h>
#include "conninfra.h"

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

struct connv3_hw_ops_struct {

	u32 (*connsys_plt_get_chipid) (void);
	u32 (*connsys_plt_get_adie_chipid) (void);
};

#define DRV_GEN_SUPPORT_FULL 0x7
struct connv3_plat_data {
	const u32 chip_id;
	const u32 consys_hw_version;
	const void* hw_ops;
	const void* platform_pmic_ops;
	const void* platform_pinctrl_ops;
};

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
int connv3_hw_init(struct platform_device *pdev);
int connv3_hw_deinit(void);

int connv3_hw_pwr_off(unsigned int curr_status, unsigned int off_radio);
int connv3_hw_pwr_on(unsigned int curr_status, unsigned int on_radio);
int connv3_hw_pwr_on_done(unsigned int radio);

unsigned int connv3_hw_get_chipid(void);
unsigned int connv3_hw_get_adie_chipid(void);
/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif	/* _CONNV3_HW_H_ */
