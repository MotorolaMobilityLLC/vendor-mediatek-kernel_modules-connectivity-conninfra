/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef _CONNV3_HW_DBG_H_
#define _CONNV3_HW_DBG_H_

#include "connv3.h"
#include "connv3_hw.h"


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

struct connv3_platform_dbg_ops {
	int (*dbg_bus_dump)(enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data);
	int (*dbg_power_info_dump)(enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data, char *buf, unsigned int size);
	int (*dbg_power_info_reset)(enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data);
};

struct connv3_dbg_command {
	bool write;
	unsigned int w_addr;
	unsigned int mask;
	unsigned int value;
	bool read;
	unsigned int r_addr;
};

struct connv3_dump_list {
	char* tag;
	unsigned int dump_size;
	struct connv3_dbg_command *cmd_list;
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

int connv3_hw_dbg_init(struct platform_device *pdev,
			const struct connv3_plat_data* plat_data);
int connv3_hw_dbg_deinit(void);
int connv3_hw_dbg_bus_dump(enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data);
int connv3_hw_dbg_dump_utility(
	struct connv3_dump_list *dump_list, struct connv3_cr_cb *cb, void *data);
int connv3_hw_dbg_power_info_dump(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data,
	char *buf, unsigned int size);
int connv3_hw_dbg_power_info_reset(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb, void *data);

#endif /* _CONNV3_HW_DBG_H_ */
