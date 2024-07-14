// File: ohcp_module.h

#ifndef OHCP_MODULE_H
#define OHCP_MODULE_H

#include "ohcp_string.h"
#include "ohcp_forward.h"
#include "ohcp_port.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (* ohcp_module_build_fptr_t) (/* ref */ ohcp_module* m);

typedef struct ohcp_module_descr    ohcp_module_descr;
struct ohcp_module_descr
{
    const ohcp_string* name;
    void* priv;
    
    ohcp_module_build_fptr_t build;
};

/* move */ ohcp_module_descr*   ohcp_module_descr_create    (/* move */ const ohcp_string* name,
                                                             /* ref */ void* priv, ohcp_module_build_fptr_t buildfn);
void                            ohcp_module_descr_destroy   (/* move */ ohcp_module_descr* md);

/* move */ ohcp_string*         ohcp_module_descr_dump      (/* ref */ const ohcp_module_descr* md);

struct ohcp_module
{
    const ohcp_module_descr* descr;
    
    const ohcp_string* name;
    
    ohcp_module* parent;
    
    ohcp_deque* node_list;
    ohcp_deque* expr_list;
    ohcp_deque* child_list;
    
    void* ipriv;
    
    void* ext;
};

/* move */ ohcp_module* ohcp_module_create          (/* ref */ ohcp_module* parent,
                                                     /* ref */ const ohcp_module_descr* descr,
                                                     /* move */ const ohcp_string* name,
                                                     /* ref */ void* ipriv);
void                    ohcp_module_destroy         (const ohcp_module* m);

int                     ohcp_module_add_node        (/* ref */ ohcp_module* m, /* move */ ohcp_node* node);
int                     ohcp_module_add_expr        (/* ref */ ohcp_module* m, /* move */ ohcp_expr* expr);
int                     ohcp_module_add_child       (/* ref */ ohcp_module* m, /* move */ ohcp_module* child);

/* ref */ ohcp_node*    ohcp_module_create_node     (/* ref */ ohcp_module* m, /* ref */ const ohcp_type* type,
                                                     /* move */ const ohcp_string* name);
/* ref */ ohcp_node*    ohcp_module_create_port     (/* ref */ ohcp_module* m, /* ref */ const ohcp_type* t,
                                                     enum ohcp_port_dir dir, /* move */ const ohcp_string* name);

int                     ohcp_module_assign          (/* ref */ ohcp_module* m, /* ref */ ohcp_node* node,
                                                     /* move */ ohcp_node* node0);

/* move */ ohcp_string* ohcp_module_full_name       (/* ref */ const ohcp_module* m, /* ref */ const ohcp_node* node);
/* move */ ohcp_string* ohcp_module_debug_str       (/* ref */ const ohcp_module* m, /* ref */ const ohcp_string* indent);

#ifdef __cplusplus
}
#endif

#endif
