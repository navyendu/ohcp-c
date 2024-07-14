// File: ohcp_string.c

#include <string.h>
#include <stdlib.h>

#include "ohcp_string.h"

ohcp_string* ohcp_string_create()
{
    return ohcp_string_create_plcstr(16, 0, "");
}

ohcp_string* ohcp_string_create_str(const ohcp_string* str0)
{
    if (str0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_create_lcstr(str0->len, str0->cstr);
}

ohcp_string* ohcp_string_create_cstr(const char* cstr0)
{
    if (cstr0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_create_lcstr(strlen(cstr0), cstr0);
}

ohcp_string* ohcp_string_create_lcstr(size_t len, const char* cstr0)
{
    return ohcp_string_create_plcstr(len + 1, len, cstr0);
}

ohcp_string* ohcp_string_create_plcstr(size_t capacity, size_t len, const char* cstr0)
{
    ohcp_string*    str;
    char*           cstr;
    
    if (capacity <= len) {
        return NULL;
    }
    
    if (cstr0 == NULL) {
        return NULL;
    }
    
    do {
        cstr = calloc(capacity, sizeof(char));
        if (cstr == NULL) {
            break;
        }
        
        do {
            str = malloc(sizeof(ohcp_string));
            if (str == NULL) {
                break;
            }
            
            strncpy(cstr, cstr0, len);
            cstr[len] = '\0';
            
            str->capacity = capacity;
            str->len = len;
            str->cstr = cstr;
            
            return str;
        } while (0);
        
        free(cstr);
    } while (0);
    
    return NULL;
}

void ohcp_string_destroy(const ohcp_string* str)
{
    if (str != NULL) {
        free(str->cstr);
    }
    
    free((void*) str);
}

ohcp_string* ohcp_string_clear(ohcp_string* str)
{
    if (str == NULL) {
        return NULL;
    }
    
    str->len = 0;
    str->cstr[0] = '\0';
    
    return str;
}

ohcp_string* ohcp_string_set(ohcp_string* str, const ohcp_string* str0)
{
    if (str0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_set_lcstr(str, str0->len, str0->cstr);
}

ohcp_string* ohcp_string_set_cstr(ohcp_string* str, const char* cstr0)
{
    if (cstr0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_set_lcstr(str, strlen(cstr0), cstr0);
}

ohcp_string* ohcp_string_set_lcstr(ohcp_string* str, size_t len, const char* cstr0)
{
    size_t  capacity;
    char*   cstr;
    
    if (str == NULL) {
        return NULL;
    }
    
    if (cstr0 == NULL) {
        return NULL;
    }
    
    capacity = len + 1;
    
    if (str->capacity < capacity) {
        cstr = calloc(capacity, sizeof(char));
        if (cstr == NULL) {
            return NULL;
        }
    } else {
        cstr = str->cstr;
        str->cstr = NULL;
        capacity = str->capacity;
    }
    
    strncpy(cstr, cstr0, len);
    cstr[len] = '\0';
    
    free(str->cstr);
    
    str->capacity = capacity;
    str->len = len;
    str->cstr = cstr;
    
    return str;
}

ohcp_string* ohcp_string_cat(ohcp_string* str, const ohcp_string* str0)
{
    if (str0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_cat_lcstr(str, str0->len, str0->cstr);
}

ohcp_string* ohcp_string_cat_cstr(ohcp_string* str, const char* cstr0)
{
    if (cstr0 == NULL) {
        return NULL;
    }
    
    return ohcp_string_cat_lcstr(str, strlen(cstr0), cstr0);
}

ohcp_string* ohcp_string_cat_lcstr(ohcp_string* str, size_t len0, const char* cstr0)
{
    size_t  capacity;
    size_t  len;
    char*   cstr;
    
    if (str == NULL) {
        return NULL;
    }
    
    if (cstr0 == NULL) {
        return NULL;
    }
    
    len = str->len + len0;
    capacity = len + 1;
    
    if (str->capacity < capacity) {
        cstr = calloc(capacity, sizeof(char));
        if (cstr == NULL) {
            return NULL;
        }
        
        strcpy(cstr, str->cstr);
    } else {
        cstr = str->cstr;
        str->cstr = NULL;
        capacity = str->capacity;
    }
    
    strncat(cstr, cstr0, len0);
    cstr[len] = '\0';
    
    free(str->cstr);
    
    str->capacity = capacity;
    str->len = len;
    str->cstr = cstr;
    
    return str;
}

size_t ohcp_string_len(const ohcp_string* str)
{
    if (str == NULL) {
        return 0;
    }
    
    return str->len;
}

size_t ohcp_string_capacity(const ohcp_string* str)
{
    if (str == NULL) {
        return 0;
    }
    
    return str->capacity;
}

char* ohcp_string_cstr(const ohcp_string* str)
{
    if (str == NULL) {
        return NULL;
    }
    
    return str->cstr;
}
