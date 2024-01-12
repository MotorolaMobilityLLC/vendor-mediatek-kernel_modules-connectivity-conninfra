// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2023 MediaTek Inc.
 */

#include <linux/delay.h>

#include "connv3.h"
#include "connv3_hw.h"
#include "connv3_hw_dbg.h"

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static int connv3_conninfra_bus_dump_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb);
static int connv3_conninfra_power_info_dump_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb,
	char *buf, unsigned int size);
static int connv3_conninfra_power_info_reset_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb);


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
const struct connv3_platform_dbg_ops g_connv3_hw_dbg_mt6653 = {
	.dbg_bus_dump = connv3_conninfra_bus_dump_mt6653,
	.dbg_power_info_dump = connv3_conninfra_power_info_dump_mt6653,
	.dbg_power_info_reset = connv3_conninfra_power_info_reset_mt6653,
};

/*******************************************************************************
 *                              F U N C T I O N S
 ********************************************************************************
 */

int connv3_conninfra_bus_dump_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb)
{
	pr_info("connv3_conninfra_bus_dump_mt6653 is empty now\n");
	return 0;
}

int connv3_conninfra_power_info_dump_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb,
	char *buf, unsigned int size)
{
	pr_info("connv3_conninfra_power_info_dump_mt6653 is empty now\n");
	return 0;
}

int connv3_conninfra_power_info_reset_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb)
{
	pr_info("connv3_conninfra_power_info_reset_mt6653 is empty now\n");
	return 0;
}
