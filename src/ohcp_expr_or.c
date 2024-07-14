// File: ohcp_expr_or.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_expr_or.h"

static ohcp_string* or_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* or_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr or_descr = {
    .name = "or",
    .to_str = or_to_str,
    .to_asgn_str = or_to_asgn_str
};

ohcp_node* ohcp_expr_or(size_t in_count, const ohcp_node* in_list [])
{
    const ohcp_type* out_type;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
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
                    expr = ohcp_expr_create(&or_descr, param_list, input_list, output);
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

// ohcp_node* ohcp_expr_orq(ohcp_deque* input_list)
// {
//     ohcp_deque* param_list;
//     ohcp_node* output;
//     ohcp_expr* expr;
//     ohcp_deque_entry* first_de;
//     ohcp_node* first_node;
    
//     if (input_list == NULL) {
//         char    buf [1024];
//         int     ret;
//         size_t  len;
        
//         ret = snprintf(buf, sizeof(buf), "%s(): input_list is null", __func__);
//         len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
//         ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
//         return NULL;
//     }
    
//     first_de = ohcp_deque_first(input_list);
//     if (first_de == NULL) {
//         char    buf [1024];
//         int     ret;
//         size_t  len;
        
//         ret = snprintf(buf, sizeof(buf), "%s(): first_de is null", __func__);
//         len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
//         ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
//         return NULL;
//     }
    
//     first_node = (ohcp_node*) first_de->data;
//     if (first_node == NULL) {
//         char    buf [1024];
//         int     ret;
//         size_t  len;
        
//         ret = snprintf(buf, sizeof(buf), "%s(): first_node is null", __func__);
//         len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
//         ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
//         return NULL;
//     }
    
//     // if (node0->type != node1->type) {
//     //     char    buf [1024];
//     //     int     ret;
//     //     size_t  len;
        
//     //     ohcp_string* left_type;
//     //     ohcp_string* right_type;
        
//     //     left_type = ohcp_type_to_str(node0->type);
//     //     right_type = ohcp_type_to_str(node1->type);
        
//     //     ret = snprintf(buf, sizeof(buf),
//     //         "%s(): Addition requires nodes to be of the same type. LHS: %s, RHS: %s",
//     //         __func__, ohcp_string_cstr(left_type), ohcp_string_cstr(right_type));
//     //     len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
//     //     ohcp_string_destroy(left_type);
//     //     ohcp_string_destroy(right_type);
        
//     //     ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
//     //     return NULL;
//     // }
    
//     do {
//         param_list = ohcp_deque_create();
//         if (param_list == NULL) {
//             char    buf [1024];
//             int     ret;
//             size_t  len;
            
//             ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
//             len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
//             ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
//             break;
//         }
        
//         do {
//             output = ohcp_node_create(first_node->type, ohcp_string_create());
//             if (output == NULL) {
//                 char    buf [1024];
//                 int     ret;
//                 size_t  len;
                
//                 ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output", __func__);
//                 len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
//                 ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
//                 break;
//             }
            
//             do {
//                 expr = ohcp_expr_create(&or_descr, param_list, input_list, output);
//                 if (expr == NULL) {
//                     char    buf [1024];
//                     int     ret;
//                     size_t  len;
                    
//                     ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
//                     len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
//                     ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
//                     break;
//                 }
                
//                 output->driver = expr;
                
//                 return output;
//             } while (0);
            
//             ohcp_node_destroy(output);
//         } while (0);
        
//         ohcp_deque_destroy(param_list);
//     } while (0);
    
//     return NULL;
// }

ohcp_node* ohcp_expr_or2(const ohcp_node* node0, const ohcp_node* node1)
{
    const ohcp_node* in_list [2];
    
    in_list[0] = node0;
    in_list[1] = node1;
    
    return ohcp_expr_or(2, in_list);
}

ohcp_node* ohcp_expr_or3(const ohcp_node* node0, const ohcp_node* node1,
    const ohcp_node* node2)
{
    const ohcp_node* in_list [3];
    
    in_list[0] = node0;
    in_list[1] = node1;
    in_list[2] = node2;
    
    return ohcp_expr_or(3, in_list);
}

ohcp_node* ohcp_expr_or4(const ohcp_node* node0, const ohcp_node* node1,
    const ohcp_node* node2, const ohcp_node* node3)
{
    const ohcp_node* in_list [4];
    
    in_list[0] = node0;
    in_list[1] = node1;
    in_list[2] = node2;
    in_list[3] = node3;
    
    return ohcp_expr_or(4, in_list);
}

// -------------------------------------------------------------------------- //

static ohcp_string* red_or_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* red_or_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr red_or_descr = {
    .name = "redor",
    .to_str = red_or_to_str,
    .to_asgn_str = red_or_to_asgn_str
};

ohcp_node* ohcp_expr_red_or(const ohcp_node* in_vec)
{
    const ohcp_type* out_type;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (in_vec == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): in_vec is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (in_vec->type == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): in_vec->type is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (in_vec->type->typetype != OHCP_TYPETYPE_VECTOR) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): Reduction AND can only be applied on a vector", __func__);
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
                    expr = ohcp_expr_create(&red_or_descr, param_list, input_list, output);
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
