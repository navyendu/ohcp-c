// File: ohcp_deque.c

#include <stdio.h>
#include <stdlib.h>

#include "ohcp_deque.h"

// ohcp_deque_entry ---- //

ohcp_deque_entry* ohcp_deque_entry_create(const void* data)
{
    ohcp_deque_entry* de;
    
    do {
        de = malloc(sizeof(ohcp_deque_entry));
        if (de == NULL) {
            break;
        }
        
        de->data = data;
        de->next = NULL;
        de->prev = NULL;
        
        return de;
    } while (0);
    
    return NULL;
}

const void* ohcp_deque_entry_destroy(const ohcp_deque_entry* de)
{
    const void* data = de->data;
    
    free((void*) de);
    
    return data;
}

const void* ohcp_deque_entry_data(const ohcp_deque_entry* de)
{
    if (de == NULL) {
        return NULL;
    }
    
    return de->data;
}

ohcp_deque_entry* ohcp_deque_entry_prev(const ohcp_deque_entry* de)
{
    if (de == NULL) {
        return NULL;
    }
    
    return de->prev;
}

ohcp_deque_entry* ohcp_deque_entry_next(const ohcp_deque_entry* de)
{
    if (de == NULL) {
        return NULL;
    }
    
    return de->next;
}

// ohcp_deque ---- //

ohcp_deque* ohcp_deque_create()
{
    ohcp_deque* deque;
    
    do {
        deque = malloc(sizeof(ohcp_deque));
        if (deque == NULL) {
            break;
        }
        
        deque->first = NULL;
        deque->last = NULL;
        
        return deque;
    } while (0);
    
    return NULL;
}

void ohcp_deque_destroy(ohcp_deque* deque)
{
    if (deque != NULL) {
        while (!ohcp_deque_is_empty(deque)) {
            ohcp_deque_pop_front(deque);
        }
    }
    
    free((void*) deque);
}

int ohcp_deque_push_front(ohcp_deque* deque, const void* data)
{
    ohcp_deque_entry* de;
    
    if (deque == NULL) {
        return -1;
    }
    
    do {
        de = ohcp_deque_entry_create(data);
        if (de == NULL) {
            break;
        }
        
        de->next = deque->first;
        de->prev = NULL;
        
        if (deque->first == NULL || deque->last == NULL) {
            assert (deque->first == NULL && deque->last == NULL);
            
            deque->first = de;
            deque->last = de;
        } else {
            deque->first->prev = de;
            deque->first = de;
        }
        
        deque->size++;
        
        return 0;
    } while (0);
    
    return -3;
}

int ohcp_deque_push_back(ohcp_deque* deque, const void* data)
{
    ohcp_deque_entry*   de;
    
    if (deque == NULL) {
        return -1;
    }
    
    do {
        de = ohcp_deque_entry_create(data);
        if (de == NULL) {
            break;
        }
        
        de->prev = deque->last;
        de->next = NULL;
        
        if (deque->first == NULL || deque->last == NULL) {
            assert (deque->first == NULL && deque->last == NULL);
            
            deque->first = de;
            deque->last = de;
        } else {
            deque->last->next = de;
            deque->last = de;
        }
        
        deque->size++;
        
        return 0;
    } while (0);
    
    return -3;
}

const void* ohcp_deque_pop_front(ohcp_deque* deque)
{
    ohcp_deque_entry*   de;
    ohcp_deque_entry*   first_next;
    const void*         data;
    
    if (deque == NULL) {
        return NULL;
    }
    
    de = deque->first;
    if (de == NULL) {
        return NULL;
    }
    
    first_next = de->next;
    
    de->next = NULL;
    assert(de->prev == NULL);
    
    if (first_next != NULL) {
        first_next->prev = NULL;
    } else {
        assert(deque->first == deque->last);
    }
    
    deque->first = first_next;
    if (first_next == NULL) {
        deque->last = NULL;
    }
    
    data = ohcp_deque_entry_destroy(de);
    
    deque->size--;
    
    return data;
}

const void* ohcp_deque_pop_back(ohcp_deque* deque)
{
    ohcp_deque_entry*   de;
    ohcp_deque_entry*   last_prev;
    const void*         data;
    
    if (deque == NULL) {
        return NULL;
    }
    
    de = deque->last;
    if (de == NULL) {
        return NULL;
    }
    
    last_prev = de->prev;
    
    de->prev = NULL;
    assert(de->next == NULL);
    
    if (last_prev != NULL) {
        last_prev->next = NULL;
    } else {
        assert(deque->last == deque->first);
    }
    
    deque->last = last_prev;
    if (last_prev == NULL) {
        deque->first = NULL;
    }
    
    data = ohcp_deque_entry_destroy(de);
    
    deque->size--;
    
    return data;
}

ohcp_deque_entry* ohcp_deque_first(const ohcp_deque* deque)
{
    if (deque == NULL) {
        return NULL;
    }
    
    return deque->first;
}

ohcp_deque_entry* ohcp_deque_last(const ohcp_deque* deque)
{
    if (deque == NULL) {
        return NULL;
    }
    
    return deque->last;
}

bool ohcp_deque_is_empty(const ohcp_deque* deque)
{
    if (deque == NULL) {
        return true;
    }
    
    return deque->first == NULL && deque->last == NULL;
}
