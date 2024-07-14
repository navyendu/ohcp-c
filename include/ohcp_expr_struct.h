// File: ohcp_expr_struct.h

#ifndef OHCP_EXPR_STRUCT_H
#define OHCP_EXPR_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_string.h"
#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_struct_at         (/* ref */ const ohcp_node* node0, /* move */ const ohcp_string* name);
/* move */ ohcp_node*   ohcp_expr_struct_at_cstr    (/* ref */ const ohcp_node* node0, /* move */ const char* name);

/* move */ ohcp_node*   ohcp_expr_struct_cat        (/* ref */ const ohcp_type* type,
                                                     size_t in_count, /* ref */ const ohcp_node* in_list []);

#ifdef __cplusplus
}
#endif

#endif
