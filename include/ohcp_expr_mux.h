// ohcp_expr_mux.h

#ifndef OHCP_EXPR_MUX_H
#define OHCP_EXPR_MUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_mux   (/* ref */ const ohcp_node* sel, size_t in_count,
                                         /* ref */ const ohcp_node* in_vec[]);
/* move */ ohcp_node*   ohcp_expr_vmux  (/* ref */ const ohcp_node* sel, /* ref */ const ohcp_node* in_vec);

#ifdef __cplusplus
}
#endif

#endif
