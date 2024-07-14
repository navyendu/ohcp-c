#ifndef OHCP_EX_003_AOI_H
#define OHCP_EX_003_AOI_H

#include <stdbool.h>

#include "ohcp.h"

/// Implements an module that accepts two input vectors of width "width",
/// and a third input of the same width depending on the "use_c" param,
/// peforms ~((a & b) | c) if use_c is set or ~(a & b) otherwise, and
/// drives the final result on an output port o

/// width indicates the number of bits in a, b, c and o
/// use_c indicates if port c is present
typedef struct aoi_params {
    size_t  width;
    bool    use_c;
} aoi_params;

/// function to create descriptors of different widths on the fly
/// need to delete thse using ohcp_module_descr_destroy
ohcp_module_descr* aoi_descr (const aoi_params* params);

/// ports of aoi, obtained from the build function
typedef struct aoi_ports {
    ohcp_node* a;
    ohcp_node* b;
    ohcp_node* c;
    
    ohcp_node* o;
} aoi_ports;

#endif
