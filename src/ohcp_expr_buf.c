// File: ohcp_expr_buf.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohcp_stats.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_expr_buf.h"

static ohcp_string* buf_to_str(/* ref */ const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* buf_to_asgn_str(/* ref */ const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr buf_descr = {
    .name = "buf",
    .to_str = buf_to_str,
    .to_asgn_str = buf_to_asgn_str
};

ohcp_node* ohcp_expr_buf(ohcp_node* node)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
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
            ohcp_deque_push_back(input_list, node);
            
            do {
                output = ohcp_node_create(node->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&buf_descr, param_list, input_list, output);
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
