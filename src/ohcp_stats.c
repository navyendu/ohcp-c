// File: ohcp_stats.c

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "ohcp_deque.h"
#include "ohcp_stats.h"

ohcp_string* ohcp_severity_to_str(ohcp_severity sev)
{
    const char* cstr;
    
    switch (sev) {
        case OHCP_SEV_DEBUG:
            cstr = "[ D ]";
            break;
        case OHCP_SEV_INFO:
            cstr = "[ I ]";
            break;
        case OHCP_SEV_WARN:
            cstr = "[ W ]";
            break;
        case OHCP_SEV_ERROR:
            cstr = "[ E ]";
            break;
        case OHCP_SEV_FATAL:
            cstr = "[ F ]";
            break;
        default:
            cstr = "[ ? ]";
            break;
    }
    
    return ohcp_string_create_cstr(cstr);
}

// ohcp_stats_entry --------------------------------------------------------- //

ohcp_stats_entry* ohcp_stats_entry_create(ohcp_severity sev, /* move */ const ohcp_string* msg)
{
    ohcp_stats_entry* se;
    
    if (sev > 4) {
        return NULL;
    }
    
    if (msg == NULL) {
        return NULL;
    }
    
    do {
        se = malloc(sizeof(ohcp_stats_entry));
        if (se == NULL) {
            break;
        }
        
        se->sev = sev;
        se->msg = msg;
        
        return se;
    } while (0);
    
    return NULL;
}

void ohcp_stats_entry_destroy(/* move */ const ohcp_stats_entry* se)
{
    if (se != NULL) {
        ohcp_string_destroy(se->msg);
    }
    
    free((void*) se);
}

// Using int for portability
int ohcp_stats_entry_sev(/* ref */ const ohcp_stats_entry* se)
{
    if (se == NULL) {
        return -1;
    }
    
    return se->sev;
}

const ohcp_string* ohcp_stats_entry_msg(/* ref */ const ohcp_stats_entry* se)
{
    if (se == NULL) {
        return NULL;
    }
    
    return se->msg;
}

// ohcp_stats --------------------------------------------------------------- //

static ohcp_deque* stats_deque;

int ohcp_stats_init(void)
{
    do {
        stats_deque = ohcp_deque_create();
        if (stats_deque == NULL) {
            break;
        }
        
        return 0;
    } while (0);
    
    return -1;
}

void ohcp_stats_cleanup(void)
{
    while (!ohcp_deque_is_empty(stats_deque)) {
        const ohcp_stats_entry* se;
        
        se = ohcp_deque_pop_front(stats_deque);
        
        ohcp_stats_entry_destroy(se);
    }
    
    ohcp_deque_destroy(stats_deque);
}

int ohcp_stats_push_back(enum ohcp_severity sev, /* move */ const ohcp_string* msg)
{
    ohcp_stats_entry*   se;
    int                 ret;
    
    assert(stats_deque != NULL);
    if (stats_deque == NULL) {
        return -1;
    }
    
    do {
        se = ohcp_stats_entry_create(sev, msg);
        if (se == NULL) {
            break;
        }
        
        do {
            ret = ohcp_deque_push_back(stats_deque, se);
            if (ret != 0) {
                break;
            }
            
            return 0;
        } while (0);
        
        ohcp_stats_entry_destroy(se);
    } while (0);
    
    return -2;
}

const ohcp_deque_entry* ohcp_stats_first(void)
{
    if (stats_deque == NULL) {
        return NULL;
    }
    
    return stats_deque->first;
}
