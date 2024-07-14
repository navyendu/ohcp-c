// File: ohcp_expr_mux.c

#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_expr_mux.h"

static ohcp_string* mux_to_str(/* ref */ const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* mux_to_asgn_str(/* ref */ const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr mux_descr = {
    .name = "mux",
    .to_str = mux_to_str,
    .to_asgn_str = mux_to_asgn_str
};

ohcp_node* ohcp_expr_mux(const ohcp_node* sel, size_t in_count, const ohcp_node* in_list [])
{
    const ohcp_type* out_type;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (sel == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): sel is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (in_count == 0) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): in_count is 0", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    for (size_t i = 0 ; i < in_count ; i++) {
        if (in_list[i] == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): in_list[%lu] is NULL", __func__, i);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
    }
    
    out_type = in_list[0]->type;
    for (size_t i = 1 ; i < in_count ; i++) {
        if (in_list[i]->type != out_type) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): in_list[%lu]->type != in_list[0].type", __func__, i);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
    }
    
    do {
        param_list = ohcp_deque_create();
        if (param_list == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            input_list = ohcp_deque_create();
            if (input_list == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to create input_list", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            // Ideally we should check the return value here :|
            ohcp_deque_push_back(input_list, sel);
            for (size_t i = 0 ; i < in_count ; i++) {
                ohcp_deque_push_back(input_list, in_list[i]);
            }
            
            do {
                output = ohcp_node_create(out_type, ohcp_string_create());
                if (output == NULL) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                do {
                    expr = ohcp_expr_create(&mux_descr, param_list, input_list, output);
                    if (expr == NULL) {
                        char    buf [1024];
                        int     ret;
                        size_t  len;
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
                        break;
                    }
                    
                    output->driver = expr;
                    
                    return output;
                } while (0);
                
                ohcp_node_destroy(output);
            } while (0);
            
            ohcp_deque_destroy(input_list);
        } while (0);
        
        ohcp_deque_destroy(param_list);
    } while (0);
    
    return NULL;
}

static ohcp_string* vmux_to_str(/* ref */ const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* vmux_to_asgn_str(/* ref */ const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr vmux_descr = {
    .name = "vmux",
    .to_str = vmux_to_str,
    .to_asgn_str = vmux_to_asgn_str
};

ohcp_node* ohcp_expr_vmux(const ohcp_node* sel, const ohcp_node* in_vec)
{
    const ohcp_type* out_type;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (sel == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): sel is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (in_vec == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): in_vec is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    out_type = ((const ohcp_typedescr_vector*) in_vec->type->descr)->base;
    
    do {
        param_list = ohcp_deque_create();
        if (param_list == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            input_list = ohcp_deque_create();
            if (input_list == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to create input_list", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            // Ideally we should check the return value here :|
            ohcp_deque_push_back(input_list, sel);
            ohcp_deque_push_back(input_list, in_vec);
            
            do {
                output = ohcp_node_create(out_type, ohcp_string_create());
                if (output == NULL) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                do {
                    expr = ohcp_expr_create(&vmux_descr, param_list, input_list, output);
                    if (expr == NULL) {
                        char    buf [1024];
                        int     ret;
                        size_t  len;
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
                        break;
                    }
                    
                    output->driver = expr;
                    
                    return output;
                } while (0);
                
                ohcp_node_destroy(output);
            } while (0);
            
            ohcp_deque_destroy(input_list);
        } while (0);
        
        ohcp_deque_destroy(param_list);
    } while (0);
    
    return NULL;
}
