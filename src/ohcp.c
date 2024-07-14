// File: ohcp.c

#include "ohcp.h"

// static int expr_init()
// {
//     // ohcp_expr_buf_init();
//     // ohcp_expr_vector_init();
    
//     return 0;
// }

int ohcp_init()
{
    int iret;
    
    do {
        iret = ohcp_stats_init();
        if (iret != 0) {
            int     ret;
            size_t  len;
            char    buf [1024];
            
            ret = snprintf(buf, sizeof(buf), "%s(): ohcp_stats_init() returned %d", __func__, iret);
            len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
            
            ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
            
            break;
        }
        
        do {
            iret = ohcp_typelist_init();
            if (iret != 0) {
                int     ret;
                size_t  len;
                char    buf [1024];
                
                ret = snprintf(buf, sizeof(buf), "%s(): ohcp_typelist_init() returned %d", __func__, iret);
                len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                
                ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                
                break;
            }
            
            do {
                iret = ohcp_logic_init();
                if (iret != 0) {
                    int     ret;
                    size_t  len;
                    char    buf [1024];
                    
                    ret = snprintf(buf, sizeof(buf), "%s(): ohcp_typelist_init() returned %d", __func__, iret);
                    len = ret > (int) sizeof(buf) ? sizeof(buf) - 1 : (size_t) ret;
                    
                    ohcp_stats_push_back(OHCP_SEV_FATAL, ohcp_string_create_lcstr(len, buf));
                    
                    break;
                }
                
                // expr_init();
                
                return 0;
            } while (0);
            
            ohcp_typelist_cleanup();
        } while (0);
        
        ohcp_stats_cleanup();
    } while (0);
    
    return -1;
}

void ohcp_cleanup()
{
    // ohcp_expr_vector_cleanup();
    // ohcp_expr_buf_cleanup();
    
    ohcp_typelist_cleanup();
    ohcp_stats_cleanup();
}
