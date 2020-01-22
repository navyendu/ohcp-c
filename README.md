# Open Hardware Construction Platform - C API

Reference implementation of OHCP in C

    int build_adder(ohcp_module* m) {
        // Add a port to the module
        ohcp_node* a = ohcp_module_create_port(m, ohcp_type_vector(4, ohcp_logic), OHCP_PORT_IN, "a");
        ohcp_node* b = ohcp_module_create_port(m, ohcp_type_vector(4, ohcp_logic), OHCP_PORT_IN, "b");
        ohcp_node* c;
        // Conditionally add port
        if (add_3) {
            c = ohcp_module_create_port(m, ohcp_logic, OHCP_PORT_IN, "c");
        }
        ohcp_node* o = module_create_port("o", PORT_OUT, type_array(logic, WIDTH));
        
        // Conditional assignment
        if (add_3) {
            ohcp_assign(o, expr_add3(a, b, c));
        } else {
            ohcp_assign(o, expr_add2(a, b));
        }
        
        return 0;
    }
    
    ohcp_module_descr adder = {
        .build = build_adder
    }
    
    int main() {
        ohcp_module* a0 = ohcp_module_create(adder, "a0");
        
        ohcp_synthesize(a0);
        ohcp_dump_sv(a0, "file.sv");
    }

## Acknowledgments

_I humbly present this work to The Supreme Protector who resides in the beautiful temple at the heart of Guruvayur town_

_Special thanks to my parents, my uncle and my cousin for their support in my scientific endeavors_

## About

*Work in progress*
