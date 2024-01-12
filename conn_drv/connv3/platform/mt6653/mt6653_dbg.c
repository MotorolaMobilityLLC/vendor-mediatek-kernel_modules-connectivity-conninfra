// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2023 MediaTek Inc.
 */

#include <linux/delay.h>

#include "connv3.h"
#include "connv3_hw.h"
#include "connv3_hw_dbg.h"

#include "mt6653_dbg.h"

#define MT6653_CONN_INFRA_CLK_DETECT		0x20023000
#define MT6653_CONN_INFRA_VERSION_ID_REG	0x7c011000
#define MT6653_CONN_INFRA_VERSION_ID		0x03040001
#define MT6653_CONN_INFRA_OFF_IRQ_REG		0x20023400

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

static int connv3_bus_check_ap2conn_off_mt6653(struct connv3_cr_cb *cb)
{
	unsigned int value;
	int i, ret;
	void *data = cb->priv_data;

	/* AP2CONN_INFRA OFF */
	/* 1.Check "AP2CONN_INFRA ON step is ok" (X)
	 * 2. Check conn_infra off bus clock
	 * (Need to polling 4 times to confirm the correctness and polling every 1ms)
	 * - write 0x1 to 0x1802_3000[0], reset clock detect
	 * - 0x1802_3000[1] conn_infra off bus clock (should be 1'b1 if clock exist)
	 * - 0x1802_3000[3] lp_osc clock (should be 1'b1 if clock exist)
	 * 3. Read conn_infra IP version
	 * - Read 0x1801_1000 = 0x03030002
	 * 4. Check conn_infra off domain bus hang irq status
	 * - 0x1802_3400[9:0], should be 10'b0, or means conn_infra off bus timeout
	 */
	for (i = 0; i < 4; i++) {
		ret = cb->write_mask(data, MT6653_CONN_INFRA_CLK_DETECT, 0x1, 0x1);
		if (ret) {
			pr_notice("[%s] clock detect write fail, ret = %d", __func__, ret);
			break;
		}
		ret = cb->read(data, MT6653_CONN_INFRA_CLK_DETECT, &value);
		if (ret) {
			pr_notice("[%s] clock detect read fail, ret = %d", __func__, ret);
			break;
		}
		if ((value & 0xa) == 0xa)
			break;
		udelay(1000);
	}
	if (ret)
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	if ((value & 0xa) != 0xa) {
		pr_notice("[%s] clock detect fail, get: [0x%08x]", __func__, value);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}

	/* Read IP version */
	ret = cb->read(data, MT6653_CONN_INFRA_VERSION_ID_REG, &value);
	if (ret) {
		pr_notice("[%s] get conn_infra version fail, ret=[%d]", __func__, ret);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}
	if (value != MT6653_CONN_INFRA_VERSION_ID) {
		pr_notice("[%s] get conn_infra version fail, expect:[0x%08x], get:0x%08x",
			__func__, MT6653_CONN_INFRA_VERSION_ID, value);
		return CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR;
	}

	/* Check bus timeout irq */
	ret = cb->read(data, MT6653_CONN_INFRA_OFF_IRQ_REG, &value);
	if (ret) {
		pr_notice("[%s] read irq status fail, ret=[%d]", __func__, ret);
		return CONNV3_BUS_CONN_INFRA_BUS_HANG_IRQ;
	}
	if ((value & 0x3ff) != 0x0) {
		pr_notice("[%s] bus time out irq detect, get:0x%08x", __func__, value);
		return CONNV3_BUS_CONN_INFRA_BUS_HANG_IRQ;
	}

	return 0;
}

int connv3_conninfra_bus_dump_mt6653(
	enum connv3_drv_type drv_type, struct connv3_cr_cb *cb)
{
	int ret = 0, func_ret = 0;

	/* Print version */
	pr_info("[V3_BUS][PSOP_1_1] version=%s\n", MT6653_CONNINFRA_DEBUGSOP_DUMP_VERSION);

	/* Dump host side CR */
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_conn_infra_bus_a, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_conn_infra_bus_a error(%d)\n", __func__, ret);
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_connsys_power_b, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_connsys_power_b error(%d)\n", __func__, ret);
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_conn_infra_top_a, cb);
	if (ret)
		pr_notice("[%s] mt6653_conn_infra_top_a error(%d)\n", __func__, ret);

	/* AP2CONN_INFRA OFF check */
	func_ret = connv3_bus_check_ap2conn_off_mt6653(cb);
	if (func_ret == CONNV3_BUS_CONN_INFRA_OFF_CLK_ERR)
		return func_ret;

	/* Dump conninfra off */
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_conn_infra_bus_b, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_conn_infra_bus_b error(%d)\n", __func__, ret);
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_conn_infra_bus_c, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_conn_infra_bus_c error(%d)\n", __func__, ret);
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_connsys_power_c, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_connsys_power_c error(%d)\n", __func__, ret);
	ret = connv3_hw_dbg_unify_dump_utility(
		&mt6653_dump_list_conn_infra_top_b, cb);
	if (ret)
		pr_notice("[%s] mt6653_dump_list_conn_infra_top_b error(%d)\n", __func__, ret);

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
