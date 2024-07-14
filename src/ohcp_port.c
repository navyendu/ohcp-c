// File: ohcp_port.c

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_node.h"
#include "ohcp_port.h"

ohcp_string* ohcp_port_dir_to_str(enum ohcp_port_dir dir)
{
    if (dir == OHCP_PORT_IN) {
        return ohcp_string_create_cstr("input");
    } else if (dir == OHCP_PORT_OUT) {
        return ohcp_string_create_cstr("output");
    } else if (dir == OHCP_PORT_INOUT) {
        return ohcp_string_create_cstr("inout");
    } else {
        return NULL;
    }
}

ohcp_node* ohcp_port_create(const ohcp_type* type, enum ohcp_port_dir dir, const ohcp_string* name)
{
    char stats_msg [1024];
    
    if (type == NULL) {
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Argument \'type\' is NULL", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return NULL;
    }
    
    if (!(dir == OHCP_PORT_IN || dir == OHCP_PORT_OUT || dir == OHCP_PORT_INOUT)) {
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Port direction must be one of OHCP_PORT_IN, OHCP_PORT_OUT or OHCP_PORT_INOUT", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return NULL;
    }
    
    if (name == NULL) {
        int     ret;
        size_t  len;
        
        ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Argument \'name\' is NULL", __func__);
        len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, stats_msg));
        
        return NULL;
    }
    
    do {
        ohcp_node* node;
        
        node = ohcp_node_create(type, name);
        if (node == NULL) {
            int     ret;
            size_t  len;
            
            ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Failed to create internal ohcp_node", __func__);
            len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, stats_msg));
            
            break;
        }
        
        do {
            ohcp_port* port;
            
            port = malloc(sizeof(ohcp_port));
            if (port == NULL) {
                int     ret;
                size_t  len;
                
                ret = snprintf(stats_msg, sizeof(stats_msg), "%s(): Failed to malloc \'port\'", __func__);
                len = ret > (int) sizeof(stats_msg) ? sizeof(stats_msg) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, stats_msg));
                
                break;
            }
            
            port->node = node;
            port->dir = dir;
            
            node->port = port;
            
            return node;
        } while (0);
        
        ohcp_node_destroy(node);
    } while (0);
    
    return NULL;
}

void ohcp_port_destroy(const ohcp_port* port)
{
    free((void*) port);
}
