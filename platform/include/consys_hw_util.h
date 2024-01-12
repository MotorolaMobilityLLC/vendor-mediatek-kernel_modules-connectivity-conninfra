/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
/*! \file
*    \brief  Declaration of library functions
*
*    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
*/

#ifndef _PLATFORM_CONSYS_HW_UTIL_H_
#define _PLATFORM_CONSYS_HW_UTIL_H_

#include <sync_write.h>
#include "osal.h"
/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

#define KBYTE (1024*sizeof(char))
#define CONSYS_SET_BIT(REG, BITVAL) (*((volatile unsigned int *)(REG)) |= ((unsigned int)(BITVAL)))
#define CONSYS_CLR_BIT(REG, BITVAL) ((*(volatile unsigned int *)(REG)) &= ~((unsigned int)(BITVAL)))
#define CONSYS_CLR_BIT_WITH_KEY(REG, BITVAL, KEY) {\
	unsigned int val = (*(volatile unsigned int *)(REG)); \
	val &= ~((unsigned int)(BITVAL)); \
	val |= ((unsigned int)(KEY)); \
	(*(volatile unsigned int *)(REG)) = val;\
}
#define CONSYS_REG_READ(addr) (*((volatile unsigned int *)(addr)))
#define CONSYS_REG_WRITE(addr, data)  mt_reg_sync_writel(data, addr)
#define CONSYS_REG_WRITE_RANGE(reg, data, end, begin) {\
	unsigned int val = CONSYS_REG_READ(reg); \
	SET_BIT_RANGE(&val, data, end, begin); \
	CONSYS_REG_WRITE(reg, val); \
}
#define CONSYS_REG_WRITE_MASK(reg, data, mask) {\
	unsigned int val = CONSYS_REG_READ(reg); \
	SET_BIT_MASK(&val, data, mask); \
	CONSYS_REG_WRITE(reg, val); \
}

/*
 * Write value with value_offset bits of right shift and size bits,
 * to the reg_offset-th bit of address reg
 * value  -----------XXXXXXXXXXXX-------------------
 *                   |<--size-->|<--value_offset-->|
 * reg    -------------OOOOOOOOOOOO-----------------
 *                     |<--size-->|<--reg_offset-->|
 * result -------------XXXXXXXXXXXX-----------------
 */
#define CONSYS_REG_WRITE_OFFSET_RANGE(reg, value, reg_offset, value_offset, size) ({\
	unsigned int data = (value) >> (value_offset); \
	data = GET_BIT_RANGE(data, size, 0); \
	data = data << (reg_offset); \
	CONSYS_REG_WRITE_RANGE(reg, data, ((reg_offset) + ((size) - 1)), reg_offset); \
})

#define CONSYS_REG_WRITE_BIT(reg, offset, val) CONSYS_REG_WRITE_OFFSET_RANGE(reg, ((val) & 1), offset, 0, 1)


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


/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif				/* _PLATFORM_CONSYS_HW_UTIL_H_ */
