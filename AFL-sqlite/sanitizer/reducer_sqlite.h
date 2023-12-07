#ifndef _REDUCER_H_
#define _REDUCER_H_
#include <fcntl.h>
#include "types.h"
#include "afl-fuzz.h"

extern void reducer(char** argv, std::vector<stmtstr_with_info> new_sqls, const char* path);
extern void * get_reduced_testcase();
extern int get_reduced_length();

#endif