#include "fifo.h"

int main()
{
    ohcp_init();
    
    fifo_params params;
    params.depth = 4;
    params.width = 17;
    
    ohcp_module_descr* fd = fifo_descr(&params);
    
    fifo_ports f0_ports;
    ohcp_module* f0 = ohcp_module_create(NULL, fd, ohcp_string_create_cstr("f0"), &f0_ports);
    
    ohcp_string* fname = ohcp_module_full_name(f0, NULL);
    ohcp_string* dump = ohcp_module_debug_str(f0, NULL);
    
    fprintf(stderr, "fname == %s\n", ohcp_string_cstr(fname));
    fprintf(stderr, "%s\n", ohcp_string_cstr(dump));
    
    ohcp_string_destroy(dump);
    ohcp_string_destroy(fname);
    
    ohcp_module_destroy(f0);
    ohcp_module_descr_destroy(fd);
    
    ohcp_cleanup();
}
