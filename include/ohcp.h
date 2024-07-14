// File: ohcp.h

#ifndef OHCP_H
#define OHCP_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "ohcp_string.h"
#include "ohcp_deque.h"
#include "ohcp_stats.h"
#include "ohcp_forward.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_port.h"
#include "ohcp_expr.h"
#include "ohcp_module.h"

#include "ohcp_logic.h"

#include "ohcp_expr_vector.h"
#include "ohcp_expr_struct.h"
#include "ohcp_expr_buf.h"
#include "ohcp_expr_inv.h"
#include "ohcp_expr_and.h"
#include "ohcp_expr_or.h"
#include "ohcp_expr_xor.h"
#include "ohcp_expr_mux.h"
#include "ohcp_expr_rel.h"
#include "ohcp_expr_flop.h"

int     ohcp_init       ();
void    ohcp_cleanup    ();

#endif
