/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef _PLATFORM_MT6983_EMI_H_
#define _PLATFORM_MT6983_EMI_H_

int consys_emi_mpu_set_region_protection_mt6983(void);
void consys_emi_get_md_shared_emi_mt6983(phys_addr_t* base, unsigned int* size);

#endif /* _PLATFORM_MT6983_EMI_H_ */
