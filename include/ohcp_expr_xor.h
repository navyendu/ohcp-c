// File: ohcp_expr_xor.h

#ifndef OHCP_EXPR_XOR_H
#define OHCP_EXPR_XOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_xor       (size_t in_count, /* ref */ const ohcp_node* in_list []);
/* move */ ohcp_node*   ohcp_expr_xor2      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);
/* move */ ohcp_node*   ohcp_expr_xor3      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1,
                                             /* ref */ const ohcp_node* node2);
/* move */ ohcp_node*   ohcp_expr_xor4      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1,
                                             /* ref */ const ohcp_node* node2, /* ref */ const ohcp_node* node3);

/* move */ ohcp_node*   ohcp_expr_red_xor   (/* ref */ const ohcp_node* in_vec);

#ifdef __cplusplus
}
#endif

#endif
