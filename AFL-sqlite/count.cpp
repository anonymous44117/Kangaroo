#include <bits/stdc++.h>
#include <regex>
#include "count.h"
using namespace std;
#define SQLITE_LINE_LENGTH 1024
char buffer[SQLITE_LINE_LENGTH];

string pre_process(const std::vector<stmtstr_with_info> &new_sqls){
    if(new_sqls.empty()) return "";
    string ret = ".output sqlresult\n";
    int i = 0;
    if(new_sqls[0].stmt_str.find("output sqlresult") != string::npos) i++;
    for(; i < new_sqls.size(); i++){
        ret = ret + new_sqls[i].stmt_str + "\n";
    }
    return ret;
}

void count_success(std::vector<stmtstr_with_info>& v, long& syntax_err_num, long& semantic_err_num, long* correct_stmt_num, long* total_stmt_num, long& correct_all_num, long& total_all_num){
    map<int, bool>mp;
    int pos;
    FILE* f = fopen("test.err", "r");
    if(f == NULL) return;
    // FILE* fd = fopen("debug.txt", "w");
    // fprintf(fd, "%s\n", cmd);
    while(fgets(buffer, SQLITE_LINE_LENGTH - 1, f) != NULL){
        char* pos;
        if((pos = strstr(buffer, (char*)"near line")) != NULL){
    //         fprintf(fd, "%s", buffer);
            int line;
            sscanf(pos, "near line %d:", &line);
            mp[line] = (strstr(buffer, (char*)"syntax") != NULL);
        }
    }
    fclose(f);
    // fclose(fd);
    int sz = v.size();
    for(int i = 0; i < sz; i++){
        total_all_num++;
        total_stmt_num[v[i].stmt_type]++;
        if(!mp.count(i+2)) {
            correct_all_num++;
            correct_stmt_num[v[i].stmt_type]++;
        }
        else if(v[i].stmt_type == STMT_TYPE_SELECT){
            if(mp[i+2]) syntax_err_num++;
            else semantic_err_num++;
        }
    }
}
