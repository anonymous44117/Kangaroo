#ifndef _COUNT_H_
#define _COUNT_H_

#include <string>
#include <vector>
// #include "../../include/typedef.h"
#include "new_mutate.h"
using std::string;
using std::vector;


string pre_process(const std::vector<stmtstr_with_info>& new_sqls);

void count_success(std::vector<stmtstr_with_info> &new_sqls, long& syntax_err_num, long& semantic_err_num, long* correct_stmt_num, long* total_stmt_num, long& correct_all_num, long& total_all_num);
#endif
