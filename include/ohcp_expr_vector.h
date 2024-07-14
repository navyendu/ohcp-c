// File: ohcp_expr_vector.h

#ifndef OHCP_EXPR_VECTOR_H
#define OHCP_EXPR_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_vector_at     (/* ref */ const ohcp_node* node0, size_t index);
/* move */ ohcp_node*   ohcp_expr_vector_range  (/* ref */ const ohcp_node* node0, size_t start, size_t len);

/* move */ ohcp_node*   ohcp_expr_vector_cat    (size_t in_count, /* ref */ const ohcp_node* in_list []);
/* move */ ohcp_node*   ohcp_expr_vector_cat2   (/* ref */ const ohcp_node* node0, /* ref */ const ohcp_node* node1);

#ifdef __cplusplus
}
#endif

#endif
