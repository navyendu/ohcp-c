// File: ohcp_string.h

#ifndef OHCP_STRING_H
#define OHCP_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ohcp_string ohcp_string;
struct ohcp_string
{
    size_t      capacity;
    size_t      len;
    
    char*       cstr;
};

/* move */ ohcp_string* ohcp_string_create          ();
/* move */ ohcp_string* ohcp_string_create_str      (/* ref */ const ohcp_string* str0);
/* move */ ohcp_string* ohcp_string_create_cstr     (/* ref */ const char* cstr);
/* move */ ohcp_string* ohcp_string_create_lcstr    (size_t len, /* ref */ const char* cstr);
/* move */ ohcp_string* ohcp_string_create_plcstr   (size_t capacity, size_t len, /* ref */ const char* cstr0);
void                    ohcp_string_destroy         (/* move */ const ohcp_string* str);

/* ref */ ohcp_string*  ohcp_string_clear           (/* ref */ ohcp_string* str);

/* ref */ ohcp_string*  ohcp_string_set             (/* ref */ ohcp_string* str, /* ref */ const ohcp_string* str0);
/* ref */ ohcp_string*  ohcp_string_set_cstr        (/* ref */ ohcp_string* str, /* ref */ const char* cstr);
/* ref */ ohcp_string*  ohcp_string_set_lcstr       (/* ref */ ohcp_string* str, size_t len, /* ref */ const char* cstr);

/* ref */ ohcp_string*  ohcp_string_cat             (/* ref */ ohcp_string* str, /* ref */ const ohcp_string* str0);
/* ref */ ohcp_string*  ohcp_string_cat_cstr        (/* ref */ ohcp_string* str, /* ref */ const char* cstr);
/* ref */ ohcp_string*  ohcp_string_cat_lcstr       (/* ref */ ohcp_string* str, size_t len, /* ref */ const char* cstr);

size_t                  ohcp_string_len             (/* ref */ const ohcp_string* str);
size_t                  ohcp_string_capacity        (/* ref */ const ohcp_string* str);
/* ref */ char*         ohcp_string_cstr            (/* ref */ const ohcp_string* str);

#ifdef __cplusplus
}
#endif

#endif
