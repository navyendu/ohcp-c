// File: ohcp_port.h

#ifndef OHCP_PORT_H
#define OHCP_PORT_H

#include "ohcp_string.h"
#include "ohcp_forward.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ohcp_port_dir
{
    OHCP_PORT_IN    = 0,
    OHCP_PORT_OUT   = 1,
    OHCP_PORT_INOUT = 2
};
typedef enum ohcp_port_dir ohcp_port_dir;

/* move */ ohcp_string* ohcp_port_dir_to_str    (ohcp_port_dir dir);

struct ohcp_port
{
    ohcp_port_dir   dir;
    
    ohcp_node*      node;
};

/* move */ ohcp_node*   ohcp_port_create    (/* ref */ const ohcp_type* t, enum ohcp_port_dir dir, /* move */ const ohcp_string* name);
void                    ohcp_port_destroy   (/* move */ const ohcp_port* p);

#ifdef __cplusplus
}
#endif

#endif
