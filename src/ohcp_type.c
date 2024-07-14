// File: ohcp_type.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ohcp_stats.h"
#include "ohcp_type.h"

static ohcp_deque*  type_list;
static ohcp_deque*  atomic_list;
static ohcp_deque*  vector_list;
static ohcp_deque*  tuple_list;

// fprintf(stderr, "here: %s:%d:%s()\n", __FILE__, __LINE__, __func__);

ohcp_type* ohcp_type_create_atomic(/* move */ const ohcp_string* name, /* move */ const ohcp_string* literal_list)
{
    ohcp_type* type;
    ohcp_typedescr_atomic* descr;
    
    if (type_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (atomic_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): atomic_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    // if (std::find(atomic_list_ptr->cbegin(), atomic_list_ptr->cend(), string(name->cstr)) != atomic_list_ptr->cend()) {
    //     throw std::logic_error("Atomic type " + string(name->cstr) + " already exists");
    // }
    
    do {
        descr = ohcp_typedescr_atomic_create(name, literal_list);
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create atomic type descriptor", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            type = malloc(sizeof(ohcp_type));
            if (type == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc ohcp_type", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            type->typetype = OHCP_TYPETYPE_ATOMIC;
            type->descr = descr;
            
            do {
                int push_ret;
                
                push_ret = ohcp_deque_push_back(type_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into type_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                push_ret = ohcp_deque_push_back(atomic_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into atomic_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                return type;
            } while (0);
            
            free(type);
        } while (0);
        
        ohcp_typedescr_atomic_destroy(descr);
    } while (0);
    
    return NULL;
}

ohcp_type* ohcp_type_create_vector(size_t size, /* ref */ const ohcp_type* base)
{
    ohcp_type* type;
    ohcp_typedescr_vector* descr;
    
    if (type_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (vector_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): vector_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    {
        // Search for existing (size, base)
        for (ohcp_deque_entry* de = ohcp_deque_first(vector_list) ; de != NULL ; de = de->next) {
            ohcp_type* de_type;
            const ohcp_typedescr_vector* de_descr;
            
            de_type = (ohcp_type*) de->data;
            
            assert (de_type != NULL);
            assert (de_type->typetype == OHCP_TYPETYPE_VECTOR);
            
            de_descr = (ohcp_typedescr_vector*) de_type->descr;
            
            assert (de_descr != NULL);
            
            if (de_descr->size == size && de_descr->base == base) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "Found vector type [%lu,%p] @%p",
                    size, (void*) base, (void*) de_type);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, buf));
                
                return de_type;
            }
        }
    }
    
    do {
        descr = ohcp_typedescr_vector_create(size, base);
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create vector type descriptor", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            type = malloc(sizeof(ohcp_type));
            if (type == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc type", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            type->typetype = OHCP_TYPETYPE_VECTOR;
            type->descr = descr;
            
            do {
                int push_ret;
                
                push_ret = ohcp_deque_push_back(type_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into type_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                push_ret = ohcp_deque_push_back(vector_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into vector_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                if (1) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "Created vector type [%lu,@%p] @%p",
                        size, (void*) base, (void*) type);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, buf));
                }
                return type;
            } while (0);
            
            free(type);
        } while (0);
        
        ohcp_typedescr_vector_destroy(descr);
    } while (0);
    
    return NULL;
}

ohcp_type* ohcp_type_create_struct(/* move */ const ohcp_string* name, /* move */ ohcp_deque* field_list)
{
    ohcp_type* type;
    ohcp_typedescr_struct* descr;
    
    if (type_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): type_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (tuple_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): tuple_list is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        descr = ohcp_typedescr_struct_create(name, field_list);
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to create vector type descriptor", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            type = malloc(sizeof(ohcp_type));
            if (type == NULL) {
                char    buf [1024];
                int     ret;
                size_t  len;
                
                ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc type", __func__);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            type->typetype = OHCP_TYPETYPE_STRUCT;
            type->descr = descr;
            
            do {
                int push_ret;
                
                push_ret = ohcp_deque_push_back(type_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into type_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                push_ret = ohcp_deque_push_back(tuple_list, type);
                if (push_ret != 0) {
                    char    buf [1024];
                    int     ret;
                    size_t  len;
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): Failed to push type object into tuple_list", __func__);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                return type;
            } while (0);
            
            free(type);
        } while (0);
        
        ohcp_typedescr_struct_destroy(descr);
    } while (0);
    
    return NULL;
}

void ohcp_type_destroy(/* move */ const ohcp_type* type)
{
    if (type != NULL) {
        if (type->typetype == OHCP_TYPETYPE_ATOMIC) {
            ohcp_typedescr_atomic_destroy((ohcp_typedescr_atomic*) type->descr);
        } else if (type->typetype == OHCP_TYPETYPE_VECTOR) {
            ohcp_typedescr_vector_destroy((ohcp_typedescr_vector*) type->descr);
        } else if (type->typetype == OHCP_TYPETYPE_STRUCT) {
            ohcp_typedescr_struct_destroy((ohcp_typedescr_struct*) type->descr);
        }
    }
    
    free((void*) type);
}

ohcp_string* ohcp_type_to_str(/* ref */ const ohcp_type* type)
{
    ohcp_string* str;
    
    if (type == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'type\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->typetype > OHCP_TYPETYPE_STRUCT) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): typetype (%d) is not in valid range",
            __func__, type->typetype);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->typetype == OHCP_TYPETYPE_ATOMIC) {
        ohcp_typedescr_atomic*  descr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_atomic*) type->descr;
        
        ret = snprintf(buf, sizeof(buf), "%s", ohcp_string_cstr(descr->name));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        str = ohcp_string_create_lcstr(len, buf);
    } else if (type->typetype == OHCP_TYPETYPE_VECTOR) {
        ohcp_typedescr_vector*  descr;
        ohcp_string*            basestr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_vector*) type->descr;
        basestr = ohcp_type_to_str(descr->base);
        
        ret = snprintf(buf, sizeof(buf), "[%lu %s]", descr->size, ohcp_string_cstr(basestr));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_string_destroy(basestr);
        
        str = ohcp_string_create_lcstr(len, buf);
    } else {
        ohcp_typedescr_struct*   descr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_struct*) type->descr;
        
        str = ohcp_string_create_cstr("[");
        for (const ohcp_deque_entry* de = ohcp_deque_first(descr->field_list) ; de != NULL ; de = de->next) {
            const ohcp_struct_field* field;
            ohcp_string* basestr;
            
            field = (ohcp_struct_field*) de->data;
            basestr = ohcp_type_to_str(field->base);
            
            ret = snprintf(buf, sizeof(buf), de->next == NULL ? "%s" : "%s,", ohcp_string_cstr(basestr));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            str = ohcp_string_cat_lcstr(str, len, buf);
            
            ohcp_string_destroy(basestr);
        }
        str = ohcp_string_cat_cstr(str, "]");
    }
    
    return str;
}

ohcp_string* ohcp_type_dump(/* ref */ const ohcp_type* type)
{
    ohcp_string* str;
    
    if (type == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'type\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->typetype > OHCP_TYPETYPE_STRUCT) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): typetype (%d) is not in valid range",
            __func__, type->typetype);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (type->typetype == OHCP_TYPETYPE_ATOMIC) {
        ohcp_typedescr_atomic*  descr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_atomic*) type->descr;
        
        ret = snprintf(buf, sizeof(buf), "@%p {%s:\"%s\"}", (void*) type,
            ohcp_string_cstr(descr->name), ohcp_string_cstr(descr->literal_list));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        str = ohcp_string_create_lcstr(len, buf);
    } else if (type->typetype == OHCP_TYPETYPE_VECTOR) {
        ohcp_typedescr_vector*  descr;
        ohcp_string*            basestr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_vector*) type->descr;
        basestr = ohcp_type_to_str(descr->base);
        
        ret = snprintf(buf, sizeof(buf), "@%p [%lu %s]", (void*) type,
            descr->size, ohcp_string_cstr(basestr));
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_string_destroy(basestr);
        
        str = ohcp_string_create_lcstr(len, buf);
    } else {
        ohcp_typedescr_struct*   descr;
        char                    buf   [1024];
        int                     ret;
        size_t                  len;
        
        descr = (ohcp_typedescr_struct*) type->descr;
        
        ret = snprintf(buf, sizeof(buf), "@%p [", (void*) type);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        str = ohcp_string_create_lcstr(len, buf);
        for (const ohcp_deque_entry* de = ohcp_deque_first(descr->field_list) ; de != NULL ; de = de->next) {
            const ohcp_struct_field* field;
            ohcp_string* basestr;
            
            field = (ohcp_struct_field*) de->data;
            basestr = ohcp_type_to_str(field->base);
            
            ret = snprintf(buf, sizeof(buf), de->next == NULL ? "%s %s" : "%s %s,",
                ohcp_string_cstr(basestr), ohcp_string_cstr(field->name));
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            str = ohcp_string_cat_lcstr(str, len, buf);
            
            ohcp_string_destroy(basestr);
        }
        str = ohcp_string_cat_cstr(str, "]");
    }
    
    return str;
}

ohcp_typedescr_atomic* ohcp_typedescr_atomic_create(
    /* move */ const ohcp_string* name, /* move */ const ohcp_string* literal_list
){
    ohcp_typedescr_atomic* descr;
    
    if (name == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'name\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (name->len == 0) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): name cannot be an empty string", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (literal_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): Argument \'literal_list\' is NULL", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (literal_list->len == 0) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): literal_list cannot be an empty string", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        descr = malloc(sizeof(ohcp_typedescr_atomic));
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc ohcp_typedescr_atomic", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        descr->name = name;
        descr->literal_list = literal_list;
        
        return descr;
    } while (0);
    
    return NULL;
}

void ohcp_typedescr_atomic_destroy(/* move */ const ohcp_typedescr_atomic* descr_atomic)
{
    if (descr_atomic != NULL) {
        ohcp_string_destroy(descr_atomic->name);
        ohcp_string_destroy(descr_atomic->literal_list);
    }
    
    free((void*) descr_atomic);
}

ohcp_typedescr_vector* ohcp_typedescr_vector_create(size_t size, /* ref */ const ohcp_type* base)
{
    ohcp_typedescr_vector* descr;
    
    if (size == 0) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): Vector cannot have zero size", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (base == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'base\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    // search and optimize
    
    do {
        descr = malloc(sizeof(ohcp_typedescr_vector));
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc ohcp_typedescr_vector", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        descr->size = size;
        descr->base = base;
        
        return descr;
    } while (0);
    
    return NULL;
}

void ohcp_typedescr_vector_destroy(/* ref */ const ohcp_typedescr_vector* descr_vector)
{
    free((void*) descr_vector);
}

ohcp_struct_field* ohcp_struct_field_create(/* move */ const ohcp_string* name, /* ref */ const ohcp_type* base)
{
    ohcp_struct_field* field;
    
    if (name == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'name\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (name->len == 0) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): Tuple field identifier cannot be empty", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (base == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'base\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    do {
        field = malloc(sizeof(ohcp_struct_field));
        if (field == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc ohcp_struct_field", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        field->name = name;
        field->base = base;
        
        return field;
    } while (0);
    
    return NULL;
}

void ohcp_tuple_field_destroy(/* move */ const ohcp_struct_field* field)
{
    if (field != NULL) {
        ohcp_string_destroy(field->name);
    }
    
    free((void*) field);
}

ohcp_typedescr_struct* ohcp_typedescr_struct_create(
    /* move */ const ohcp_string* name, /* move */ ohcp_deque* field_list
){
    ohcp_typedescr_struct* descr;
    
    if (name == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'name\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    if (field_list == NULL) {
        char    buf [1024];
        int     ret;
        size_t  len;
        
        ret = snprintf(buf, sizeof(buf), "%s(): \'field_list\' is null", __func__);
        len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
        
        return NULL;
    }
    
    // if (ohcp_deque_is_empty(field_list)) {
    //     
    // }
    
    do {
        descr = malloc(sizeof(ohcp_typedescr_struct));
        if (descr == NULL) {
            char    buf [1024];
            int     ret;
            size_t  len;
            
            ret = snprintf(buf, sizeof(buf), "%s(): Failed to malloc ohcp_typedescr_struct", __func__);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        descr->name = name;
        descr->field_list = field_list;
        
        return descr;
    } while (0);
    
    return NULL;
}

void ohcp_typedescr_struct_destroy(/* move */ const ohcp_typedescr_struct* descr_tuple)
{
    if (descr_tuple != NULL) {
        ohcp_string_destroy(descr_tuple->name);
        
        for (const ohcp_deque_entry* de = ohcp_deque_first(descr_tuple->field_list) ; de != NULL ; de = de->next) {
            ohcp_tuple_field_destroy((ohcp_struct_field*) de->data);
        }
        
        ohcp_deque_destroy(descr_tuple->field_list);
    }
    
    free((void*) descr_tuple);
}

int ohcp_typelist_init()
{
    do {
        type_list = ohcp_deque_create();
        if (type_list == NULL) {
            break;
        }
        
        do {
            atomic_list = ohcp_deque_create();
            if (atomic_list == NULL) {
                break;
            }
            
            do {
                vector_list = ohcp_deque_create();
                if (vector_list == NULL) {
                    break;
                }
                
                do {
                    tuple_list = ohcp_deque_create();
                    if (tuple_list == NULL) {
                        break;
                    }
                    
                    return 0;
                } while (0);
                
                ohcp_deque_destroy(vector_list);
            } while (0);
            
            ohcp_deque_destroy(atomic_list);
        } while (0);
        
        ohcp_deque_destroy(type_list);
    } while (0);
    
    return -1;
}

void ohcp_typelist_cleanup()
{
    ohcp_deque_destroy(tuple_list);
    ohcp_deque_destroy(vector_list);
    ohcp_deque_destroy(atomic_list);
    
    if (type_list != NULL) {
        for (const ohcp_deque_entry* de = ohcp_deque_first(type_list) ; de != NULL ; de = de->next) {
            ohcp_type_destroy((ohcp_type*) de->data);
        }
    }
    ohcp_deque_destroy(type_list);
}

const ohcp_deque_entry* ohcp_typelist_first()
{
    return type_list->first;
}
