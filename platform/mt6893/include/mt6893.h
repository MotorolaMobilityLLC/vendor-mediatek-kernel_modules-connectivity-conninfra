/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#ifndef _PLATFORM_MT6893_H_
#define _PLATFORM_MT6893_H_

int consys_platform_spm_conn_ctrl(unsigned int enable);
int consys_co_clock_type(void);

struct consys_plat_thermal_data {
	int thermal_b;
	int slop_molecule;
	int offset;
};

void update_thermal_data(struct consys_plat_thermal_data* input);
#endif /* _PLATFORM_MT6893_H_ */
