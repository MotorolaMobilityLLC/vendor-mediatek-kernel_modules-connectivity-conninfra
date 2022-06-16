// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include <linux/of.h>
#include <linux/pm_runtime.h>
#include <linux/regmap.h>
#include <linux/types.h>

#include "osal.h"
#include "conninfra.h"
#include "conninfra_conf.h"
#include "consys_hw.h"
#include "consys_reg_mng.h"
#include "consys_reg_util.h"
#include "connsys_smc.h"

#include "include/mt6985.h"
#include "include/mt6985_pos.h"
#include "include/mt6985_consys_reg.h"
#include "include/mt6985_consys_reg_offset.h"
#include "include/mt6985_connsyslog.h"

#include "clock_mng.h"
#include "coredump_mng.h"

static int consys_clk_get_from_dts_mt6985(struct platform_device *pdev);
static int consys_clock_buffer_ctrl_mt6985(unsigned int enable);
static unsigned int consys_soc_chipid_get_mt6985(void);
static unsigned int consys_get_hw_ver_mt6985(void);
static int consys_init_atf_data_mt6985_atf(void);

struct consys_hw_ops_struct g_consys_hw_ops_mt6985 = {
	.consys_plt_init_atf_data = consys_init_atf_data_mt6985_atf,
	.consys_plt_clk_get_from_dts = consys_clk_get_from_dts_mt6985,
	.consys_plt_clock_buffer_ctrl = consys_clock_buffer_ctrl_mt6985,
	.consys_plt_co_clock_type = consys_co_clock_type_mt6985,
	/* POS */
	.consys_plt_conninfra_on_power_ctrl = consys_conninfra_on_power_ctrl_mt6985,
	.consys_plt_set_if_pinmux = consys_set_if_pinmux_mt6985,
	.consys_plt_polling_consys_chipid = consys_polling_chipid_mt6985,
	.consys_plt_d_die_cfg = connsys_d_die_cfg_mt6985,
	.consys_plt_spi_master_cfg = connsys_spi_master_cfg_mt6985,
	.consys_plt_subsys_pll_initial = connsys_subsys_pll_initial_mt6985,
	.consys_plt_low_power_setting = connsys_low_power_setting_mt6985,
	.consys_plt_soc_chipid_get = consys_soc_chipid_get_mt6985,
	.consys_plt_conninfra_wakeup = consys_conninfra_wakeup_mt6985,
	.consys_plt_conninfra_sleep = consys_conninfra_sleep_mt6985,
	.consys_plt_is_rc_mode_enable = consys_is_rc_mode_enable_mt6985,

	.consys_plt_clock_fail_dump = NULL, // consys_clock_fail_dump_mt6985,
	.consys_plt_get_hw_ver = consys_get_hw_ver_mt6985,
	.consys_plt_spi_read = consys_spi_read_mt6985,
	.consys_plt_spi_write = consys_spi_write_mt6985,
	.consys_plt_spi_update_bits = consys_spi_update_bits_mt6985,
	.consys_plt_spi_clock_switch = NULL, // consys_spi_clock_switch_mt6985,
	.consys_plt_subsys_status_update = consys_subsys_status_update_mt6985,

	.consys_plt_enable_power_dump = NULL, // consys_enable_power_dump_mt6985,
	.consys_plt_reset_power_state = NULL, // consys_power_state_dump_mt6985,
	.consys_plt_power_state = NULL, // consys_power_state_dump_mt6985,
	.consys_plt_soc_timestamp_get = NULL, // consys_soc_timestamp_get_mt6985,
	.consys_plt_adie_detection = consys_get_adie_chipid_mt6985,
	.consys_plt_set_mcu_control = NULL, //consys_set_mcu_control_mt6985,
};

extern struct consys_hw_ops_struct g_consys_hw_ops_mt6985;
extern struct consys_reg_mng_ops g_dev_consys_reg_ops_mt6985;
extern struct consys_platform_emi_ops g_consys_platform_emi_ops_mt6985;
extern struct consys_platform_pmic_ops g_consys_platform_pmic_ops_mt6985;
extern struct consys_platform_coredump_ops g_consys_platform_coredump_ops_mt6985;

const struct conninfra_plat_data mt6985_plat_data = {
	.chip_id = PLATFORM_SOC_CHIP_MT6985,
	.consys_hw_version = CONN_HW_VER_MT6985,
	.hw_ops = &g_consys_hw_ops_mt6985,
	.reg_ops = &g_dev_consys_reg_ops_mt6985,
	.platform_emi_ops = &g_consys_platform_emi_ops_mt6985,
	.platform_pmic_ops = &g_consys_platform_pmic_ops_mt6985,
	.platform_coredump_ops = &g_consys_platform_coredump_ops_mt6985,
	.connsyslog_config = &g_connsyslog_config_mt6985,
};


int consys_clk_get_from_dts_mt6985(struct platform_device *pdev)
{
	pm_runtime_enable(&pdev->dev);
	dev_pm_syscore_device(&pdev->dev, true);

	return 0;
}

int consys_platform_spm_conn_ctrl_mt6985(unsigned int enable)
{
	int ret = 0;
	struct platform_device *pdev = get_consys_device();

	if (!pdev) {
		pr_info("get_consys_device fail.\n");
		return -1;
	}

	if (enable) {
		ret = pm_runtime_get_sync(&(pdev->dev));
		if (ret)
			pr_info("pm_runtime_get_sync() fail(%d)\n", ret);
		else
			pr_info("pm_runtime_get_sync() CONSYS ok\n");

		ret = device_init_wakeup(&(pdev->dev), true);
		if (ret)
			pr_info("device_init_wakeup(true) fail.\n");
		else
			pr_info("device_init_wakeup(true) CONSYS ok\n");
	} else {
		ret = device_init_wakeup(&(pdev->dev), false);
		if (ret)
			pr_info("device_init_wakeup(false) fail.\n");
		else
			pr_info("device_init_wakeup(false) CONSYS ok\n");

		ret = pm_runtime_put_sync(&(pdev->dev));
		if (ret)
			pr_info("pm_runtime_put_sync() fail.\n");
		else
			pr_info("pm_runtime_put_sync() CONSYS ok\n");
	}

	return ret;
}

int consys_clock_buffer_ctrl_mt6985(unsigned int enable)
{
	return 0;
}

unsigned int consys_soc_chipid_get_mt6985(void)
{
	return PLATFORM_SOC_CHIP_MT6985;
}

unsigned int consys_get_adie_chipid_mt6985(void)
{
	return CONNSYS_A_DIE_ID_MT6985;
}

unsigned int consys_get_hw_ver_mt6985(void)
{
	return CONN_HW_VER_MT6985;
}

int consys_co_clock_type_mt6985(void)
{
	const struct conninfra_conf *conf;
	/* In 6985, clock for connsys is always 26M (RFCK2B).
	 * We don't read clock ic register to indetify clock rate.
	 */
	int clock_type = CONNSYS_CLOCK_SCHEMATIC_26M_COTMS;
	unsigned char tcxo_gpio = 0;

	/* Default solution */
	conf = conninfra_conf_get_cfg();
	if (NULL == conf)
		pr_err("[%s] Get conf fail", __func__);
	else
		tcxo_gpio = conf->tcxo_gpio;

	if (tcxo_gpio != 0 || conn_hw_env.tcxo_support)
		clock_type = CONNSYS_CLOCK_SCHEMATIC_26M_EXTCXO;
	pr_info("[%s] conf->tcxo_gpio=%d conn_hw_env.tcxo_support=%d, %s",
		__func__, tcxo_gpio, conn_hw_env.tcxo_support,
		clock_mng_get_schematic_name(clock_type));

	return clock_type;
}

int consys_init_atf_data_mt6985_atf(void)
{
	struct arm_smccc_res res;
	int platform_config;
	static bool initialized = 0;
	int ret;

	if (initialized == 1)
		return 0;

	platform_config = consys_hw_get_platform_config();
	arm_smccc_smc(MTK_SIP_KERNEL_CONNSYS_CONTROL, SMC_CONNSYS_INIT_ATF_DATA_OPID,
		platform_config, conn_hw_env.clock_type, 0, 0, 0, 0, &res);
	ret = res.a0;
	initialized = 1;
	return ret;
}
