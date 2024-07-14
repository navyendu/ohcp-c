#include "aoi.h"

/// build aoi module with the static params passed through m->descr->priv
static int aoi_build (ohcp_module* m)
{
    aoi_ports ports;
    aoi_params params = *((aoi_params*) m->descr->priv);
    
    ports.a = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("b"));
    if (params.use_c) {
        ports.c = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("c"));
    }
    ports.o = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_OUT, ohcp_string_create_cstr("o"));
    
    ohcp_node* ab = ohcp_expr_and2(ports.a, ports.b);
    ohcp_node* abc = params.use_c ? ohcp_expr_or2(ab, ports.c) : ab;
    
    ohcp_module_assign(m, ports.o, ohcp_expr_inv(abc));
    
    if (m->ipriv != NULL) {
        *((aoi_ports*) m->ipriv) = ports;
    }
    
    return 0;
}

/// function to create descriptors of different widths on the fly
/// need to delete thse using ohcp_module_descr_destroy
ohcp_module_descr* aoi_descr (const aoi_params* params)
{
    return ohcp_module_descr_create(ohcp_string_create_cstr("aoi"), (aoi_params*) params, aoi_build);
}
