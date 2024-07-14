// File: test_string_01.c

#include <stdio.h>

#include "ohcp_string.h"

int main()
{
    ohcp_string* str0;
    ohcp_string* str1;
    ohcp_string* str2;
    
    str0 = ohcp_string_create();
    str1 = ohcp_string_create_str(str0);
    str2 = ohcp_string_create_cstr("hello");
    
    fprintf(stdout, "str0 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str0->capacity, str0->len, str0->cstr);
    fprintf(stdout, "str1 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str1->capacity, str1->len, str1->cstr);
    fprintf(stdout, "str2 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str2->capacity, str2->len, str2->cstr);
    
    ohcp_string_set_cstr(str0, "Hello");
    ohcp_string_set_cstr(str1, "Bel");
    
    fprintf(stdout, "str0 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str0->capacity, str0->len, str0->cstr);
    fprintf(stdout, "str1 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str1->capacity, str1->len, str1->cstr);
    
    ohcp_string_cat_cstr(str0, " World");
    ohcp_string_set_cstr(str1, "B");
    
    fprintf(stdout, "str0 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str0->capacity, str0->len, str0->cstr);
    fprintf(stdout, "str1 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str1->capacity, str1->len, str1->cstr);
    
    ohcp_string_set(str0, str1);
    ohcp_string_cat(str2, str1);
    
    fprintf(stdout, "str0 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str0->capacity, str0->len, str0->cstr);
    fprintf(stdout, "str2 == { cap: %lu, len: %lu, cstr: \"%s\" }\n",
        str2->capacity, str2->len, str2->cstr);
    
    ohcp_string_destroy(str2);
    ohcp_string_destroy(str1);
    ohcp_string_destroy(str0);
    
    return 0;
}
