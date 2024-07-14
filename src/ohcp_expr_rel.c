// File: ohcp_expr_rel.c

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_expr.h"
#include "ohcp_expr_rel.h"

// -------------------------------------------------------------------------- //

static ohcp_string* eq_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* eq_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr eq_descr = {
    .name = "eq",
    .to_str = eq_to_str,
    .to_asgn_str = eq_to_asgn_str
};

ohcp_node* ohcp_expr_eq(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): EQ can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&eq_descr, param_list, input_list, output);
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

// -------------------------------------------------------------------------- //

static ohcp_string* ne_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* ne_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr ne_descr = {
    .name = "ne",
    .to_str = ne_to_str,
    .to_asgn_str = ne_to_asgn_str
};

ohcp_node* ohcp_expr_ne(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): NE can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&ne_descr, param_list, input_list, output);
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

// -------------------------------------------------------------------------- //

static ohcp_string* lt_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* lt_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr lt_descr = {
    .name = "lt",
    .to_str = lt_to_str,
    .to_asgn_str = lt_to_asgn_str
};

ohcp_node* ohcp_expr_lt(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): LT can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&lt_descr, param_list, input_list, output);
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

// -------------------------------------------------------------------------- //

static ohcp_string* ge_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* ge_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr ge_descr = {
    .name = "ge",
    .to_str = ge_to_str,
    .to_asgn_str = ge_to_asgn_str
};

ohcp_node* ohcp_expr_ge(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): Equality can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&ge_descr, param_list, input_list, output);
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

// -------------------------------------------------------------------------- //

static ohcp_string* gt_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* gt_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr gt_descr = {
    .name = "gt",
    .to_str = gt_to_str,
    .to_asgn_str = gt_to_asgn_str
};

ohcp_node* ohcp_expr_gt(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): GT can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&gt_descr, param_list, input_list, output);
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

// -------------------------------------------------------------------------- //

static ohcp_string* le_to_str(const ohcp_expr* expr)
{
    (void) expr;
    
    return NULL;
}

static ohcp_string* le_to_asgn_str(const ohcp_expr* expr)
{
    ohcp_string* str;
    
    (void) expr;
    
    str = ohcp_string_create();
    
    return str;
}

static ohcp_expr_descr le_descr = {
    .name = "le",
    .to_str = le_to_str,
    .to_asgn_str = le_to_asgn_str
};

ohcp_node* ohcp_expr_le(const ohcp_node* node0, const ohcp_node* node1)
{
    ohcp_deque* param_list;
    ohcp_deque* input_list;
    ohcp_node* output;
    ohcp_expr* expr;
    
    if (node0 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node0 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node1 == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): node1 is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (node0->type != node1->type) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf),
            "%s(): LE can be applied only on nodes of the same type", __func__);
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
            ohcp_deque_push_back(input_list, node0);
            ohcp_deque_push_back(input_list, node1);
            
            do {
                output = ohcp_node_create(node0->type, ohcp_string_create());
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
                    expr = ohcp_expr_create(&le_descr, param_list, input_list, output);
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
