// File: ohcp_bit.h

#ifndef OHCP_BIT_H
#define OHCP_BIT_H

#include "ohcp_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OHCP_BIT_NAME "bit"
#define OHCP_BIT_NUM_STATES 2

#define OHCP_BIT_0 0
#define OHCP_BIT_1 1

#define OHCP_BIT_0_LIT '0'
#define OHCP_BIT_1_LIT '1'

extern const struct ohcp_type*  ohcp_bit;

int     ohcp_bit_init   (void);

#ifdef __cplusplus
}
#endif

#endif
