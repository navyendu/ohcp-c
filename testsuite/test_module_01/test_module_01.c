// File: test_module_01.c

#include <stdio.h>

#include "ohcp.h"

static ohcp_module_descr* half_adder_descr;

typedef struct half_adder_port_t {
    ohcp_node* a;
    ohcp_node* b;
    
    ohcp_node* s;
    ohcp_node* d;
} half_adder_port_t;

static int half_adder_build(ohcp_module* m)
{
    half_adder_port_t ports;
    
    ports.a = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("b"));
    ports.s = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("s"));
    ports.d = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("d"));
    
    assert(ports.a != NULL);
    assert(ports.b != NULL);
    assert(ports.s != NULL);
    assert(ports.d != NULL);
    
    ohcp_module_assign(m, ports.s, ohcp_expr_buf(ohcp_expr_buf(ports.a)));
    ohcp_module_assign(m, ports.d, ohcp_expr_buf(ports.b));
    
    if (m->ipriv != NULL) {
        *((half_adder_port_t*) m->ipriv) = ports;
    }
    
    return 0;
}

static ohcp_module_descr* full_adder_descr;

typedef struct full_adder_port_t {
    ohcp_node* a;
    ohcp_node* b;
    ohcp_node* c;
    
    ohcp_node* s;
    ohcp_node* d;
} full_adder_port_t;

static int full_adder_build(ohcp_module* m)
{
    full_adder_port_t ports;
    
    ohcp_node* i0;
    ohcp_node* i1;
    ohcp_node* i2;
    
    ports.a = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("b"));
    ports.c = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("c"));
    ports.s = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("s"));
    ports.d = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("d"));
    
    i0 = ohcp_module_create_node(m, ohcp_logic, ohcp_string_create_cstr("i0"));
    i1 = ohcp_module_create_node(m, ohcp_logic, ohcp_string_create_cstr("i1"));
    i2 = ohcp_module_create_node(m, ohcp_logic, ohcp_string_create_cstr("i2"));
    
    half_adder_port_t ha0_ports;
    half_adder_port_t ha1_ports;
    
    ohcp_module* ha0 = ohcp_module_create(m, half_adder_descr, ohcp_string_create_cstr("ha0"), &ha0_ports);
    ohcp_module* ha1 = ohcp_module_create(m, half_adder_descr, ohcp_string_create_cstr("ha1"), &ha1_ports);
    
    assert (ha0 != NULL);
    assert (ha1 != NULL);
    
    ohcp_module_assign(m, ha0_ports.a, ohcp_expr_buf(ports.a));
    ohcp_module_assign(m, ha0_ports.b, ohcp_expr_buf(ports.b));
    ohcp_module_assign(m, i0, ohcp_expr_buf(ha0_ports.s));
    ohcp_module_assign(m, i1, ohcp_expr_buf(ha0_ports.d));
    
    ohcp_module_assign(m, ha1_ports.a, ohcp_expr_buf(ports.c));
    ohcp_module_assign(m, ha1_ports.b, ohcp_expr_buf(i0));
    ohcp_module_assign(m, ports.s, ohcp_expr_buf(ha1_ports.s));
    ohcp_module_assign(m, i2, ohcp_expr_buf(ha1_ports.d));
    
    ohcp_module_assign(m, ports.d, ohcp_expr_buf(i1));
    
    if (m->ipriv != NULL) {
        *((full_adder_port_t*) m->ipriv) = ports;
    }
    
    return 0;
}

int main()
{
    ohcp_string* fname;
    ohcp_string* dump;
    ohcp_string* indent;
    int ret;
    
    ret = ohcp_init();
    if (ret != 0) {
        fprintf(stderr, "ohcp_init() == %d\n", ret);
        return -1;
    }
    
    half_adder_descr = ohcp_module_descr_create(ohcp_string_create_cstr("half_adder"), NULL, half_adder_build);
    full_adder_descr = ohcp_module_descr_create(ohcp_string_create_cstr("full_adder"), NULL, full_adder_build);
    
    ohcp_module* fa0 = ohcp_module_create(NULL, full_adder_descr, ohcp_string_create_cstr("fa0"), NULL);
    
    indent = ohcp_string_create_cstr("");
    fname = ohcp_module_full_name(fa0, NULL);
    dump = ohcp_module_debug_str(fa0, indent);
    
    fprintf(stderr, "fname == %s\n", ohcp_string_cstr(fname));
    fprintf(stderr, "%s\n", ohcp_string_cstr(dump));
    
    ohcp_string_destroy(dump);
    ohcp_string_destroy(fname);
    ohcp_string_destroy(indent);
    
    ohcp_module_destroy(fa0);
    ohcp_module_descr_destroy(half_adder_descr);
    ohcp_module_descr_destroy(full_adder_descr);
    
    for (const ohcp_deque_entry* iter = ohcp_stats_first() ; iter != NULL ; iter = iter->next) {
        const ohcp_stats_entry* se;
        const ohcp_string* str;
        
        se = iter->data;
        str = ohcp_severity_to_str(se->sev);
        
        fprintf(stderr, "%s %s\n", ohcp_string_cstr(str), ohcp_string_cstr(se->msg));
        
        ohcp_string_destroy(str);
    }
    
    ohcp_cleanup();
    
    return 0;
}
