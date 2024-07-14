// File: ohcp_expr_vector.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_module.h"
#include "ohcp_expr_vector.h"

// ohcp_vector_at ----------------------------------------------------------- //

static ohcp_string* vector_at_to_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    const ohcp_node* input;
    const size_t* index;
    
    if (expr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): expr is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (expr->input_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): expr->input_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    for (const ohcp_deque_entry* de = ohcp_deque_first(expr->input_list) ; de != NULL ; de = de->next) {
        input = (const ohcp_node*) de->data;
    }
    
    for (const ohcp_deque_entry* de = ohcp_deque_first(expr->param_list) ; de != NULL ; de = de->next) {
        index = (const size_t*) de->data;
    }
    
    if (input == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): input is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (index == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): index is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s[%lu]", ohcp_string_cstr(input->name), *index);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        str = ohcp_string_create_lcstr(len, buf);
    }
    
    return str;
}

static ohcp_string* vector_at_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr vector_at_descr = {
    .name = "vector_at",
    .to_str = vector_at_to_str,
    .to_asgn_str = vector_at_to_asgn_str
};

ohcp_node* ohcp_expr_vector_at(const ohcp_node* node0, size_t index)
{
    const ohcp_typedescr_vector* node0_type_descr;
    const ohcp_type* out_type;
    ohcp_node* out_node;
    size_t* index_copy;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %lu): node0 is null",
            __func__, index);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type->typetype != OHCP_TYPETYPE_VECTOR) {
        char buf [1024];
        int ret;
        size_t len;
        ohcp_string* fname;
        
        fname = ohcp_module_full_name(node0->parent, node0);
        
        ret = snprintf(buf, sizeof(buf),
            "%s(%s, %lu): Vector subscript operation can only be applied on a vector",
            __func__, ohcp_string_cstr(fname), index);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        ohcp_string_destroy(fname);
        
        return NULL;
    }
    
    node0_type_descr = (ohcp_typedescr_vector*) node0->type->descr;
    if (index >= node0_type_descr->size) {
        char    buf [1024];
        int     ret;
        size_t  len;
        ohcp_string* fname;
        
        fname = ohcp_module_full_name(node0->parent, node0);
        
        ret = snprintf(buf, sizeof(buf), "%s(%s, %lu): Index %lu is out of range",
            __func__, ohcp_string_cstr(fname), index, index);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        ohcp_string_destroy(fname);
        
        return NULL;
    }
    
    do {
        index_copy = malloc(sizeof(size_t));
        if (index_copy == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc index_buf", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        *index_copy = index;
        
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
            
            ohcp_deque_push_back(param_list, index_copy);
            
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
                
                ohcp_deque_push_back(input_list, node0);
                
                do {
                    out_type = node0_type_descr->base;
                    
                    out_node = ohcp_node_create(out_type, ohcp_string_create());
                    if (out_node == NULL) {
                        char    buf [1024];
                        int     ret;
                        size_t  len;
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
                        break;
                    }
                    
                    do {
                        expr = ohcp_expr_create(&vector_at_descr, param_list, input_list, out_node);
                        if (expr == NULL) {
                            char    buf [1024];
                            int     ret;
                            size_t  len;
                            
                            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create expr", __func__);
                            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                            
                            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                            
                            break;
                        }
                        
                        out_node->driver = expr;
                        
                        return out_node;
                    } while (0);
                    
                    ohcp_node_destroy(out_node);
                } while (0);
                
                ohcp_deque_destroy(input_list);
            } while (0);
            
            ohcp_deque_destroy(param_list);
        } while (0);
        
        free(index_copy);
    } while (0);
    
    return NULL;
}

// ohcp_vector_range -------------------------------------------------------- //

static ohcp_string* vector_range_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_string* vector_range_to_asgn_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_expr_descr vector_range_descr = {
    .name = "vector_range",
    .to_str = vector_range_to_str,
    .to_asgn_str = vector_range_to_asgn_str
};

ohcp_node* ohcp_expr_vector_range(const ohcp_node* node0, size_t start, size_t range_len)
{
    const ohcp_typedescr_vector* node0_type_descr;
    size_t* start_copy;
    size_t* range_len_copy;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    const ohcp_type* out_type;
    ohcp_node* out_node;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type->typetype != OHCP_TYPETYPE_VECTOR) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): vector_range() can only be applied on a vector", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    node0_type_descr = (const ohcp_typedescr_vector*) node0->type->descr;
    if (start >= node0_type_descr->size) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(start: %lu, %lu): start is out of range", __func__, start, range_len);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (start + range_len > node0_type_descr->size) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(start: %lu, %lu): start+len is out of range", __func__, start, range_len);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        start_copy = malloc(sizeof(size_t));
        if (start_copy == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc start_copy", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        *start_copy = start;
        
        do {
            range_len_copy = malloc(sizeof(size_t));
            if (range_len_copy == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc range_len_copy", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            *range_len_copy = range_len;
            
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
                
                ohcp_deque_push_back(param_list, start_copy);
                ohcp_deque_push_back(param_list, range_len_copy);
                
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
                    
                    ohcp_deque_push_back(input_list, node0);
                    
                    do {
                        out_type = ohcp_type_create_vector(range_len, node0_type_descr->base);
                        
                        out_node = ohcp_node_create(out_type, ohcp_string_create());
                        if (out_node == NULL) {
                            char    buf [1024];
                            int     ret;
                            size_t  len;
                            
                            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
                            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                            
                            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                            
                            break;
                        }
                        
                        do {
                            expr = ohcp_expr_create(&vector_range_descr, param_list, input_list, out_node);
                            if (expr == NULL) {
                                char    buf [1024];
                                int     ret;
                                size_t  len;
                                
                                ret = snprintf(buf, sizeof(buf), "%s(): Failed to create expr", __func__);
                                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                                
                                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                                
                                break;
                            }
                            
                            out_node->driver = expr;
                            
                            return out_node;
                        } while (0);
                        
                        ohcp_node_destroy(out_node);
                    } while (0);
                    
                    ohcp_deque_destroy(input_list);
                } while (0);
                
                ohcp_deque_destroy(param_list);
            } while (0);
            
            free(range_len_copy);
        } while (0);
        
        free(start_copy);
    } while (0);
    
    return NULL;
}

// ohcp_vector_cat ---------------------------------------------------------- //

static ohcp_string* vector_cat_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_string* vector_cat_to_asgn_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_expr_descr vector_cat_descr = {
    .name = "vector_cat",
    .to_str = vector_cat_to_str,
    .to_asgn_str = vector_cat_to_asgn_str
};

ohcp_node* ohcp_expr_vector_cat(size_t in_count, const ohcp_node* in_list[])
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_type* out_type;
    const ohcp_type* base_type;
    size_t final_size;
    ohcp_node* out_node;
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
    
    if (in_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): in_list is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    base_type = NULL;
    final_size = 0;
    for (size_t i = 0 ; i < in_count ; i++) {
        const ohcp_node* node;
        const ohcp_typedescr_vector* node_type_descr;
        
        node = in_list[i];
        if (node == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): node inside input_list is NULL", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        if (node->type->typetype != OHCP_TYPETYPE_VECTOR) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): vector_cat can only operate on vectors", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        node_type_descr = (const ohcp_typedescr_vector*) node->type->descr;
        
        if (base_type == NULL) {
            // First node in the queue
            base_type = node_type_descr->base;
        } else {
            if (node_type_descr->base != base_type) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf),
                    "%s(): vector_cat can only concatenate vectors of the same base type", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
                return NULL;
            }
        }
        
        final_size += node_type_descr->size;
    }
    
    do {
        param_list = ohcp_deque_create();
        if (param_list == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
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
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            for (size_t i = 0 ; i < in_count ; i++) {
                ohcp_deque_push_back(input_list, in_list[i]);
            }
            
            do {
                out_type = ohcp_type_create_vector(final_size, base_type);
                if (out_type == NULL) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                do {
                    out_node = ohcp_node_create(out_type, ohcp_string_create());
                    if (out_node == NULL) {
                        char    buf [1024];
                        int     ret;
                        size_t  len;
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
                        break;
                    }
                    
                    do {
                        expr = ohcp_expr_create(&vector_cat_descr, param_list, input_list, out_node);
                        if (expr == NULL) {
                            char    buf [1024];
                            int     ret;
                            size_t  len;
                            
                            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create expr", __func__);
                            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                            
                            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                            
                            break;
                        }
                        
                        out_node->driver = expr;
                        
                        return out_node;
                    } while (0);
                    
                    ohcp_node_destroy(out_node);
                } while (0);
                
                ohcp_type_destroy(out_type);
            } while (0);
            
            ohcp_deque_destroy(input_list);
        } while (0);
            
        ohcp_deque_destroy(param_list);
    } while (0);
    
    return NULL;
}

// ohcp_node* ohcp_expr_vector_catq(ohcp_deque* input_list)
// {
//     ohcp_deque* param_list;
//     ohcp_type* out_type;
//     const ohcp_type* base_type;
//     size_t final_size;
//     ohcp_node* out_node;
//     ohcp_expr* expr;
    
//     if (input_list == NULL) {
//         char    buf [1024];
//         int     ret;
//         size_t  len;
        
//         ret = snprintf(buf, sizeof(buf), "%s(): input_list is NULL", __func__);
//         len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
//         ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
//         return NULL;
//     }
    
//     base_type = NULL;
//     final_size = 0;
//     for (ohcp_deque_entry* de = ohcp_deque_first(input_list) ; de != NULL ; de = de->next) {
//         const ohcp_node* node;
//         const ohcp_typedescr_vector* node_type_descr;
        
//         node = (const ohcp_node*) de->data;
//         if (node == NULL) {
//             char    buf [1024];
//             int     ret;
//             size_t  len;
            
//             ret = snprintf(buf, sizeof(buf), "%s(): node inside input_list is NULL", __func__);
//             len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
//             ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
//             return NULL;
//         }
        
//         node_type_descr = (const ohcp_typedescr_vector*) node->type->descr;
        
//         if (node->type->typetype != OHCP_TYPETYPE_VECTOR) {
//             char    buf [1024];
//             int     ret;
//             size_t  len;
            
//             ret = snprintf(buf, sizeof(buf), "%s(): vector_cat can only operate on vectors", __func__);
//             len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
//             ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
//             return NULL;
//         }
        
//         if (base_type == NULL) {
//             // First node in the queue
//             base_type = node_type_descr->base;
//         } else {
//             if (node_type_descr->base != base_type) {
//                 char    buf [1024];
//                 int     ret;
//                 size_t  len;
                
//                 ret = snprintf(buf, sizeof(buf),
//                     "%s(): vector_cat can only concatenate vectors of the same base type", __func__);
//                 len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
//                 ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
                
//                 return NULL;
//             }
//         }
        
//         final_size += node_type_descr->size;
//     }
    
//     do {
//         param_list = ohcp_deque_create();
//         if (param_list == NULL) {
//             char    buf [1024];
//             int     ret;
//             size_t  len;
            
//             ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
//             len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
//             ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
//             break;
//         }
        
//         do {
//             out_type = ohcp_type_create_vector(final_size, base_type);
//             if (out_type == NULL) {
//                 char    buf [1024];
//                 int     ret;
//                 size_t  len;
                
//                 ret = snprintf(buf, sizeof(buf), "%s(): Failed to create param_list", __func__);
//                 len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
//                 ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
//                 break;
//             }
            
//             do {
//                 out_node = ohcp_node_create(out_type, ohcp_string_create());
//                 if (out_node == NULL) {
//                     char    buf [1024];
//                     int     ret;
//                     size_t  len;
                    
//                     ret = snprintf(buf, sizeof(buf), "%s(): Failed to create output_node", __func__);
//                     len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
//                     ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
//                     break;
//                 }
                
//                 do {
//                     expr = ohcp_expr_create(&vector_cat_descr, param_list, input_list, out_node);
//                     if (expr == NULL) {
//                         char    buf [1024];
//                         int     ret;
//                         size_t  len;
                        
//                         ret = snprintf(buf, sizeof(buf), "%s(): Failed to create expr", __func__);
//                         len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
//                         ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
//                         break;
//                     }
                    
//                     out_node->driver = expr;
                    
//                     return out_node;
//                 } while (0);
                
//                 ohcp_node_destroy(out_node);
//             } while (0);
            
//             ohcp_type_destroy(out_type);
//         } while (0);
        
//         ohcp_deque_destroy(param_list);
//     } while (0);
    
//     return NULL;
// }

ohcp_node* ohcp_expr_vector_cat2(const ohcp_node* node0, const ohcp_node* node1)
{
    const ohcp_node* in_list [2];
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    in_list[0] = node0;
    in_list[1] = node1;
    
    do {
        ohcp_node* out_node;
        
        out_node = ohcp_expr_vector_cat(2, in_list);
        if (out_node == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): ohcp_expr_vector_cat returned NULL", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        return out_node;
    } while (0);
    
    return NULL;
}
