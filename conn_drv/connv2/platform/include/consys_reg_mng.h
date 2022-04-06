/*  SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef _PLATFORM_CONSYS_REG_MNG_H_
#define _PLATFORM_CONSYS_REG_MNG_H_

#include <linux/platform_device.h>

#include "consys_hw.h"

enum conn_dump_cpupcr_type {
	CONN_DUMP_CPUPCR_TYPE_BT = 1,
	CONN_DUMP_CPUPCR_TYPE_WF = 2,
	CONN_DUMP_CPUPCR_TYPE_ALL = 3,
};

enum conninfra_bus_error_type
{
	CONNINFRA_POWER_ON_DOMAIN_INACCESSIBLE = 0,
	CONNINFRA_POWER_OFF_DOMAIN_INACCESSIBLE = 1,
	CONNINFRA_BUG_HANG_IRQ_OCCUR = 2,
};

struct consys_reg_mng_ops {
	int (*consys_reg_mng_init)(struct platform_device *pdev);
	int (*consys_reg_mng_deinit)(void);
	void (*consys_reg_mng_debug_init)(void);
	void (*consys_reg_mng_debug_deinit)(void);
	int (*consys_reg_mng_check_reable)(void);
	int (*consys_reg_mng_check_reable_for_coredump)(void);
	int (*consys_reg_mng_is_consys_reg)(unsigned int addr);

	int (*consys_reg_mng_is_bus_hang)(void);
	int (*consys_reg_mng_dump_bus_status)(void);
	int (*consys_reg_mng_dump_conninfra_status)(void);
	int (*consys_reg_mng_dump_cpupcr)(enum conn_dump_cpupcr_type, int times,
					  unsigned long interval_us);

	int (*consys_reg_mng_is_host_csr)(unsigned long addr);

	int (*consys_reg_mng_check_readable_conninfra_on_status)(void);
	int (*consys_reg_mng_check_readable_conninfra_off_status)(void);
	int (*consys_reg_mng_check_readable_conninfra_irq)(void);
	void (*consys_reg_mng_check_readable_conninfra_platform_log)(void);
	int (*consys_reg_mng_check_readable_conninfra_log)(int level);
	void (*consys_reg_mng_check_readable_conninfra_pmic_log)(void);
};

int consys_reg_mng_init(struct platform_device *pdev, const struct conninfra_plat_data *plat_data);
int consys_reg_mng_deinit(void);

int consys_reg_mng_reg_readable(void);
int consys_reg_mng_reg_readable_for_coredump(void);
int consys_reg_mng_is_connsys_reg(phys_addr_t addr);
int consys_reg_mng_reg_read(unsigned long addr, unsigned int *value, unsigned int mask);
int consys_reg_mng_reg_write(unsigned long addr, unsigned int value, unsigned int mask);
int consys_reg_mng_is_bus_hang(void);
int consys_reg_mng_dump_bus_status(void);
int consys_reg_mng_dump_conninfra_status(void);
int consys_reg_mng_dump_cpupcr(enum conn_dump_cpupcr_type dump_type, int times,
					  unsigned long interval_us);

int consys_reg_mng_is_host_csr(unsigned long addr);

#endif				/* _PLATFORM_CONSYS_REG_MNG_H_ */
