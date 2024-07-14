// File: test_type_01.c

#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"

// fprintf(stderr, "%s:%s():%u\n", __FILE__, __func__, __LINE__);

int main()
{
    int ret = ohcp_stats_init();
    if (ret != 0) {
        fprintf(stderr, "ohcp_stats_init() returned %d", ret);
    }
    
    ret = ohcp_typelist_init();
    if (ret != 0) {
        fprintf(stderr, "ohcp_type_init() returned %d", ret);
    }
    
    ohcp_string* ta00_name = NULL;
    ohcp_string* ta01_name = NULL;
    ohcp_string* ta02_name = NULL;
    ohcp_string* ta03_name = NULL;
    ohcp_string* ta04_name = ohcp_string_create_cstr("");
    ohcp_string* ta05_name = ohcp_string_create_cstr("");
    ohcp_string* ta06_name = ohcp_string_create_cstr("");
    ohcp_string* ta07_name = ohcp_string_create_cstr("");
    ohcp_string* ta08_name = ohcp_string_create_cstr("ta08");
    ohcp_string* ta09_name = ohcp_string_create_cstr("ta09");
    ohcp_string* ta0a_name = ohcp_string_create_cstr("ta0a");
    ohcp_string* ta0b_name = ohcp_string_create_cstr("ta0b");
    ohcp_string* ta0c_name = ohcp_string_create_cstr("ta0c");
    ohcp_string* ta0d_name = ohcp_string_create_cstr("ta0d");
    ohcp_string* ta0e_name = ohcp_string_create_cstr("ta0e");
    ohcp_string* ta0f_name = ohcp_string_create_cstr("ta0f");
    
    ohcp_string* ta00_litlist = NULL;
    ohcp_string* ta01_litlist = ohcp_string_create_cstr("");
    ohcp_string* ta02_litlist = ohcp_string_create_cstr("!");
    ohcp_string* ta03_litlist = ohcp_string_create_cstr("!@");
    ohcp_string* ta04_litlist = NULL;
    ohcp_string* ta05_litlist = ohcp_string_create_cstr("");
    ohcp_string* ta06_litlist = ohcp_string_create_cstr("!");
    ohcp_string* ta07_litlist = ohcp_string_create_cstr("!@");
    ohcp_string* ta08_litlist = NULL;
    ohcp_string* ta09_litlist = ohcp_string_create_cstr("");
    ohcp_string* ta0a_litlist = ohcp_string_create_cstr("!");
    ohcp_string* ta0b_litlist = ohcp_string_create_cstr("!@");
    ohcp_string* ta0c_litlist = NULL;
    ohcp_string* ta0d_litlist = ohcp_string_create_cstr("");
    ohcp_string* ta0e_litlist = ohcp_string_create_cstr("!");
    ohcp_string* ta0f_litlist = ohcp_string_create_cstr("!@");
    
    const ohcp_type* ta00 = ohcp_type_create_atomic(ta00_name, ta00_litlist);
    const ohcp_type* ta01 = ohcp_type_create_atomic(ta01_name, ta01_litlist);
    const ohcp_type* ta02 = ohcp_type_create_atomic(ta02_name, ta02_litlist);
    const ohcp_type* ta03 = ohcp_type_create_atomic(ta03_name, ta03_litlist);
    const ohcp_type* ta04 = ohcp_type_create_atomic(ta04_name, ta04_litlist);
    const ohcp_type* ta05 = ohcp_type_create_atomic(ta05_name, ta05_litlist);
    const ohcp_type* ta06 = ohcp_type_create_atomic(ta06_name, ta06_litlist);
    const ohcp_type* ta07 = ohcp_type_create_atomic(ta07_name, ta07_litlist);
    const ohcp_type* ta08 = ohcp_type_create_atomic(ta08_name, ta08_litlist);
    const ohcp_type* ta09 = ohcp_type_create_atomic(ta09_name, ta09_litlist);
    const ohcp_type* ta0a = ohcp_type_create_atomic(ta0a_name, ta0a_litlist);
    const ohcp_type* ta0b = ohcp_type_create_atomic(ta0b_name, ta0b_litlist);
    const ohcp_type* ta0c = ohcp_type_create_atomic(ta0c_name, ta0c_litlist);
    const ohcp_type* ta0d = ohcp_type_create_atomic(ta0d_name, ta0d_litlist);
    const ohcp_type* ta0e = ohcp_type_create_atomic(ta0e_name, ta0e_litlist);
    const ohcp_type* ta0f = ohcp_type_create_atomic(ta0f_name, ta0f_litlist);
    
    ohcp_string* ta00_dbgstr = ohcp_type_dump(ta00);
    ohcp_string* ta01_dbgstr = ohcp_type_dump(ta01);
    ohcp_string* ta02_dbgstr = ohcp_type_dump(ta02);
    ohcp_string* ta03_dbgstr = ohcp_type_dump(ta03);
    ohcp_string* ta04_dbgstr = ohcp_type_dump(ta04);
    ohcp_string* ta05_dbgstr = ohcp_type_dump(ta05);
    ohcp_string* ta06_dbgstr = ohcp_type_dump(ta06);
    ohcp_string* ta07_dbgstr = ohcp_type_dump(ta07);
    ohcp_string* ta08_dbgstr = ohcp_type_dump(ta08);
    ohcp_string* ta09_dbgstr = ohcp_type_dump(ta09);
    ohcp_string* ta0a_dbgstr = ohcp_type_dump(ta0a);
    ohcp_string* ta0b_dbgstr = ohcp_type_dump(ta0b);
    ohcp_string* ta0c_dbgstr = ohcp_type_dump(ta0c);
    ohcp_string* ta0d_dbgstr = ohcp_type_dump(ta0d);
    ohcp_string* ta0e_dbgstr = ohcp_type_dump(ta0e);
    ohcp_string* ta0f_dbgstr = ohcp_type_dump(ta0f);
    
    fprintf(stdout, "ta00 == %s\n", ta00_dbgstr != NULL ? ohcp_string_cstr(ta00_dbgstr) : NULL);
    fprintf(stdout, "ta01 == %s\n", ta01_dbgstr != NULL ? ohcp_string_cstr(ta01_dbgstr) : NULL);
    fprintf(stdout, "ta02 == %s\n", ta02_dbgstr != NULL ? ohcp_string_cstr(ta02_dbgstr) : NULL);
    fprintf(stdout, "ta03 == %s\n", ta03_dbgstr != NULL ? ohcp_string_cstr(ta03_dbgstr) : NULL);
    fprintf(stdout, "ta04 == %s\n", ta04_dbgstr != NULL ? ohcp_string_cstr(ta04_dbgstr) : NULL);
    fprintf(stdout, "ta05 == %s\n", ta05_dbgstr != NULL ? ohcp_string_cstr(ta05_dbgstr) : NULL);
    fprintf(stdout, "ta06 == %s\n", ta06_dbgstr != NULL ? ohcp_string_cstr(ta06_dbgstr) : NULL);
    fprintf(stdout, "ta07 == %s\n", ta07_dbgstr != NULL ? ohcp_string_cstr(ta07_dbgstr) : NULL);
    fprintf(stdout, "ta08 == %s\n", ta08_dbgstr != NULL ? ohcp_string_cstr(ta08_dbgstr) : NULL);
    fprintf(stdout, "ta09 == %s\n", ta09_dbgstr != NULL ? ohcp_string_cstr(ta09_dbgstr) : NULL);
    fprintf(stdout, "ta0a == %s\n", ta0a_dbgstr != NULL ? ohcp_string_cstr(ta0a_dbgstr) : NULL);
    fprintf(stdout, "ta0b == %s\n", ta0b_dbgstr != NULL ? ohcp_string_cstr(ta0b_dbgstr) : NULL);
    fprintf(stdout, "ta0c == %s\n", ta0c_dbgstr != NULL ? ohcp_string_cstr(ta0c_dbgstr) : NULL);
    fprintf(stdout, "ta0d == %s\n", ta0d_dbgstr != NULL ? ohcp_string_cstr(ta0d_dbgstr) : NULL);
    fprintf(stdout, "ta0e == %s\n", ta0e_dbgstr != NULL ? ohcp_string_cstr(ta0e_dbgstr) : NULL);
    fprintf(stdout, "ta0f == %s\n", ta0f_dbgstr != NULL ? ohcp_string_cstr(ta0f_dbgstr) : NULL);
    
    if (ta00 == NULL) ohcp_string_destroy(ta00_name);
    if (ta01 == NULL) ohcp_string_destroy(ta01_name);
    if (ta02 == NULL) ohcp_string_destroy(ta02_name);
    if (ta03 == NULL) ohcp_string_destroy(ta03_name);
    if (ta04 == NULL) ohcp_string_destroy(ta04_name);
    if (ta05 == NULL) ohcp_string_destroy(ta05_name);
    if (ta06 == NULL) ohcp_string_destroy(ta06_name);
    if (ta07 == NULL) ohcp_string_destroy(ta07_name);
    if (ta08 == NULL) ohcp_string_destroy(ta08_name);
    if (ta09 == NULL) ohcp_string_destroy(ta09_name);
    if (ta0a == NULL) ohcp_string_destroy(ta0a_name);
    if (ta0b == NULL) ohcp_string_destroy(ta0b_name);
    if (ta0c == NULL) ohcp_string_destroy(ta0c_name);
    if (ta0d == NULL) ohcp_string_destroy(ta0d_name);
    if (ta0e == NULL) ohcp_string_destroy(ta0e_name);
    if (ta0f == NULL) ohcp_string_destroy(ta0f_name);
    
    if (ta00 == NULL) ohcp_string_destroy(ta00_litlist);
    if (ta01 == NULL) ohcp_string_destroy(ta01_litlist);
    if (ta02 == NULL) ohcp_string_destroy(ta02_litlist);
    if (ta03 == NULL) ohcp_string_destroy(ta03_litlist);
    if (ta04 == NULL) ohcp_string_destroy(ta04_litlist);
    if (ta05 == NULL) ohcp_string_destroy(ta05_litlist);
    if (ta06 == NULL) ohcp_string_destroy(ta06_litlist);
    if (ta07 == NULL) ohcp_string_destroy(ta07_litlist);
    if (ta08 == NULL) ohcp_string_destroy(ta08_litlist);
    if (ta09 == NULL) ohcp_string_destroy(ta09_litlist);
    if (ta0a == NULL) ohcp_string_destroy(ta0a_litlist);
    if (ta0b == NULL) ohcp_string_destroy(ta0b_litlist);
    if (ta0c == NULL) ohcp_string_destroy(ta0c_litlist);
    if (ta0d == NULL) ohcp_string_destroy(ta0d_litlist);
    if (ta0e == NULL) ohcp_string_destroy(ta0e_litlist);
    if (ta0f == NULL) ohcp_string_destroy(ta0f_litlist);
    
    ohcp_string_destroy(ta00_dbgstr);
    ohcp_string_destroy(ta01_dbgstr);
    ohcp_string_destroy(ta02_dbgstr);
    ohcp_string_destroy(ta03_dbgstr);
    ohcp_string_destroy(ta04_dbgstr);
    ohcp_string_destroy(ta05_dbgstr);
    ohcp_string_destroy(ta06_dbgstr);
    ohcp_string_destroy(ta07_dbgstr);
    ohcp_string_destroy(ta08_dbgstr);
    ohcp_string_destroy(ta09_dbgstr);
    ohcp_string_destroy(ta0a_dbgstr);
    ohcp_string_destroy(ta0b_dbgstr);
    ohcp_string_destroy(ta0c_dbgstr);
    ohcp_string_destroy(ta0d_dbgstr);
    ohcp_string_destroy(ta0e_dbgstr);
    ohcp_string_destroy(ta0f_dbgstr);
    
    const ohcp_type* tv00 = ohcp_type_create_vector(0, NULL);
    const ohcp_type* tv01 = ohcp_type_create_vector(0, ta0a);
    const ohcp_type* tv02 = ohcp_type_create_vector(0, tv01);
    const ohcp_type* tv03 = ohcp_type_create_vector(0, tv02);
    const ohcp_type* tv04 = ohcp_type_create_vector(0, ta0a);
    const ohcp_type* tv05 = ohcp_type_create_vector(0, tv01);
    const ohcp_type* tv06 = ohcp_type_create_vector(0, tv02);
    const ohcp_type* tv07 = ohcp_type_create_vector(1, NULL);
    const ohcp_type* tv08 = ohcp_type_create_vector(1, ta0a);
    const ohcp_type* tv09 = ohcp_type_create_vector(1, tv08);
    const ohcp_type* tv0a = ohcp_type_create_vector(1, tv09);
    const ohcp_type* tv0b = ohcp_type_create_vector(1, ta0a);
    const ohcp_type* tv0c = ohcp_type_create_vector(1, tv08);
    const ohcp_type* tv0d = ohcp_type_create_vector(1, tv09);
    const ohcp_type* tv0e = ohcp_type_create_vector(2, NULL);
    const ohcp_type* tv0f = ohcp_type_create_vector(2, ta0a);
    const ohcp_type* tv10 = ohcp_type_create_vector(2, tv0f);
    const ohcp_type* tv11 = ohcp_type_create_vector(2, tv10);
    const ohcp_type* tv12 = ohcp_type_create_vector(2, ta0a);
    const ohcp_type* tv13 = ohcp_type_create_vector(2, tv0f);
    const ohcp_type* tv14 = ohcp_type_create_vector(2, tv10);
    
    ohcp_string* tv00_dbgstr = ohcp_type_dump(tv00);
    ohcp_string* tv01_dbgstr = ohcp_type_dump(tv01);
    ohcp_string* tv02_dbgstr = ohcp_type_dump(tv02);
    ohcp_string* tv03_dbgstr = ohcp_type_dump(tv03);
    ohcp_string* tv04_dbgstr = ohcp_type_dump(tv04);
    ohcp_string* tv05_dbgstr = ohcp_type_dump(tv05);
    ohcp_string* tv06_dbgstr = ohcp_type_dump(tv06);
    ohcp_string* tv07_dbgstr = ohcp_type_dump(tv07);
    ohcp_string* tv08_dbgstr = ohcp_type_dump(tv08);
    ohcp_string* tv09_dbgstr = ohcp_type_dump(tv09);
    ohcp_string* tv0a_dbgstr = ohcp_type_dump(tv0a);
    ohcp_string* tv0b_dbgstr = ohcp_type_dump(tv0b);
    ohcp_string* tv0c_dbgstr = ohcp_type_dump(tv0c);
    ohcp_string* tv0d_dbgstr = ohcp_type_dump(tv0d);
    ohcp_string* tv0e_dbgstr = ohcp_type_dump(tv0e);
    ohcp_string* tv0f_dbgstr = ohcp_type_dump(tv0f);
    ohcp_string* tv10_dbgstr = ohcp_type_dump(tv10);
    ohcp_string* tv11_dbgstr = ohcp_type_dump(tv11);
    ohcp_string* tv12_dbgstr = ohcp_type_dump(tv12);
    ohcp_string* tv13_dbgstr = ohcp_type_dump(tv13);
    ohcp_string* tv14_dbgstr = ohcp_type_dump(tv14);
    
    fprintf(stdout, "tv00 == %s\n", tv00_dbgstr != NULL ? ohcp_string_cstr(tv00_dbgstr) : NULL);
    fprintf(stdout, "tv01 == %s\n", tv01_dbgstr != NULL ? ohcp_string_cstr(tv01_dbgstr) : NULL);
    fprintf(stdout, "tv02 == %s\n", tv02_dbgstr != NULL ? ohcp_string_cstr(tv02_dbgstr) : NULL);
    fprintf(stdout, "tv03 == %s\n", tv03_dbgstr != NULL ? ohcp_string_cstr(tv03_dbgstr) : NULL);
    fprintf(stdout, "tv04 == %s\n", tv04_dbgstr != NULL ? ohcp_string_cstr(tv04_dbgstr) : NULL);
    fprintf(stdout, "tv05 == %s\n", tv05_dbgstr != NULL ? ohcp_string_cstr(tv05_dbgstr) : NULL);
    fprintf(stdout, "tv06 == %s\n", tv06_dbgstr != NULL ? ohcp_string_cstr(tv06_dbgstr) : NULL);
    fprintf(stdout, "tv07 == %s\n", tv07_dbgstr != NULL ? ohcp_string_cstr(tv07_dbgstr) : NULL);
    fprintf(stdout, "tv08 == %s\n", tv08_dbgstr != NULL ? ohcp_string_cstr(tv08_dbgstr) : NULL);
    fprintf(stdout, "tv09 == %s\n", tv09_dbgstr != NULL ? ohcp_string_cstr(tv09_dbgstr) : NULL);
    fprintf(stdout, "tv0a == %s\n", tv0a_dbgstr != NULL ? ohcp_string_cstr(tv0a_dbgstr) : NULL);
    fprintf(stdout, "tv0b == %s\n", tv0b_dbgstr != NULL ? ohcp_string_cstr(tv0b_dbgstr) : NULL);
    fprintf(stdout, "tv0c == %s\n", tv0c_dbgstr != NULL ? ohcp_string_cstr(tv0c_dbgstr) : NULL);
    fprintf(stdout, "tv0d == %s\n", tv0d_dbgstr != NULL ? ohcp_string_cstr(tv0d_dbgstr) : NULL);
    fprintf(stdout, "tv0e == %s\n", tv0e_dbgstr != NULL ? ohcp_string_cstr(tv0e_dbgstr) : NULL);
    fprintf(stdout, "tv0f == %s\n", tv0f_dbgstr != NULL ? ohcp_string_cstr(tv0f_dbgstr) : NULL);
    fprintf(stdout, "tv10 == %s\n", tv10_dbgstr != NULL ? ohcp_string_cstr(tv10_dbgstr) : NULL);
    fprintf(stdout, "tv11 == %s\n", tv11_dbgstr != NULL ? ohcp_string_cstr(tv11_dbgstr) : NULL);
    fprintf(stdout, "tv12 == %s\n", tv12_dbgstr != NULL ? ohcp_string_cstr(tv12_dbgstr) : NULL);
    fprintf(stdout, "tv13 == %s\n", tv13_dbgstr != NULL ? ohcp_string_cstr(tv13_dbgstr) : NULL);
    fprintf(stdout, "tv14 == %s\n", tv14_dbgstr != NULL ? ohcp_string_cstr(tv14_dbgstr) : NULL);
    
    ohcp_string_destroy(tv00_dbgstr);
    ohcp_string_destroy(tv01_dbgstr);
    ohcp_string_destroy(tv02_dbgstr);
    ohcp_string_destroy(tv03_dbgstr);
    ohcp_string_destroy(tv04_dbgstr);
    ohcp_string_destroy(tv05_dbgstr);
    ohcp_string_destroy(tv06_dbgstr);
    ohcp_string_destroy(tv07_dbgstr);
    ohcp_string_destroy(tv08_dbgstr);
    ohcp_string_destroy(tv09_dbgstr);
    ohcp_string_destroy(tv0a_dbgstr);
    ohcp_string_destroy(tv0b_dbgstr);
    ohcp_string_destroy(tv0c_dbgstr);
    ohcp_string_destroy(tv0d_dbgstr);
    ohcp_string_destroy(tv0e_dbgstr);
    ohcp_string_destroy(tv0f_dbgstr);
    ohcp_string_destroy(tv10_dbgstr);
    ohcp_string_destroy(tv11_dbgstr);
    ohcp_string_destroy(tv12_dbgstr);
    ohcp_string_destroy(tv13_dbgstr);
    ohcp_string_destroy(tv14_dbgstr);
    
    ohcp_type* tt00;
    ohcp_deque* tt00_field_list;
    
    tt00_field_list = ohcp_deque_create();
    ohcp_deque_push_back(tt00_field_list, ohcp_struct_field_create(ohcp_string_create_cstr("a"), ta0f));
    ohcp_deque_push_back(tt00_field_list, ohcp_struct_field_create(ohcp_string_create_cstr("b"), tv0f));
    ohcp_deque_push_back(tt00_field_list, ohcp_struct_field_create(ohcp_string_create_cstr("c"), tv10));
    
    tt00 = ohcp_type_create_struct(ohcp_string_create_cstr("tt00"), tt00_field_list);
    
    ohcp_string* tt00_dbgstr = ohcp_type_dump(tt00);
    
    fprintf(stdout, "tt00 == %s\n", tt00_dbgstr != NULL ? ohcp_string_cstr(tt00_dbgstr) : NULL);
    
    ohcp_string_destroy(tt00_dbgstr);
    
    for (const ohcp_deque_entry* iter = ohcp_typelist_first() ; iter != NULL ; iter = iter->next) {
        const ohcp_type* type = (ohcp_type*) iter->data;
        ohcp_string* typestr = ohcp_type_dump(type);
        
        fprintf(stdout, "type_list entry: type == %p | %s\n", (void*) type, ohcp_string_cstr(typestr));
        
        ohcp_string_destroy(typestr);
    }
    
    for (const ohcp_deque_entry* iter = ohcp_stats_first() ; iter != NULL ; iter = iter->next) {
        const ohcp_stats_entry* se = iter->data;
        ohcp_string* sevstr = ohcp_severity_to_str(se->sev);
        
        fprintf(stdout, "%s %s\n", ohcp_string_cstr(sevstr), ohcp_string_cstr(se->msg));
        
        ohcp_string_destroy(sevstr);
    }
    
    ohcp_typelist_cleanup();
    ohcp_stats_cleanup();
    
    return 0;
}
