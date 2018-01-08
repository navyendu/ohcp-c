# Open Hardware Construction Platform - C API

Reference implementation of OHCP in C

    int build_adder(module * m) {
        node * a = module_create_port("a", PORT_IN, type_array(logic, WIDTH));      // Add a port to the module
        node * b = module_create_port("b", PORT_IN, type_array(logic, WIDTH));
        node * c;
        if (add_3) {                                            // Conditionally add port
            c = module_create_port("b", PORT_IN, type_array(logic, WIDTH));
        }
        node * o = module_create_port("o", PORT_OUT, type_array(logic, WIDTH));
        
        if (add_3) {
            expr_add3(o, a, b, c);
        } else {
            expr_add2(o, a, b);
        }
        
        return 0;
    }
    
    module_descr adder = {
        .build = build_adder
    }
    
    int main() {
        module * a0 = module_create(adder, "a0");
        
        synthesize(a0);
        dump_sysverilog(a0, "file.sv");
    }

## Acknowledgments

_I humbly present this work to The Supreme Protector who resides in the beautiful temple at the heart of Guruvayur town_

_Special thanks to my parents, my uncle and my cousin for their support in my scientific endeavors_

## About

*Work in progress*
