// File: test_node_01.c

#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_node.h"
#include "ohcp_logic.h"
#include "ohcp_module.h"

int main()
{
    int             ret;
    ohcp_node*      n;
    ohcp_string*    fname;
    ohcp_string*    dump;
    ohcp_string*    name;
    
    ret = ohcp_stats_init();
    fprintf(stdout, "ohcp_stats_init() == %d\n", ret);
    
    ret = ohcp_typelist_init();
    fprintf(stdout, "ohcp_type_init() == %d\n", ret);
    
    ret = ohcp_logic_init();
    fprintf(stdout, "ohcp_logic_init() == %d\n", ret);
    
    name = ohcp_string_create_cstr("myNode");
    n = ohcp_node_create(ohcp_type_create_vector(4, ohcp_logic), name);
    
    fname = ohcp_module_full_name(NULL, n);
    dump = ohcp_node_debug_str(n);
    
    fprintf(stdout, "n == %p\n", (void*) n);
    fprintf(stdout, "fname == %s\n", fname != NULL ? ohcp_string_cstr(fname) : NULL);
    fprintf(stdout, "dump == %s\n", dump != NULL ? ohcp_string_cstr(dump) : NULL);
    
    ohcp_string_destroy(fname);
    ohcp_string_destroy(dump);
    ohcp_node_destroy(n);
    
    ohcp_typelist_cleanup();
    ohcp_stats_cleanup();
    
    return 0;
}
