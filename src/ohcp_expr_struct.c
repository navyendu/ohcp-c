// File: ohcp_expr_struct.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_module.h"
#include "ohcp_expr_struct.h"

// ohcp_struct_at ------------------------------------------------------------ //

static ohcp_string* struct_at_to_str(const ohcp_expr* expr)
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

static ohcp_string* struct_at_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr struct_at_descr = {
    .name = "struct_at",
    .to_str = struct_at_to_str,
    .to_asgn_str = struct_at_to_asgn_str
};

ohcp_node* ohcp_expr_struct_at(const ohcp_node* node0, const ohcp_string* name)
{
    const ohcp_typedescr_struct* node0_type_descr;
    bool found;
    const ohcp_struct_field* field;
    const ohcp_type* out_type;
    ohcp_node* out_node;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_expr* expr;
    
    if (name == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): name is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): node0 is null",
            __func__, ohcp_string_cstr(name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): node0->type is null",
            __func__, ohcp_string_cstr(name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type->typetype != OHCP_TYPETYPE_STRUCT) {
        char buf [1024];
        int ret;
        size_t len;
        ohcp_string* fname;
        
        fname = ohcp_module_full_name(node0->parent, node0);
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): Tuple subscript operation can only be applied on a struct",
            __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        ohcp_string_destroy(fname);
        
        return NULL;
    }
    
    node0_type_descr = (ohcp_typedescr_struct*) node0->type->descr;
    if (node0_type_descr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): node0_type_descr is null",
            __func__, ohcp_string_cstr(name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0_type_descr->field_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): node0_type_descr->field_list is null",
            __func__, ohcp_string_cstr(name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    found = false;
    for (ohcp_deque_entry* de = ohcp_deque_first(node0_type_descr->field_list) ; de != NULL ; de = de->next) {
        if (de->data == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): de->data is null",
                __func__, ohcp_string_cstr(name));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        field = (const ohcp_struct_field*) de->data;
        if (strcmp(ohcp_string_cstr(field->name), ohcp_string_cstr(name))) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(NULL, %s): No field \"%s\" found in struct",
            __func__, ohcp_string_cstr(name), ohcp_string_cstr(name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
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
        
        ohcp_deque_push_back(param_list, field);
        
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
                out_type = field->base;
                
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
                    expr = ohcp_expr_create(&struct_at_descr, param_list, input_list, out_node);
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
    
    return NULL;
}

ohcp_node* ohcp_expr_struct_at_cstr(const ohcp_node* node0, const char* name)
{
    return ohcp_expr_struct_at(node0, ohcp_string_create_cstr(name));
}

// ohcp_struct_cat ---------------------------------------------------------- //

static ohcp_string* struct_cat_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_string* struct_cat_to_asgn_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return ohcp_string_create();
}

static ohcp_expr_descr struct_cat_descr = {
    .name = "struct_cat",
    .to_str = struct_cat_to_str,
    .to_asgn_str = struct_cat_to_asgn_str
};

ohcp_node* ohcp_expr_struct_cat(const ohcp_type* type, size_t in_count, const ohcp_node* in_list[])
{
    const ohcp_typedescr_struct* typedescr;
    size_t field_count;
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* out_node;
    ohcp_expr* expr;
    
    if (type == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->descr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type->descr is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->typetype != OHCP_TYPETYPE_STRUCT) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type->typetype must be STRUCT", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    typedescr = (const ohcp_typedescr_struct*) type->descr;
    if (typedescr->field_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): typedescr->field_list is NULL", __func__);
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
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
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
    
    field_count = 0;
    for (const ohcp_deque_entry* de = ohcp_deque_first(typedescr->field_list) ;
         de != NULL && field_count < in_count ; de = de->next)
    {
        const ohcp_struct_field* field;
        const ohcp_node* node;
        
        if (de->data == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): de->data is NULL", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        field = (const ohcp_struct_field*) de->data;
        
        node = in_list[field_count];
        if (node == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): in_list[%lu] is NULL", __func__, field_count);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        if (field->base != node->type) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf),
                "%s(): type in_list[%lu] does not match that of the field %s",
                __func__, field_count, ohcp_string_cstr(field->name));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            return NULL;
        }
        
        field_count++;
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
            
            for (size_t i = 0 ; i < field_count ; i++) {
                ohcp_deque_push_back(input_list, in_list[i]);
            }
            
            do {
                out_node = ohcp_node_create(type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&struct_cat_descr, param_list, input_list, out_node);
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
        
    return NULL;
}
