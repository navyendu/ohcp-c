// File: ohcp_stats.h

#ifndef OHCP_STATS_H
#define OHCP_STATS_H

#include <stddef.h>

#include "ohcp_string.h"
#include "ohcp_deque.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ohcp_severity
{
    OHCP_SEV_DEBUG = 0,
    OHCP_SEV_INFO  = 1,
    OHCP_SEV_WARN  = 2,
    OHCP_SEV_ERROR = 3,
    OHCP_SEV_FATAL = 4
};
typedef enum ohcp_severity ohcp_severity;

ohcp_string*            ohcp_severity_to_str        (ohcp_severity sev);

// ---- //

typedef struct ohcp_stats_entry ohcp_stats_entry;
struct ohcp_stats_entry
{
    ohcp_severity       sev;
    const ohcp_string*  msg;
};

ohcp_stats_entry*       ohcp_stats_entry_create     (ohcp_severity sev, const ohcp_string* msg);
void                    ohcp_stats_entry_destroy    (const ohcp_stats_entry* se);

int                     ohcp_stats_entry_sev        (const ohcp_stats_entry* entry);
const ohcp_string*      ohcp_stats_entry_msg        (const ohcp_stats_entry* entry);

// ---- //

int                     ohcp_stats_init             (void);
void                    ohcp_stats_cleanup          (void);

int                     ohcp_stats_push_back        (ohcp_severity sev, const ohcp_string* msg);
const ohcp_deque_entry* ohcp_stats_first            (void);

#ifdef __cplusplus
}
#endif

#endif
