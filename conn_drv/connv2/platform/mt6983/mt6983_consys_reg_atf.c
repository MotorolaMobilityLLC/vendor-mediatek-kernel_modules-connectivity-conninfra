// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include <linux/platform_device.h>

#include "consys_reg_mng.h"
#include "mt6983_atf.h"
#include "mt6983_consys_reg.h"
#include "mt6983_pmic.h"

static void consys_debug_init_mt6983_atf(void);
static void consys_debug_deinit_mt6983_atf(void);

static int consys_check_conninfra_off_domain_status_mt6983_atf(void);
static int consys_check_conninfra_irq_status_mt6983_atf(void);
static int consys_print_debug_mt6983_atf(int level);


struct consys_reg_mng_ops g_dev_consys_reg_ops_mt6983_atf = {
	.consys_reg_mng_init = consys_reg_init_mt6983,
	.consys_reg_mng_deinit = consys_reg_deinit_mt6983,
	.consys_reg_mng_debug_init = consys_debug_init_mt6983_atf,
	.consys_reg_mng_debug_deinit = consys_debug_deinit_mt6983_atf,

	.consys_reg_mng_is_consys_reg = consys_is_consys_reg_mt6983,

	.consys_reg_mng_check_readable_conninfra_on_status
		= consys_check_conninfra_on_domain_status_mt6983,
	.consys_reg_mng_check_readable_conninfra_off_status
		= consys_check_conninfra_off_domain_status_mt6983_atf,
	.consys_reg_mng_check_readable_conninfra_irq
		= consys_check_conninfra_irq_status_mt6983_atf,
	.consys_reg_mng_check_readable_conninfra_platform_log = consys_print_platform_debug_mt6983,
	.consys_reg_mng_check_readable_conninfra_log = consys_print_debug_mt6983_atf,
	.consys_reg_mng_check_readable_conninfra_pmic_log = consys_pmic_debug_log_mt6983,
};

static int consys_print_debug_mt6983_atf(int level)
{
	int ret;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_PRINT_DEBUG_MT6983_OPID, level, 0, 0, 0, 0, 0, ret);
	return ret;
}

static int consys_check_conninfra_off_domain_status_mt6983_atf(void)
{
	int ret;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_CHECK_CONNINFRA_OFF_DOMAIN_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

static int consys_check_conninfra_irq_status_mt6983_atf(void)
{
	int ret;
	CONNSYS_SMC_CALL_RET(SMC_CONNSYS_CHECK_CONNINFRA_IRQ_STATUS_OPID, 0, 0, 0, 0, 0, 0, ret);
	return ret;
}

static void consys_debug_init_mt6983_atf(void)
{
	CONNSYS_SMC_CALL_VOID(SMC_CONNSYS_DEBUG_INIT_MT6983_OPID, 0, 0, 0, 0, 0, 0);
}

static void consys_debug_deinit_mt6983_atf(void)
{
	CONNSYS_SMC_CALL_VOID(SMC_CONNSYS_DEBUG_DEINIT_MT6983_OPID, 0, 0, 0, 0, 0, 0);
}

