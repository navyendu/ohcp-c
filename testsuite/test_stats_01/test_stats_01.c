// File: test_stats_01.c

#include <stdio.h>

#include "ohcp_stats.h"

// fprintf(stderr, "%s:%s():%u\n", __FILE__, __func__, __LINE__);

int main()
{
    int ret = ohcp_stats_init();
    if (ret != 0) {
        fprintf(stderr, "ohcp_stats_init() returned %d", ret);
    }
    
    for (size_t i = 0 ; i < 4 ; i++) {
        char msg [1024];
        int len;
        
        len = snprintf(msg, sizeof(msg), "Message %lu", i);
        len = len > (int) sizeof(msg) ? sizeof(msg) - 1 : (size_t) len;
        
        ohcp_stats_push_back(OHCP_SEV_DEBUG, ohcp_string_create_lcstr(len, msg));
    }
    
    for (size_t i = 0 ; i < 4 ; i++) {
        char msg [1024];
        int len;
        
        len = snprintf(msg, sizeof(msg), "Message %lu", i);
        len = len > (int) sizeof(msg) ? sizeof(msg) - 1 : (size_t) len;
        
        ohcp_stats_push_back(OHCP_SEV_INFO, ohcp_string_create_lcstr(len, msg));
    }
    
    for (size_t i = 0 ; i < 4 ; i++) {
        char msg [1024];
        int len;
        
        len = snprintf(msg, sizeof(msg), "Message %lu", i);
        len = len > (int) sizeof(msg) ? sizeof(msg) - 1 : (size_t) len;
        
        ohcp_stats_push_back(OHCP_SEV_WARN, ohcp_string_create_lcstr(len, msg));
    }
    
    for (size_t i = 0 ; i < 4 ; i++) {
        char            msg [1024];
        int             len;
        
        len = snprintf(msg, sizeof(msg), "Message %lu", i);
        len = len > (int) sizeof(msg) ? sizeof(msg) - 1 : (size_t) len;
        
        ohcp_stats_push_back(OHCP_SEV_ERROR, ohcp_string_create_lcstr(len, msg));
    }
    
    for (size_t i = 0 ; i < 4 ; i++) {
        char msg [1024];
        int len;
        
        len = snprintf(msg, sizeof(msg), "Message %lu", i);
        len = len > (int) sizeof(msg) ? sizeof(msg) - 1 : (size_t) len;
        
        ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, msg));
    }
    
    for (const ohcp_deque_entry* iter = ohcp_stats_first() ; iter != NULL ; iter = iter->next) {
        const ohcp_stats_entry* se;
        const ohcp_string* str;
        
        se = iter->data;
        str = ohcp_severity_to_str(se->sev);
        
        fprintf(stdout, "%s %s\n", ohcp_string_cstr(str), ohcp_string_cstr(se->msg));
        
        ohcp_string_destroy(str);
    }
    
    ohcp_stats_cleanup();
    
    return 0;
}
