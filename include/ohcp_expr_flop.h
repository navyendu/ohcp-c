// File: ohcp_expr_flop.h

#ifndef OHCP_EXPR_FLOP_H
#define OHCP_EXPR_FLOP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ohcp_forward.h"

/* move */ ohcp_node*   ohcp_expr_dff           (/* ref */ ohcp_node* clk, /* ref */ ohcp_node* d);
/* move */ ohcp_node*   ohcp_expr_dff_rst       (/* ref */ ohcp_node* clk, /* ref */ ohcp_node* rst, /* ref */ ohcp_node* d);
/* move */ ohcp_node*   ohcp_expr_dff_en        (/* ref */ ohcp_node* clk, /* ref */ ohcp_node* en, /* ref */ ohcp_node* d);
/* move */ ohcp_node*   ohcp_expr_dff_rst_en    (/* ref */ ohcp_node* clk, /* ref */ ohcp_node* rst,
                                                 /* ref */ ohcp_node* en, /* ref */ ohcp_node* d);

#ifdef __cplusplus
}
#endif

#endif
