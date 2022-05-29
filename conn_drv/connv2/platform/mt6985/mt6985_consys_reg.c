// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include <linux/delay.h>
#include <linux/memblock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>

/* For bus hang error definition */
#include "conninfra.h"
#include "consys_reg_mng.h"
#include "consys_reg_util.h"
#include "osal.h"
#include "mt6985_consys_reg.h"
#include "mt6985_consys_reg_offset.h"
#include "mt6985_pos.h"
#include "mt6985_pos_gen.h"

static int consys_reg_init(struct platform_device *pdev);
static int consys_reg_deinit(void);
static int consys_check_reg_readable(void);
static int consys_check_reg_readable_for_coredump(void);
static int consys_is_consys_reg(unsigned int addr);
static int consys_is_bus_hang(void);

struct consys_base_addr g_conn_reg_mt6985;

struct consys_reg_mng_ops g_dev_consys_reg_ops_mt6985 = {
	.consys_reg_mng_init = consys_reg_init,
	.consys_reg_mng_deinit = consys_reg_deinit,
	.consys_reg_mng_check_reable = consys_check_reg_readable,
	.consys_reg_mng_check_reable_for_coredump = consys_check_reg_readable_for_coredump,
	.consys_reg_mng_is_bus_hang = consys_is_bus_hang,
	.consys_reg_mng_is_consys_reg = consys_is_consys_reg,
};

static const char* consys_base_addr_index_to_str[CONSYS_BASE_ADDR_MAX] = {
	"conn_cfg",
	"conn_host_csr_top",
	"conn_infra_sysram",
	"conn_infra_bus_cr",
	"conn_infra_rgu_on",
	"conn_wt_slp_ctl_reg",
	"conn_infra_cfg_on",
	"conn_infra_bus_cr_on",
	"conn_infra_off_debug_ctrl_ao",
	"conn_infra_clkgen_top",
	"conn_rf_spi_mst_reg",
	"ifrbus_ao_reg",
	"spm",
	"conn_semaphore",
	"conn_afe_ctl",
	"SRCLKENRC",
	"CONN_DBG_CTL",
};

int consys_reg_init(struct platform_device *pdev)
{
	int ret = -1;
	struct device_node *node = NULL;
	struct consys_reg_base_addr *base_addr = NULL;
	struct resource res;
	int flag, i = 0;

	node = pdev->dev.of_node;
	pr_info("[%s] node=[%p]\n", __func__, node);
	if (node) {
		for (i = 0; i < CONSYS_BASE_ADDR_MAX; i++) {
			base_addr = &g_conn_reg_mt6985.reg_base_addr[i];

			ret = of_address_to_resource(node, i, &res);
			if (ret) {
				pr_err("Get Reg Index(%d-%s) failed",
						i, consys_base_addr_index_to_str[i]);
				continue;
			}

			base_addr->phy_addr = res.start;
			base_addr->vir_addr =
				(unsigned long) of_iomap(node, i);
			of_get_address(node, i, &(base_addr->size), &flag);

			pr_info("Get Index(%d-%s) phy(0x%zx) baseAddr=(0x%zx) size=(0x%zx)",
				i, consys_base_addr_index_to_str[i], base_addr->phy_addr,
				base_addr->vir_addr, base_addr->size);
		}

	} else {
		pr_err("[%s] can't find CONSYS compatible node\n", __func__);
		return ret;
	}

	return 0;
}

static int consys_reg_deinit(void)
{
	int i = 0;

	for (i = 0; i < CONSYS_BASE_ADDR_MAX; i++) {
		if (g_conn_reg_mt6985.reg_base_addr[i].vir_addr) {
			pr_info("[%d] Unmap %s (0x%zx)",
				i, consys_base_addr_index_to_str[i],
				g_conn_reg_mt6985.reg_base_addr[i].vir_addr);
			iounmap((void __iomem*)g_conn_reg_mt6985.reg_base_addr[i].vir_addr);
			g_conn_reg_mt6985.reg_base_addr[i].vir_addr = 0;
		}
	}

	return 0;
}

int consys_check_ap2conn_infra_on(void)
{
	unsigned int tx, rx;
	/* Check ap2conn slpprot
	 * 0x1002_C004[25] / 0x1002_C00C[25](tx/rx) (sleep protect enable ready)
	 * both of them should be 1'b0
	 */

	tx = CONSYS_REG_READ(INFRBUS_AO_REG_BASE_ADDR_MT6985 + 0x4);
	rx = CONSYS_REG_READ(INFRBUS_AO_REG_BASE_ADDR_MT6985 + 0xc);
	if (tx & (0x1 << 25))
		return CONNINFRA_AP2CONN_TX_SLP_PROT_ERR;
	if (rx & (0x1 << 25))
		return CONNINFRA_AP2CONN_RX_SLP_PROT_ERR;

	return 0;
}

static int __consys_reg_clock_detect(void)
{
	unsigned int r = 0;

	unsigned int count = 0;

	/* Check conn_infra off bus clock */
	/* - write 0x1 to 0x1802_3000[0], reset clock detect */
	/* - 0x1802_3000[1]  conn_infra off bus clock (should be 1'b1 if clock exist) */
	/* - 0x1802_3000[2]  osc clock (should be 1'b1 if clock exist) */
	while (count < 4) {
		CONSYS_SET_BIT(CONN_DBG_CTL_CLOCK_DETECT_ADDR, (0x1 << 0));
		udelay(20);
		r = CONSYS_REG_READ_BIT(CONN_DBG_CTL_CLOCK_DETECT_ADDR, ((0x1 << 2) | (0x1 << 1)));
		if (r == 0x6)
			break;
		udelay(1000);
		count++;
	}

	if (r != 0x6) {
		pr_info("%s fail:0x1802_3000 = %x\n", __func__, r);
		return 0;
	}
	return 1;
}

int consys_check_ap2conn_infra_off_clock(void)
{

	/* 1.Check "AP2CONN_INFRA ON step is ok"
	 * 2. Check conn_infra off bus clock
	 *    (Need to polling 4 times to confirm the correctness and polling every 1ms)
	 * - write 0x1 to 0x1802_3000[0], reset clock detect
	 * - 0x1802_3000[1] conn_infra off bus clock (should be 1'b1 if clock exist)
	 * - 0x1802_3000[2] osc clock (should be 1'b1 if clock exist)
	 * 3. Read conn_infra IP version
	 * - Read 0x1801_1000 = 0x02050300
	 */
	if (!__consys_reg_clock_detect())
		return CONNINFRA_AP2CONN_CLK_ERR;
	if (CONSYS_REG_READ(CONN_CFG_IP_VERSION_ADDR) != CONSYS_CONN_HW_VER)
		return CONNINFRA_AP2CONN_CLK_ERR;
	return 0;
}

int consys_check_ap2conn_infra_off_irq(void)
{
	/* 4. Check conn_infra off domain bus hang irq status
	 * - 0x1802_3400[2:0], should be 3'b000, or means conn_infra off bus might hang
	 */
	int ret = -1;

	ret = CONSYS_REG_READ_BIT(CONN_DBG_CTL_CONN_INFRA_BUS_TIMEOUT_IRQ_ADDR,
			(0x1 << 0) | (0x1 << 1) | (0x1 << 2));

	return (ret == 0) ? 0 : CONNINFRA_INFRA_BUS_HANG_IRQ;
}

int consys_check_reg_readable(void)
{
	if (consys_check_ap2conn_infra_on())
		return 0;
	if (consys_check_ap2conn_infra_off_clock())
		return 0;
	if (consys_check_ap2conn_infra_off_irq())
		return 0;
	return 1;
}


int consys_check_reg_readable_for_coredump(void)
{
	if (consys_check_ap2conn_infra_on())
		return 0;
	return 1;
}

int consys_is_consys_reg(unsigned int addr)
{
	if (addr >= 0x18000000 && addr < 0x19000000)
		return 1;
	return 0;
}

int consys_is_bus_hang(void)
{
	int ret = 0;

	ret = consys_check_ap2conn_infra_on();
	if (ret) {
		pr_notice("[%s] ap2conn_infra_on fail", __func__);
		return ret;
	}

	ret = consys_check_ap2conn_infra_off_clock();
	if (ret)
		pr_info("[%s] ap2conn_infra_off clock fail", __func__);

	ret = consys_check_ap2conn_infra_off_irq();
	if (ret)
		pr_notice("[%s] ap2conn_infra_off timeout irq fail", __func__);

	return ret;
}
