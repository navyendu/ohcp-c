// File: ohcp_deque.h

#ifndef OHCP_DEQUE_H
#define OHCP_DEQUE_H

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ohcp_deque_entry ohcp_deque_entry;
struct ohcp_deque_entry
{
    const void*         data;
    
    ohcp_deque_entry*   prev;
    ohcp_deque_entry*   next;
};

/* move */ ohcp_deque_entry*    ohcp_deque_entry_create     (/* move */ const void* data);
/* move */ const void*          ohcp_deque_entry_destroy    (/* move */ const ohcp_deque_entry* de);

/* ref */ const void*           ohcp_deque_entry_data       (/* ref */ const ohcp_deque_entry* entry);
/* ref */ ohcp_deque_entry*     ohcp_deque_entry_prev       (/* ref */ const ohcp_deque_entry* entry);
/* ref */ ohcp_deque_entry*     ohcp_deque_entry_next       (/* ref */ const ohcp_deque_entry* entry);

// ---- //

typedef struct ohcp_deque ohcp_deque;
struct ohcp_deque
{
    size_t              size;
    ohcp_deque_entry*   first;
    ohcp_deque_entry*   last;
};

/* move */ ohcp_deque*          ohcp_deque_create       ();
void                            ohcp_deque_destroy      (/* move */ ohcp_deque* deque);

int                             ohcp_deque_push_front   (/* ref */ ohcp_deque* deque, /* move */ const void* data);
int                             ohcp_deque_push_back    (/* ref */ ohcp_deque* deque, /* move */ const void* data);
/* move */ const void*          ohcp_deque_pop_front    (/* ref */ ohcp_deque* deque);
/* move */ const void*          ohcp_deque_pop_back     (/* ref */ ohcp_deque* deque);

/* ref */ ohcp_deque_entry*     ohcp_deque_first        (/* ref */ const ohcp_deque* deque);
/* ref */ ohcp_deque_entry*     ohcp_deque_last         (/* ref */ const ohcp_deque* deque);

bool                            ohcp_deque_is_empty     (/* ref */ const ohcp_deque* deque);

#ifdef __cplusplus
}
#endif

#endif
