// File: test_module_02.c

#include <stdio.h>

#include "ohcp.h"

static ohcp_module_descr* const_mux_descr;

typedef struct const_mux_port_t {
    ohcp_node* in;
    size_t index;
    ohcp_node* out;
    
    ohcp_node* a;
    ohcp_node* b;
    ohcp_node* y;
} const_mux_port_t;

static int const_mux_build(struct ohcp_module* m)
{
    const_mux_port_t ports;
    
    ports.in = ohcp_module_create_port(m,
        ohcp_type_create_vector(3, ohcp_type_create_vector(4, ohcp_logic)),
        OHCP_PORT_IN, ohcp_string_create_cstr("in"));
    ports.index = 2;
    ports.out = ohcp_module_create_port(m,
        ohcp_type_create_vector(4, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("out"));
    
    ports.a = ohcp_module_create_port(m,
        ohcp_type_create_vector(3, ohcp_type_create_vector(4, ohcp_logic)),
        OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b = ohcp_module_create_port(m,
        ohcp_type_create_vector(3, ohcp_type_create_vector(4, ohcp_logic)),
        OHCP_PORT_IN, ohcp_string_create_cstr("b"));
    ports.y = ohcp_module_create_port(m,
        ohcp_type_create_vector(3, ohcp_type_create_vector(4, ohcp_logic)),
        OHCP_PORT_OUT, ohcp_string_create_cstr("y"));
    
    ohcp_module_assign(m, ports.out, ohcp_expr_inv(ohcp_expr_vector_at(ports.in, ports.index)));
    ohcp_module_assign(m, ports.y, ohcp_expr_inv(ohcp_expr_and2(ohcp_expr_inv(ports.a), ports.b)));
    
    if (m->ipriv != NULL) {
        *((const_mux_port_t*) m->ipriv) = ports;
    }
    
    return 0;
}

typedef struct vector_test_port_t {
    ohcp_node* clk;
    ohcp_node* a;
    ohcp_node* b0;
    ohcp_node* b1;
    
    ohcp_node* c;
    ohcp_node* d;
    ohcp_node* e;
    ohcp_node* f;
    ohcp_node* g;
    ohcp_node* h;
} vector_test_port_t;

ohcp_type* struct_type;

static int vector_test_build(ohcp_module* m)
{
    vector_test_port_t ports;
    
    ohcp_struct_field* f1 = ohcp_struct_field_create(
        ohcp_string_create_cstr("f1"), ohcp_type_create_vector(4, ohcp_logic));
    ohcp_struct_field* f2 = ohcp_struct_field_create(
        ohcp_string_create_cstr("f2"), ohcp_logic);
    
    ohcp_deque* field_list = ohcp_deque_create();
    ohcp_deque_push_back(field_list, f1);
    ohcp_deque_push_back(field_list, f2);
    
    struct_type = ohcp_type_create_struct(
        ohcp_string_create_cstr("my_struct"), field_list);
    
    ports.clk = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("clk"));
    ports.a = ohcp_module_create_port(m, ohcp_type_create_vector(4, ohcp_logic),
        OHCP_PORT_IN, ohcp_string_create_cstr("a"));
    ports.b0 = ohcp_module_create_port(m, ohcp_type_create_vector(3, ohcp_logic),
        OHCP_PORT_IN, ohcp_string_create_cstr("b0"));
    ports.b1 = ohcp_module_create_port(m, ohcp_type_create_vector(3, ohcp_logic),
        OHCP_PORT_IN, ohcp_string_create_cstr("b1"));
    
    ports.c = ohcp_module_create_port(m, ohcp_type_create_vector(7, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("c"));
    ports.d = ohcp_module_create_port(m, ohcp_type_create_vector(2, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("d"));
    ports.e = ohcp_module_create_port(m, ohcp_type_create_vector(4, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("e"));
    ports.f = ohcp_module_create_port(m, ohcp_type_create_vector(3, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("f"));
    ports.g = ohcp_module_create_port(m, ohcp_type_create_vector(3, ohcp_logic),
        OHCP_PORT_OUT, ohcp_string_create_cstr("g"));
    ports.h = ohcp_module_create_port(m, struct_type,
        OHCP_PORT_OUT, ohcp_string_create_cstr("h"));
    
    ohcp_module_assign(m, ports.c, ohcp_expr_vector_cat2(ports.a, ports.b0));
    ohcp_module_assign(m, ports.d, ohcp_expr_vector_range(ports.a, 1, 2));
    ohcp_module_assign(m, ports.e, ohcp_expr_dff(ports.clk, ports.a));
    
    const ohcp_node* mux_in_list [2];
    mux_in_list[0] = ports.b0;
    mux_in_list[1] = ports.b1;
    ohcp_module_assign(m, ports.f, ohcp_expr_mux(ports.a, 2, mux_in_list));
    
    ohcp_module_assign(m, ports.g, ohcp_expr_ge(ports.b0, ports.b1));
    
    const ohcp_node* struct_list [2];
    struct_list[0] = ports.a;
    struct_list[1] = ohcp_expr_vector_at(ports.b0, 2);
    ohcp_module_assign(m, ports.h, ohcp_expr_struct_cat(struct_type, 2, struct_list));
    
    return 0;
}

static ohcp_module_descr* vector_test_descr;

int main()
{
    ohcp_string* fname;
    ohcp_string* dump;
    int ret;
    
    ret = ohcp_init();
    if (ret != 0) {
        fprintf(stderr, "ohcp_init() == %d\n", ret);
        return -1;
    }
    
    const_mux_descr = ohcp_module_descr_create(ohcp_string_create_cstr("const_mux"), NULL, const_mux_build);
    vector_test_descr = ohcp_module_descr_create(ohcp_string_create_cstr("vector_test"), NULL, vector_test_build);
    
    ohcp_module* cm0 = ohcp_module_create(NULL, const_mux_descr, ohcp_string_create_cstr("cm"), NULL);
    ohcp_module* vt0 = ohcp_module_create(NULL, vector_test_descr, ohcp_string_create_cstr("vt0"), NULL);
    
    fname = ohcp_module_full_name(cm0, NULL);
    dump = ohcp_module_debug_str(cm0, NULL);
    
    fprintf(stderr, "fname == %s\n", ohcp_string_cstr(fname));
    fprintf(stderr, "%s\n", ohcp_string_cstr(dump));
    
    ohcp_string_destroy(dump);
    ohcp_string_destroy(fname);
    
    dump = ohcp_module_debug_str(vt0, NULL);
    fprintf(stderr, "%s\n", ohcp_string_cstr(dump));
    ohcp_string_destroy(dump);
    
    ohcp_module_destroy(vt0);
    ohcp_module_destroy(cm0);
    ohcp_module_descr_destroy(vector_test_descr);
    ohcp_module_descr_destroy(const_mux_descr);
    
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
