/*  SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef _PLATFORM_CLOCK_MNG_H_
#define _PLATFORM_CLOCK_MNG_H_

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/version.h>

#include "consys_hw.h"

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
#define COMMON_KERNEL_CLK_SUPPORT	1
#else
#define COMMON_KERNEL_CLK_SUPPORT	0
#endif

#include "conninfra.h"

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
int clock_mng_init(struct platform_device *pdev, const struct conninfra_plat_data* plat_data);
int clock_mng_deinit(void);
struct regmap* consys_clock_mng_get_regmap(void);
const char* clock_mng_get_schematic_name(enum connsys_clock_schematic type);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif				/* _PLATFORM_CLOCK_MNG_H_ */
