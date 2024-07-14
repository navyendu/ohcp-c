// File: ohcp_expr_rel.h

#ifndef OHCP_EXPR_REL_H
#define OHCP_EXPR_REL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_eq    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);
/* move */ ohcp_node*   ohcp_expr_ne    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);

/* move */ ohcp_node*   ohcp_expr_lt    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);
/* move */ ohcp_node*   ohcp_expr_ge    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);

/* move */ ohcp_node*   ohcp_expr_gt    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);
/* move */ ohcp_node*   ohcp_expr_le    (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);

#ifdef __cplusplus
}
#endif

#endif
