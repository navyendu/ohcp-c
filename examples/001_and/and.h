#ifndef OHCP_EX_001_AND_H
#define OHCP_EX_001_AND_H

#include "ohcp.h"

ohcp_module_descr* and_descr (size_t width);

typedef struct and_ports {
    ohcp_node* a;
    ohcp_node* b;
    ohcp_node* c;
    
    ohcp_node* o;
} and_ports;

#endif
