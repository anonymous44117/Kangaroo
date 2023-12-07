#ifndef _FILTER_H_
#define _FILTER_H_
#include <string>
#include "types.h"
typedef enum Notbug
{
    NB_UNKNOWN,                 /* unknown, maybe it's a bug */
    NB_BARE_COLUMN,				/* bare column */
    NB_DISTINCT,                /* DISTINCT keyword */
    NB_JSON,                    /* json extension */
    NB_LOAD_EXTENSION,          /* load extension */
    NB_WINDOW_FUNCTION,         /* WINDOW FUNCTIONS including:     */
                                /* row_number, rank, dense_rank,   */
                                /* percent_rank, cume_dist, ntile, */
                                /* lag, lead, first_value,         */
                                /* last_value, nth_value           */
    NB_AGGREGATE,               /* aggregate functions, may cause  */
                                /* bare column                     */
    NB_PRECISION,               /* precision error, integer overflow */
    NB_LEFT_JOIN,               /* left (outer) join */
    NB_MULTI_AGGREGATE,          /* multi aggregate  */
    NB_MATCH,
    NB_RANDOM,
    NB_GROUP_BY,
    NB_BOUND,
    NB_RTREE
} Notbug;

const std::string NotbugName[] = {
    "unknown",
    "bare_column",
    "distinct",
    "json",
    "load_extension",
    "window_function",
    "aggregate_function",
    "precision_error",
    "left_join",
    "multi_aggregate",
    "match",
    "random",
    "group_by",
    "overflow_bound",
    "rtree"
};

extern Notbug filter(char** argv, void* mem, unsigned int len, const char* path);
extern const char* getNotbugTypeName(Notbug notbug);
#endif
