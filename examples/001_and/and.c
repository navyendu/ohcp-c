#include "and.h"

static int and_build (ohcp_module* m)
{
    and_ports ports;
    size_t width = (size_t) m->descr->priv;
    
    ports.a = ohcp_module_create_port(m, ohcp_type_create_vector(width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b = ohcp_module_create_port(m, ohcp_type_create_vector(width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("b"));
    ports.o = ohcp_module_create_port(m, ohcp_type_create_vector(width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("c"));
    
    ohcp_module_assign(m, ports.o, ohcp_expr_and2(ports.a, ports.b));
    
    if (m->ipriv != NULL) {
        *((and_ports*) m->ipriv) = ports;
    }
    
    return 0;
}

ohcp_module_descr* and_descr (size_t width)
{
    return ohcp_module_descr_create(ohcp_string_create_cstr("and"), (void*) width, and_build);
}
