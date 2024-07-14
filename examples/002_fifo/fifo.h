#ifndef OHCP_EX_002_FIFO_H
#define OHCP_EX_002_FIFO_H

#include "ohcp.h"

typedef struct fifo_params {
    size_t  width;
    size_t  depth;
} fifo_params;

ohcp_module_descr* fifo_descr (const fifo_params* params);

typedef struct fifo_ports {
    ohcp_node* clk;
    ohcp_node* rst;
    
    ohcp_node* wr_en;
    ohcp_node* wr_data;
    
    ohcp_node* rd_en;
    ohcp_node* rd_data;
    
    ohcp_node* full;
    ohcp_node* empty;
} fifo_ports;

#endif
