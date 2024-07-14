// File: test_expr_01.c

#include "ohcp_stats.h"
#include "ohcp_expr_buf.h"
#include "ohcp_expr_vector.h"
#include "ohcp_logic.h"
#include "ohcp.h"

int main()
{
    int ret;
    
    ret = ohcp_init();
    fprintf(stderr, "ohcp_init() == %d\n", ret);
    
    ohcp_node* vec_node = ohcp_node_create(
        ohcp_type_create_vector(4, ohcp_logic),
        ohcp_string_create_cstr("vec_node"));
    ohcp_string* dumpstr = ohcp_node_debug_str(vec_node);
    fprintf(stderr, "vec_node == {%s}\n", ohcp_string_cstr(dumpstr));
    ohcp_string_destroy(dumpstr);
    
    ohcp_node* out = ohcp_expr_vector_at(vec_node, 0);
    dumpstr = ohcp_node_debug_str(out);
    fprintf(stderr, "out == {%s}\n", ohcp_string_cstr(dumpstr));
    ohcp_string_destroy(dumpstr);
    
    ohcp_expr* expr = out->driver;
    dumpstr = ohcp_expr_dump(expr);
    fprintf(stderr, "expr == {%s}\n", ohcp_string_cstr(dumpstr));
    ohcp_string_destroy(dumpstr);
    
    ohcp_node* out2 = ohcp_expr_buf(vec_node);
    fprintf(stderr, "out2 == @%p\n", (void*) out2);
    dumpstr = ohcp_node_debug_str(out2);
    fprintf(stderr, "dumpstr == @%p\n", (void*) dumpstr);
    fprintf(stderr, "out2 == {%s}\n", ohcp_string_cstr(dumpstr));
    ohcp_string_destroy(dumpstr);
    
    ohcp_expr* expr2 = out2->driver;
    dumpstr = ohcp_expr_dump(expr2);
    fprintf(stderr, "expr2 == {%s}\n", ohcp_string_cstr(dumpstr));
    ohcp_string_destroy(dumpstr);
    
    ohcp_node_destroy(out);
    ohcp_expr_destroy(expr);
    
    ohcp_node_destroy(out2);
    ohcp_expr_destroy(expr2);
    
    ohcp_node_destroy(vec_node);
    
    ohcp_cleanup();
    
    return 0;
}
