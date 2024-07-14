// File: ohcp_bit.c

#include <stddef.h>

#include "ohcp_deque.h"
#include "ohcp_bit.h"

const struct ohcp_type* ohcp_bit = NULL;

// static unsigned int bit_sim_buf(unsigned int a)
// {
//     static const unsigned int lookup[BIT_NUM_STATES] = {
//         BIT_0,
//         BIT_1
//     };
    
//     return lookup[a];
// }

// static unsigned int bit_sim_inv(unsigned int a)
// {
//     static const unsigned int lookup[BIT_NUM_STATES] = {
//         BIT_1,
//         BIT_0
//     };
    
//     return lookup[a];
// }

// static unsigned int bit_sim_and(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_0, BIT_0 },
//         { BIT_0, BIT_1 }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int bit_sim_or(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_0, BIT_1 },
//         { BIT_1, BIT_1 }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int bit_sim_xor(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_0, BIT_1 },
//         { BIT_1, BIT_0 }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int bit_sim_eq(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_1, BIT_0 },
//         { BIT_0, BIT_1 }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int bit_sim_lt(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_0, BIT_1 },
//         { BIT_0, BIT_0 }
//     };
    
//     return lookup[a][b];
// }

// static unsigned int bit_sim_gt(unsigned int a, unsigned int b)
// {
//     static const unsigned int lookup[BIT_NUM_STATES][BIT_NUM_STATES] = {
//         { BIT_0, BIT_0 },
//         { BIT_1, BIT_0 }
//     };
    
//     return lookup[a][b];
// }

// static const struct atomic_sim_ops ops = {
//     .sim_buf = bit_sim_buf,
//     .sim_inv = bit_sim_inv,
//     .sim_and = bit_sim_and,
//     .sim_or  = bit_sim_or,
//     .sim_xor = bit_sim_xor,
//     .sim_eq  = bit_sim_eq,
//     .sim_lt  = bit_sim_lt,
//     .sim_gt  = bit_sim_gt
// };

static char ohcp_bit_litmap [OHCP_BIT_NUM_STATES] = {
    OHCP_BIT_0_LIT,
    OHCP_BIT_1_LIT
};

int bit_init(void)
{
    ohcp_string* name;
    ohcp_string* litmap;
    
    do {
        name = ohcp_string_create_cstr(OHCP_BIT_NAME);
        if (name == NULL) {
            break;
        }
        
        do {
            litmap = ohcp_string_create_lcstr(OHCP_BIT_NUM_STATES, ohcp_bit_litmap);
            if (litmap == NULL) {
                break;
            }
            
            do {
                ohcp_bit = ohcp_type_create_atomic(name, litmap);
                if (ohcp_bit == NULL) {
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
