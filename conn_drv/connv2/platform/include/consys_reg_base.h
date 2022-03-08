/*  SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef _PLATFORM_CONSYS_REG_BASE_H_
#define _PLATFORM_CONSYS_REG_BASE_H_

struct consys_reg_base_addr {
	unsigned long vir_addr;
	unsigned long phy_addr;
	unsigned long long size;
};

#endif				/* _PLATFORM_CONSYS_REG_BASE_H_ */
