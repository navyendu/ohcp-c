#include "aoi.h"

int main()
{
    ohcp_init();
    
    aoi_params params;
    params.width = 32;
    params.use_c = false;
    
    ohcp_module_descr* ad = aoi_descr(&params);
    
    aoi_ports a0_ports;
    ohcp_module* a0 = ohcp_module_create(NULL, ad, ohcp_string_create_cstr("a0"), &a0_ports);
    
    ohcp_string* fname = ohcp_module_full_name(a0, NULL);
    ohcp_string* dump = ohcp_module_debug_str(a0, NULL);
    
    fprintf(stderr, "fname == %s\n", ohcp_string_cstr(fname));
    fprintf(stderr, "%s\n", ohcp_string_cstr(dump));
    
    ohcp_string_destroy(dump);
    ohcp_string_destroy(fname);
    
    ohcp_module_destroy(a0);
    ohcp_module_descr_destroy(ad);
    
    ohcp_cleanup();
}
