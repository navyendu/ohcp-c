// File: ohcp_logic.h

#ifndef OHCP_LOGIC_H
#define OHCP_LOGIC_H

#include "ohcp_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OHCP_LOGIC_NAME "logic"
#define OHCP_LOGIC_NUM_STATES 4

#define OHCP_LOGIC_0 0
#define OHCP_LOGIC_1 1
#define OHCP_LOGIC_Z 2
#define OHCP_LOGIC_X 3

#define OHCP_LOGIC_0_LIT '0'
#define OHCP_LOGIC_1_LIT '1'
#define OHCP_LOGIC_Z_LIT 'z'
#define OHCP_LOGIC_X_LIT 'x'

extern const struct ohcp_type*  ohcp_logic;

int     ohcp_logic_init  (void);

#ifdef __cplusplus
}
#endif

#endif
