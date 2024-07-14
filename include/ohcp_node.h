// File: ohcp_node.h

#ifndef OHCP_NODE_H
#define OHCP_NODE_H

#include "ohcp_string.h"
#include "ohcp_forward.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ohcp_node
{
    const ohcp_type*    type;
    const ohcp_string*  name;
    
    ohcp_module*        parent;
    ohcp_expr*          driver;
    ohcp_port*          port;
    
    void*               ext;
};

/* move */ ohcp_node*   ohcp_node_create        (/* ref */ const ohcp_type* type, /* move */ const ohcp_string* name);
void                    ohcp_node_destroy       (/* move */ const ohcp_node* node);

/* move */ ohcp_string* ohcp_node_debug_str     (/* ref */ const ohcp_node* node);

// int                     ohcp_node_init              ();
// void                    ohcp_node_cleanup           ();

#ifdef __cplusplus
}
#endif

#endif
