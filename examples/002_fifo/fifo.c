#include <math.h>

#include "fifo.h"

static int fifo_build (ohcp_module* m)
{
    fifo_ports ports;
    fifo_params params = *((fifo_params*) m->descr->priv);
    
    ports.clk = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("clk"));
    ports.rst = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("rst"));
    
    ports.wr_en = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("wr_en"));
    ports.wr_data = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_IN, ohcp_string_create_cstr("wr_data"));
    
    ports.rd_en = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, ohcp_string_create_cstr("rd_en"));
    ports.rd_data = ohcp_module_create_port(m, ohcp_type_create_vector(params.width, ohcp_logic), OHCP_PORT_OUT, ohcp_string_create_cstr("rd_data"));
    
    ports.full = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("full"));
    ports.empty = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_OUT, ohcp_string_create_cstr("empty"));
    
    size_t ptr_width = (size_t) ceil(log2(params.depth));
    
    ohcp_node* rptr_ext;
    ohcp_node* wptr_ext;
    ohcp_node* rptr;
    ohcp_node* wptr;
    
    ohcp_node* literal [params.depth];
    ohcp_node* storage_wr_en [params.depth];
    ohcp_node* storage [params.depth];
    
    ohcp_node* literal_1;
    
    rptr_ext = ohcp_module_create_node(m, ohcp_type_create_vector(ptr_width + 1, ohcp_logic), ohcp_string_create_cstr("rptr_ext"));
    wptr_ext = ohcp_module_create_node(m, ohcp_type_create_vector(ptr_width + 1, ohcp_logic), ohcp_string_create_cstr("wptr_ext"));
    
    rptr = ohcp_expr_vector_range(rptr_ext, 0, ptr_width);
    wptr = ohcp_expr_vector_range(wptr_ext, 0, ptr_width);
    
    literal_1 = ohcp_module_create_node(m, ohcp_type_create_vector(1, ohcp_logic), ohcp_string_create_cstr("1"));
    
    for (size_t i = 0 ; i < params.depth ; i++) {
        literal[i] = ohcp_module_create_node(m, ohcp_type_create_vector(32, ohcp_logic), ohcp_string_create());
        storage_wr_en[i] = ohcp_module_create_node(m, ohcp_logic, ohcp_string_create());
        storage[i] = ohcp_module_create_node(m, ohcp_type_create_vector(params.width, ohcp_logic), ohcp_string_create());
        
        // We don't have the api capability to assign a literal value to a node yet
        // literal[i] = ohcp_expr_const(i);
        ohcp_module_assign(m, storage_wr_en[i], ohcp_expr_and2(ports.wr_en, ohcp_expr_eq(wptr, literal[i])));
        
        const ohcp_node* mux_in [2] = { storage[i], ports.wr_data };
        
        ohcp_module_assign(m, storage[i], ohcp_expr_dff(ports.clk, ohcp_expr_mux(storage_wr_en[i], 2, mux_in)));
    }
    
    const ohcp_node* w_mux_in [2] = { wptr_ext, ohcp_expr_and2(wptr_ext, literal_1) };
    const ohcp_node* r_mux_in [2] = { rptr_ext, ohcp_expr_and2(rptr_ext, literal_1) };
    
    // We don't have a working expression for d flip flop with reset and enable :(
    ohcp_module_assign(m, wptr_ext, ohcp_expr_dff(ports.clk, ohcp_expr_mux(ports.wr_en, 2, w_mux_in) ));
    ohcp_module_assign(m, rptr_ext, ohcp_expr_dff(ports.clk, ohcp_expr_mux(ports.rd_en, 2, r_mux_in) ));
    
    ohcp_module_assign(m, ports.rd_data, ohcp_expr_mux(rptr, params.depth, (const ohcp_node**) storage));
    
    ohcp_module_assign(m, ports.full, ohcp_expr_and2(
        ohcp_expr_eq(ohcp_expr_vector_at(wptr_ext, ptr_width),
        ohcp_expr_vector_at(rptr_ext, ptr_width)), ohcp_expr_eq(wptr, rptr)));
    ohcp_module_assign(m, ports.empty, ohcp_expr_and2(
        ohcp_expr_ne(ohcp_expr_vector_at(wptr_ext, ptr_width),
        ohcp_expr_vector_at(rptr_ext, ptr_width)), ohcp_expr_eq(wptr, rptr)));
    
    if (m->ipriv != NULL) {
        *((fifo_ports*) m->ipriv) = ports;
    }
    
    return 0;
}

ohcp_module_descr* fifo_descr (const fifo_params* params)
{
    return ohcp_module_descr_create(ohcp_string_create_cstr("fifo"), (fifo_params*) params, fifo_build);
}
