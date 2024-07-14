// File: ohcp_type.h

#ifndef OHCP_TYPE_H
#define OHCP_TYPE_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include "ohcp_string.h"
#include "ohcp_forward.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ohcp_typetype
{
    OHCP_TYPETYPE_ATOMIC,
    OHCP_TYPETYPE_VECTOR,
    OHCP_TYPETYPE_STRUCT
};
typedef enum ohcp_typetype  ohcp_typetype;

// ---- //

struct ohcp_type
{
    ohcp_typetype       typetype;
    void*               descr;
};

ohcp_type*              ohcp_type_create_atomic (const ohcp_string* name, const ohcp_string* literal_list);
ohcp_type*              ohcp_type_create_vector (size_t size, const ohcp_type* base);
ohcp_type*              ohcp_type_create_struct (const ohcp_string* name, ohcp_deque* field_list);

void                    ohcp_type_destroy       (const ohcp_type* type);

ohcp_string*            ohcp_type_to_str        (const ohcp_type* type);
ohcp_string*            ohcp_type_dump          (const ohcp_type* type);

// ---- //

typedef struct ohcp_typedescr_atomic ohcp_typedescr_atomic;
struct ohcp_typedescr_atomic
{
    const ohcp_string*  name;
    const ohcp_string*  literal_list;
};

ohcp_typedescr_atomic*  ohcp_typedescr_atomic_create    (const ohcp_string* name, const ohcp_string* literal_list);
void                    ohcp_typedescr_atomic_destroy   (const ohcp_typedescr_atomic* da);

// ---- //

typedef struct ohcp_typedescr_vector ohcp_typedescr_vector;
struct ohcp_typedescr_vector
{
    size_t              size;
    const ohcp_type*    base;
};

ohcp_typedescr_vector*  ohcp_typedescr_vector_create    (size_t size, const ohcp_type* base);
void                    ohcp_typedescr_vector_destroy   (const ohcp_typedescr_vector* dv);

// ---- //

typedef struct ohcp_struct_field ohcp_struct_field;
struct ohcp_struct_field
{
    const ohcp_string*  name;
    const ohcp_type*    base;
};

ohcp_struct_field*      ohcp_struct_field_create         (const ohcp_string* name, const ohcp_type* base);
void                    ohcp_struct_field_destroy        (const ohcp_struct_field* field);

typedef struct ohcp_typedescr_struct ohcp_typedescr_struct;
struct ohcp_typedescr_struct
{
    const ohcp_string*  name;
    ohcp_deque*         field_list;
};

ohcp_typedescr_struct*  ohcp_typedescr_struct_create     (const ohcp_string* name, ohcp_deque* field_list);
void                    ohcp_typedescr_struct_destroy    (const ohcp_typedescr_struct* dt);

// ---- //

int                     ohcp_typelist_init              (void);
void                    ohcp_typelist_cleanup           (void);

const ohcp_deque_entry* ohcp_typelist_first             ();

#ifdef __cplusplus
}
#endif

#endif
