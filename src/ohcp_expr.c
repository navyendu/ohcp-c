// File: ohcp_expr.c

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_expr.h"

ohcp_string* ohcp_expr_descr_dump(const ohcp_expr_descr* descr)
{
    ohcp_string* str;
    
    if (descr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): descr is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (descr->name == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): descr->name is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "@%p \"%s\"",
            (void*) descr, descr->name);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        str = ohcp_string_create_lcstr(len, buf);
    }
    
    return str;
}

struct ohcp_expr* ohcp_expr_create(const ohcp_expr_descr* descr,
    ohcp_deque* param_list, ohcp_deque* input_list, ohcp_node* output)
{
    if (descr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): descr is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (param_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): param_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (input_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): input_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (output == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): out is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        ohcp_expr* expr;
        
        expr = (ohcp_expr*) malloc(sizeof(ohcp_expr));
        if (expr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): failed to malloc expr", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        expr->descr = descr;
        expr->parent = NULL;
        expr->input_list = input_list;
        expr->param_list = param_list;
        expr->output = output;
        
        return expr;
    } while (0);
    
    return NULL;
}

void ohcp_expr_destroy(const ohcp_expr* expr)
{
    if (expr != NULL) {
        for (ohcp_deque_entry* de = ohcp_deque_first(expr->param_list) ; de != NULL ; de = de->next) {
            // Free malloc'd params
            free((void*) de->data);
        }
        
        ohcp_deque_destroy(expr->param_list);
        ohcp_deque_destroy(expr->input_list);
    }
    
    free((void*) expr);
}

ohcp_string* ohcp_expr_dump(const ohcp_expr* expr)
{
    ohcp_string* str;
    ohcp_string* str_descr;
    
    if (expr == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): expr is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        str_descr = ohcp_expr_descr_dump(expr->descr);
        
        str = ohcp_string_create();
        
        ret = snprintf(buf, sizeof(buf),
            "expr @%p parent:@%p descr:{%s} out:@%p pa:[",
            (void*) expr, (void*) expr->parent, ohcp_string_cstr(str_descr),
            (void*) expr->output);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        str = ohcp_string_cat_lcstr(str, len, buf);
        
        ohcp_string_destroy(str_descr);
        
        for (ohcp_deque_entry* de = ohcp_deque_first(expr->param_list) ; de != NULL ; de = de->next) {
            const void* param = de->data;
            
            if (de->next != NULL) {
                ret = snprintf(buf, sizeof(buf), "%p,", (void*) param);
            } else {
                ret = snprintf(buf, sizeof(buf), "%p", (void*) param);
            }
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            str = ohcp_string_cat_lcstr(str, len, buf);
        }
        
        str = ohcp_string_cat_cstr(str, "] in:[");
        
        for (ohcp_deque_entry* de = ohcp_deque_first(expr->input_list) ; de != NULL ; de = de->next) {
            const ohcp_node* in = (ohcp_node*) de->data;
            
            if (de->next != NULL) {
                ret = snprintf(buf, sizeof(buf), "%p,", (void*) in);
            } else {
                ret = snprintf(buf, sizeof(buf), "%p", (void*) in);
            }
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            str = ohcp_string_cat_lcstr(str, len, buf);
        }
        
        str = ohcp_string_cat_cstr(str, "]");
    }
    
    return str;
}

ohcp_string* ohcp_expr_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}
