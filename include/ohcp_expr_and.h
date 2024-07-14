// File: ohcp_expr_and.h

#ifndef OHCP_EXPR_AND_H
#define OHCP_EXPR_AND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_and       (size_t in_count, /* ref */ const ohcp_node* in_list []);
/* move */ ohcp_node*   ohcp_expr_and2      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);
/* move */ ohcp_node*   ohcp_expr_and3      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1,
                                             /* ref */ const ohcp_node* node2);
/* move */ ohcp_node*   ohcp_expr_and4      (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1,
                                             /* ref */ const ohcp_node* node2, /* ref */ const ohcp_node* node3);

/* move */ ohcp_node*   ohcp_expr_red_and   (/* ref */ const ohcp_node* in_vec);

#ifdef __cplusplus
}
#endif

#endif
