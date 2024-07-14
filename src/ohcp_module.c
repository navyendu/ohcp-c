// File: ohcp_module.c

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_port.h"
#include "ohcp_expr.h"
#include "ohcp_module.h"

ohcp_module_descr* ohcp_module_descr_create(const ohcp_string* name, void* priv,
    ohcp_module_build_fptr_t buildfn)
{
    if (name == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'name\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (buildfn == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'buildfn\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        ohcp_module_descr* descr;
        
        descr = malloc(sizeof(ohcp_module_descr));
        if (descr == NULL) {
            int     ret;
            size_t  len;
            char    buf [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc module descriptor", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        descr->name = name;
        descr->priv = priv;
        descr->build = buildfn;
        
        return descr;
    } while (0);
    
    return NULL;
}

void ohcp_module_descr_destroy(ohcp_module_descr* descr)
{
    if (descr != NULL) {
        ohcp_string_destroy(descr->name);
    }
    
    free((void*) descr);
}

ohcp_string* ohcp_module_descr_dump(const ohcp_module_descr* descr)
{
    int     ret;
    size_t  len;
    char    buf [1024];
    
    if (descr == NULL) {
        return NULL;
    }
    
    ret = snprintf(buf, sizeof(buf), "@%p \"%s\"",
        (void*) descr, ohcp_string_cstr(descr->name));
    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
    
    return ohcp_string_create_lcstr(len, buf);
}

// -------------------------------------------------------------------------- //

ohcp_module* ohcp_module_create(ohcp_module* parent, const ohcp_module_descr* descr,
    const ohcp_string* name, void* ipriv)
{
    if (descr == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'descr\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (descr->build == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'descr->build\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (name == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'name\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        ohcp_deque* node_list;
        
        node_list = ohcp_deque_create();
        if (node_list == NULL) {
            int     ret;
            size_t  len;
            char    buf [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create node_list", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            ohcp_deque* expr_list;
            
            expr_list = ohcp_deque_create();
            if (expr_list == NULL) {
                int     ret;
                size_t  len;
                char    buf [1024];
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to create expr_list", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            do {
                ohcp_deque* child_list;
                
                child_list = ohcp_deque_create();
                if (child_list == NULL) {
                    int     ret;
                    size_t  len;
                    char    buf [1024];
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to create child_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                do {
                    ohcp_module* module;
                    int build_ret;
                    
                    module = malloc(sizeof(ohcp_module));
                    if (module == NULL) {
                        int     ret;
                        size_t  len;
                        char    buf [1024];
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc() module", __func__);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                        
                        break;
                    }
                    
                    module->descr = descr;
                    module->name = name;
                    module->parent = parent;
                    module->node_list = node_list;
                    module->expr_list = expr_list;
                    module->child_list = child_list;
                    module->ipriv = ipriv;
                    module->ext = NULL;
                    
                    build_ret = descr->build(module);
                    
                    if (build_ret != 0) {
                        int     ret;
                        size_t  len;
                        char    buf [1024];
                        
                        ret = snprintf(buf, sizeof(buf), "%s(): build() returned %d", __func__, build_ret);
                        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                        
                        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    }
                    
                    if (parent != NULL) {
                        ohcp_module_add_child(parent, module);
                    }
                    
                    return module;
                } while (0);
                
                ohcp_deque_destroy(child_list);
            } while (0);
            
            ohcp_deque_destroy(expr_list);
        } while (0);
        
        ohcp_deque_destroy(node_list);
    } while (0);
    
    return NULL;
}

void ohcp_module_destroy(const ohcp_module* module)
{
    if (module != NULL) {
        for (const ohcp_deque_entry* de = ohcp_deque_first(module->node_list) ; de != NULL ; de = de->next) {
            ohcp_node_destroy((ohcp_node*) de->data);
        }
        ohcp_deque_destroy(module->node_list);
        
        for (const ohcp_deque_entry* de = ohcp_deque_first(module->expr_list) ; de != NULL ; de = de->next) {
            ohcp_expr_destroy((ohcp_expr*) de->data);
        }
        ohcp_deque_destroy(module->expr_list);
        
        for (const ohcp_deque_entry* de = ohcp_deque_first(module->child_list) ; de != NULL ; de = de->next) {
            ohcp_module_destroy((ohcp_module*) de->data);
        }
        ohcp_deque_destroy(module->child_list);
        
        ohcp_string_destroy(module->name);
    }
    
    free((void*) module);
}

int ohcp_module_add_node(ohcp_module* m, ohcp_node* node)
{
    int add_ret;
    
    if (m == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "m");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    if (node == NULL) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "node");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    add_ret = ohcp_deque_push_back(m->node_list, (void*) node);
    if (add_ret != 0) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): %s:%s: Failed to push node \'%s\' to queue",
            __func__, ohcp_string_cstr(m->descr->name), ohcp_string_cstr(m->name),
            ohcp_string_cstr(node->name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return -2;
    }
    
    node->parent = m;
    
    if (1) {
        int     ret;
        size_t  len;
        char    buf [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): %s:%s: Added ohcp_node \'%s\' %p",
            __func__, ohcp_string_cstr(m->descr->name), ohcp_string_cstr(m->name),
            ohcp_string_cstr(node->name), (void*) node->type);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, buf));
    }
    
    return 0;
}

int ohcp_module_add_expr(ohcp_module* m, ohcp_expr* expr)
{
    int add_ret;
    
    if (m == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "m");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    if (expr == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "expr");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    add_ret = ohcp_deque_push_back(m->expr_list, (void*) expr);
    if (add_ret != 0) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): ohcp_deque_push_back returned NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
    }
    
    expr->parent = m;
    
    if (1) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): %s:%s: Added ohcp_expr",
            __func__, ohcp_string_cstr(m->descr->name), ohcp_string_cstr(m->name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, buf));
    }
    
    return 0;
}

int ohcp_module_add_child(ohcp_module* m, /* move*/ ohcp_module* child)
{
    int add_ret;
    
    if (m == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "m");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    if (child == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "child");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return -1;
    }
    
    add_ret = ohcp_deque_push_back(m->child_list, (void*) child);
    if (add_ret != 0) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): ohcp_deque_push_back returned %d", __func__, add_ret);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
    }
    
    child->parent = m;
    
    if (1) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): %s:%s: Added child \'%s\'",
            __func__, ohcp_string_cstr(m->descr->name), ohcp_string_cstr(m->name),
            ohcp_string_cstr(child->name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, buf));
    }
    
    return 0;
}

ohcp_node* ohcp_module_create_node(ohcp_module* m, const ohcp_type* type,
    const ohcp_string* name)
{
    if (m == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "m");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        ohcp_node* node = ohcp_node_create(type, name);
        if (node == NULL) {
            int     ret;
            size_t  len;
            char    buf   [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create node %s",
                __func__, ohcp_string_cstr(name));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            int add_ret = ohcp_module_add_node(m, node);
            if (add_ret != 0) {
                int     ret;
                size_t  len;
                char    buf   [1024];
                
                ret = snprintf(buf, sizeof(buf),
                    "%s(): Failed to add node %s to module %s", __func__,
                    ohcp_string_cstr(name), ohcp_string_cstr(m->name));
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            return node;
        } while (0);
        
        ohcp_node_destroy(node);
    } while (0);
    
    return NULL;
}

ohcp_node* ohcp_module_create_port(ohcp_module* m, const ohcp_type* t,
    enum ohcp_port_dir dir, const ohcp_string* name)
{
    if (m == NULL) {
        int     ret;
        size_t  len;
        char    buf   [1024];
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'%s\' is NULL", __func__, "m");
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        ohcp_node* node = ohcp_port_create(t, dir, name);
        if (node == NULL) {
            int     ret;
            size_t  len;
            char    buf   [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create node %s",
                __func__, ohcp_string_cstr(name));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            int add_ret = ohcp_module_add_node(m, node);
            if (add_ret != 0) {
                int     ret;
                size_t  len;
                char    buf   [1024];
                
                ret = snprintf(buf, sizeof(buf),
                    "%s(): Failed to add node %s to module %s", __func__,
                    ohcp_string_cstr(name), ohcp_string_cstr(m->name));
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            return node;
        } while (0);
        
        ohcp_node_destroy(node);
    } while (0);
    
    return NULL;
}

static int ohcp_module_claim_orphans(/* ref */ ohcp_module* m, /* move */ ohcp_expr* expr)
{
    int ret;
    
    if (m == NULL) {
        return -1;
    }
    
    if (expr == NULL) {
        return -2;
    }
    
    ret = 0;
    if (expr->parent == NULL) {
        ohcp_module_add_expr(m, expr);
        
        for (ohcp_deque_entry* de = ohcp_deque_first(expr->input_list) ; de != NULL ; de = de->next) {
            ohcp_node* node = (ohcp_node*) de->data;
            
            if (node != NULL) {
                if (node->parent == NULL) {
                    ohcp_module_add_node(m, node);
                    
                    if (node->driver != NULL) {
                        ret += ohcp_module_claim_orphans(m, node->driver);
                    }
                }
            }
        }
    }
    
    return ret;
}

int ohcp_module_assign(ohcp_module* m, ohcp_node* node, ohcp_node* node0)
{
    ohcp_expr* expr;
    
    if (node == NULL) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(NULL,?): Argument \'node\' is NULL", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return -1;
    }
    
    if (node0 == NULL) {
        char            stats_msg   [1024];
        int             ret;
        size_t          len;
        ohcp_string*    fname;
        
        fname = ohcp_module_full_name(m, node);
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(%s, NULL): Argument \'node0\' is NULL",
            __func__, ohcp_string_cstr(fname));
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        ohcp_string_destroy(fname);
        
        return -1;
    }
    
    if (1) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): node->type == %p, node0->type == %p", __func__,
            (void*) node->type, (void*) node0->type);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_DEBUG, ohcp_string_create_lcstr(len, stats_msg));
    }
    
    if (node->type != node0->type) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ohcp_string* left_type;
        ohcp_string* right_type;
        
        left_type = ohcp_type_to_str(node->type);
        right_type = ohcp_type_to_str(node0->type);
        
        ret = snprintf(stats_msg, sizeof(stats_msg),
            "%s(): Assignment requires nodes to be of the same type. LHS: %s, RHS: %s",
            __func__, ohcp_string_cstr(left_type), ohcp_string_cstr(right_type));
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_string_destroy(left_type);
        ohcp_string_destroy(right_type);
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return -2;
    }
    
    if (node->driver != NULL) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Assignment requires target node to be undriven", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return -2;
    }
    
    expr = node0->driver;
    expr->output = node;
    
    node->driver = expr;
    node0->driver = NULL;
    
    if (m != NULL) {
        int claim_ret;
        
        claim_ret = ohcp_module_claim_orphans(m, expr);
        if (claim_ret != 0) {
            int     ret;
            size_t  len;
            char    buf   [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): ohcp_module_claim_orphans() returned %d",
                __func__, claim_ret);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        }
    }
    
    ohcp_node_destroy(node0);
    
    return 0;
}

static /* move */ ohcp_string* module_full_name(/* ref */ const ohcp_module* m)
{
    ohcp_string* str;
    
    if (m == NULL) {
        return NULL;
    }
    
    str = ohcp_string_create();
    
    if (m->parent != NULL) {
        ohcp_string* parent_str;
        
        parent_str = module_full_name(m->parent);
        str = ohcp_string_cat(str, parent_str);
        ohcp_string_destroy(parent_str);
    }
    
    str = ohcp_string_cat_cstr(str, "/");
    str = ohcp_string_cat(str, m->name);
    
    return str;
}


ohcp_string* ohcp_module_full_name(const ohcp_module* m, const ohcp_node* node)
{
    ohcp_string* str;
    
    str = ohcp_string_create();
    
    if (m != NULL) {
        ohcp_string* module_str;
        
        module_str = module_full_name(m);
        str = ohcp_string_cat(str, module_str);
        ohcp_string_destroy(module_str);
    }
    
    str = ohcp_string_cat_cstr(str, "/");
    
    if (node != NULL) {
        str = ohcp_string_cat(str, node->name);
    }
    
    return str;
}

ohcp_string* ohcp_module_debug_str(const ohcp_module* m, const ohcp_string* indent)
{
    ohcp_string* descr_str;
    ohcp_string* str;
    char buf [1024];
    int ret;
    size_t len;
    ohcp_string* indent_str;
    
    if (m == NULL) {
        return NULL;
    }
    
    indent_str = ohcp_string_create();
    if (indent != NULL) {
        indent_str = ohcp_string_cat(indent_str, indent);
    }
    
    descr_str = ohcp_module_descr_dump(m->descr);
    
    ret = snprintf(buf, sizeof(buf),
        "%smodule @%p parent:@%p \"%s\" descr:{%s}\n",
        ohcp_string_cstr(indent_str), (void*) m, (void*) m->parent,
        ohcp_string_cstr(m->name), ohcp_string_cstr(descr_str));
    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
    
    ohcp_string_destroy(descr_str);
    
    str = ohcp_string_create_lcstr(len, buf);
    
    for (const ohcp_deque_entry* de = ohcp_deque_first(m->node_list) ; de != NULL ; de = de->next) {
        const ohcp_node* node;
        ohcp_string* str_node;
        
        node = (ohcp_node*) de->data;
        assert (node != NULL);
        
        str_node = ohcp_node_debug_str(node);
        
        str = ohcp_string_cat(str, indent_str);
        str = ohcp_string_cat_cstr(str, "    ");
        str = ohcp_string_cat(str, str_node);
        str = ohcp_string_cat_cstr(str, "\n");
        
        ohcp_string_destroy(str_node);
    }
    
    for (const ohcp_deque_entry* de = ohcp_deque_first(m->expr_list) ; de != NULL ; de = de->next) {
        const ohcp_expr* expr;
        ohcp_string* str_expr;
        
        expr = (ohcp_expr*) de->data;
        str_expr = ohcp_expr_dump(expr);
        
        str = ohcp_string_cat(str, indent_str);
        str = ohcp_string_cat_cstr(str, "    ");
        str = ohcp_string_cat(str, str_expr);
        str = ohcp_string_cat_cstr(str, "\n");
        
        ohcp_string_destroy(str_expr);
    }
    
    for (const ohcp_deque_entry* de = ohcp_deque_first(m->child_list) ; de != NULL ; de = de->next) {
        const ohcp_module* child;
        ohcp_string* str_child;
        ohcp_string* str_child_indent;
        
        str_child_indent = ohcp_string_create_cstr("    ");
        str_child_indent = ohcp_string_cat(str_child_indent, indent_str);
        
        child = (ohcp_module*) de->data;
        str_child = ohcp_module_debug_str(child, str_child_indent);
        
        str = ohcp_string_cat(str, str_child);
        
        ohcp_string_destroy(str_child);
        ohcp_string_destroy(str_child_indent);
    }
    
    str = ohcp_string_cat(str, indent_str);
    str = ohcp_string_cat_cstr(str, "endmodule\n");
    
    ohcp_string_destroy(indent_str);
    
    return str;
}
