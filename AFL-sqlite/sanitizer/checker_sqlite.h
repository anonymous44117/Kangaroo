#ifndef _CHECKER_H_
#define _CHECKER_H_
#include <string>
#include <vector>
#include "types.h"
extern int compare_sqlresult(const char *path);
extern std::vector<std::string> getQueryPlan(const char *path);
const char* getFirstResult();
const char* getSecondResult();
#endif