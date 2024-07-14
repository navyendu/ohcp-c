// File: ohcp_expr.h

#ifndef OHCP_EXPR_H
#define OHCP_EXPR_H

#include <stddef.h>

#include "ohcp_string.h"
#include "ohcp_forward.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef /* move */ ohcp_string* (* ohcp_expr_to_str_fptr_t)         (/* ref */ const ohcp_expr* expr);
typedef /* move */ ohcp_string* (* ohcp_expr_to_asgn_str_fptr_t)    (/* ref */ const ohcp_expr* expr);

typedef struct ohcp_expr_descr  ohcp_expr_descr;
struct ohcp_expr_descr
{
    const char*                     name;   // Watch out: char*
    ohcp_expr_to_str_fptr_t         to_str;
    ohcp_expr_to_asgn_str_fptr_t    to_asgn_str;
};

/* move */ ohcp_string*     ohcp_expr_descr_dump    (/* ref */ const ohcp_expr_descr* descr);

struct ohcp_expr
{
    const ohcp_expr_descr*  descr;
    
    ohcp_module*            parent;
    
    ohcp_deque*             param_list;
    ohcp_deque*             input_list;
    ohcp_node*              output;
};

/* move */ ohcp_expr*       ohcp_expr_create        (/* ref */ const ohcp_expr_descr* descr,
                                                     /* move */ ohcp_deque* param_list,
                                                     /* move */ ohcp_deque* input_list,
                                                     /* ref */ ohcp_node* output);
void                        ohcp_expr_destroy       (/* move */ const ohcp_expr* expr);

/* move */ ohcp_string*     ohcp_expr_dump          (/* ref */ const ohcp_expr* expr);
/* move */ ohcp_string*     ohcp_expr_to_str        (/* ref */ const ohcp_expr* expr);
/* move */ ohcp_string*     ohcp_expr_to_asgn_str   (/* ref */ const ohcp_expr* expr);

#ifdef __cplusplus
}
#endif

#endif
