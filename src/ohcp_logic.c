// File: ohcp_logic.c

#include <stddef.h>

#include "ohcp_deque.h"
#include "ohcp_logic.h"

const struct ohcp_type* ohcp_logic = NULL;

// static unsigned int ohcp_logic_sim_buf(unsigned int a)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES] = {
//         OHCP_LOGIC_0,
//         OHCP_LOGIC_1,
//         OHCP_LOGIC_X,
//         OHCP_LOGIC_X
//     };
    
//     return lookup[a];
// }

// static unsigned int ohcp_logic_sim_inv(unsigned int a)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES] = {
//         OHCP_LOGIC_1,
//         OHCP_LOGIC_0,
//         OHCP_LOGIC_X,
//         OHCP_LOGIC_X
//     };
    
//     return lookup[a];
// }

// static unsigned int ohcp_logic_sim_and(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_0, OHCP_LOGIC_0, OHCP_LOGIC_0, OHCP_LOGIC_0 },
//         { OHCP_LOGIC_0, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int ohcp_logic_sim_or(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_0, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_1, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int ohcp_logic_sim_xor(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_0, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_1, OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int ohcp_logic_sim_eq(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_1, OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_0, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int ohcp_logic_sim_lt(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_0, OHCP_LOGIC_1, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_0, OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int ohcp_logic_sim_gt(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[OHCP_LOGIC_NUM_STATES][OHCP_LOGIC_NUM_STATES] = {
//         { OHCP_LOGIC_0, OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_1, OHCP_LOGIC_0, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X },
//         { OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X, OHCP_LOGIC_X }
//     };
    
//     return lookup[a][b];
// }

// static const struct atomic_sim_ops ops = {
//     .sim_buf = ohcp_logic_sim_buf,
//     .sim_inv = ohcp_logic_sim_inv,
//     .sim_and = ohcp_logic_sim_and,
//     .sim_or  = ohcp_logic_sim_or,
//     .sim_xor = ohcp_logic_sim_xor,
//     .sim_eq  = ohcp_logic_sim_eq,
//     .sim_lt  = ohcp_logic_sim_lt,
//     .sim_gt  = ohcp_logic_sim_gt
// };

static char ohcp_logic_litmap[OHCP_LOGIC_NUM_STATES] = {
    OHCP_LOGIC_0_LIT,
    OHCP_LOGIC_1_LIT,
    OHCP_LOGIC_Z_LIT,
    OHCP_LOGIC_X_LIT
};

int ohcp_logic_init(void)
{
    ohcp_string* name;
    ohcp_string* litmap;
    
    do {
        name = ohcp_string_create_cstr(OHCP_LOGIC_NAME);
        if (name == NULL) {
            break;
        }
        
        do {
            litmap = ohcp_string_create_lcstr(OHCP_LOGIC_NUM_STATES, ohcp_logic_litmap);
            if (litmap == NULL) {
                break;
            }
            
            do {
                ohcp_logic = ohcp_type_create_atomic(name, litmap);
                if (ohcp_logic == NULL) {
                    break;
                }
                
                return 0;
            } while (0);
            
            ohcp_string_destroy(litmap);
        } while (0);
        
        ohcp_string_destroy(name);
    } while (0);
    
    return -1;
}
