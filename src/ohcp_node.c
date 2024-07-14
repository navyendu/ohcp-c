// File: ohcp_node.c

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"
#include "ohcp_node.h"
#include "ohcp_port.h"

ohcp_node* ohcp_node_create(const ohcp_type* type, const ohcp_string* name)
{
    if (type == NULL) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Argument \'type\' is NULL", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, stats_msg));
        
        return NULL;
    }
    
    if (name == NULL) {
        char    stats_msg   [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Argument \'name\' is NULL", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, stats_msg));
        
        return NULL;
    }
    
    do {
        ohcp_node* node;
        
        node = malloc(sizeof(ohcp_node));
        if (node == NULL) {
            char        stats_msg   [1024];
            int         ret;
            size_t      len;
            
            ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Failed to malloc \'node\'", __func__);
            len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, stats_msg));
            
            break;
        }
        
        node->type = type;
        node->name = name;
        node->parent = NULL;
        node->driver = NULL;
        node->port = NULL;
        node->ext = NULL;
        
        return node;
    } while (0);
    
    return NULL;
}

void ohcp_node_destroy(const ohcp_node* node)
{
    if (node != NULL) {
        ohcp_string_destroy(node->name);
        
        if (node->port != NULL) {
            ohcp_port_destroy(node->port);
        }
    }
    
    free((void*) node);
}

ohcp_string* ohcp_node_debug_str(const ohcp_node* node)
{
    int             ret;
    size_t          len;
    char            buf   [1024];
    ohcp_string*    str;
    ohcp_string*    str_type;
    ohcp_string*    str_port;
    
    if (node == NULL) {
        return NULL;
    }
    
    if (node->type == NULL) {
        return NULL;
    }
    
    str_type = ohcp_type_to_str(node->type);
    
    if (node->port != NULL) {
        str_port = ohcp_port_dir_to_str(node->port->dir);
    } else {
        str_port = ohcp_string_create_cstr("");
    }
    
    ret = snprintf(buf, sizeof(buf),
        "%s @%p parent:@%p \"%s\"%s%s driver:@%p type:%s",
        node->port == NULL ? "node" : "port",
        (void*) node,
        (void*) node->parent,
        ohcp_string_cstr(node->name),
        node->port == NULL ? "" : " dir:",
        ohcp_string_cstr(str_port),
        (void*) node->driver,
        ohcp_string_cstr(str_type)
    );
    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
    
    str = ohcp_string_create_lcstr(len, buf);
    
    ohcp_string_destroy(str_port);
    ohcp_string_destroy(str_type);
    
    return str;
}
