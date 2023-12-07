#include <bits/stdc++.h>
#include <unistd.h>
#include "checker_sqlite.h"
#include "reducer_sqlite.h"
#include "afl-fuzz.h"
#ifndef LOG_DIFF
#define LOG_DIFF
#endif
using namespace std;

vector<pair<string, int> >lines;
vector<string>res;
vector<bool>rem;
list<int>sel;

int cnt_res;
string str, zSql;

static bool isSelect(string stmt){
    for(auto & x : stmt)
    if(islower(x))x = x - 'a' + 'A';
    if(stmt.find("SELECT") == string::npos)return false;
    return stmt.find("SELECT") < 3 && stmt.rfind(";") > stmt.size() - 3;
}

// simplify the test case
void reducer(char** argv, std::vector<stmtstr_with_info> new_sqls, const char* resultpath){
    // init
    res.clear();
    sel.clear();
    lines.clear();
    cnt_res = 0;
    lines.push_back(make_pair(".output sqlresult", 2));
    for(auto & x : new_sqls){
        if(x.stmt_type == STMT_TYPE_SELECT) {
            sel.push_back(lines.size());
            lines.push_back(make_pair(x.stmt_str, 1));
        }
        else lines.push_back(make_pair(x.stmt_str, 0));
    }
    int cnt = lines.size();
    for(auto & x : sel){
        // init remove flag
        rem.clear();
        rem.resize(cnt);
        for(int i = 0; i < cnt; i++){
            if(lines[i].second == 1)
                rem[i] = (i != x);
            else
                rem[i] = false;
        }

        str.clear();
        for(int j = 0; j < cnt; j++)
        if(!rem[j])str = str + lines[j].first + "\n";
        write_to_testcase((void*)str.c_str(), str.size());
        u8 fault = run_target(argv, 10 * 1000);
        // fail to trigger bug
        if(fault == FAULT_ERROR || fault == FAULT_TMOUT || !compare_sqlresult(resultpath))
            continue;
        for(int i = 0; i < cnt; i++) {
            if(lines[i].second)continue;
            rem[i] = true; // try to remove a non-select statement
            str.clear();
            for(int j = 0; j < cnt; j++)
            if(!rem[j])str = str + lines[j].first + "\n";
            write_to_testcase((void*)str.c_str(), str.size());
            fault = run_target(argv, 10* 1000);
            if(fault == FAULT_ERROR || fault == FAULT_TMOUT || !compare_sqlresult(resultpath)){
                rem[i] = false; // statement cann't be revmoed
                continue;
            }
        }
        string save;
        for(int i = 1; i < cnt; i++){
            if(!rem[i])save = save + lines[i].first + "\n";
        }
#ifdef LOG_DIFF
        zSql.clear();
        for(int i = 0; i < cnt; i++){
            if(!rem[i])
            zSql = zSql + lines[i].first + "\n";
        }
        write_to_testcase((void*)zSql.c_str(), zSql.size());
        fault = run_target(argv, 10 * 1000);
        // final confirm & write log
        int id;
        if(fault == FAULT_ERROR || fault == FAULT_TMOUT || !(id = compare_sqlresult(resultpath)))continue;
        save = save + "\n\n/*\n[Log]: diff between 1 and " + to_string(id) + ":\n";
        save = save + getFirstResult() + "\n----------------\n";
        save = save + getSecondResult() + "\n----------------\n";
        zSql.clear();
        for(int i = 0; i < cnt; i++){
            if(!rem[i]){
                if(i == x)zSql = zSql + "explain query plan ";
                zSql = zSql + lines[i].first + "\n";
            }
        }
        save = save + "[Log]: the query plans:\n";
        write_to_testcase((void*)zSql.c_str(), zSql.size());
        fault = run_target(argv, 10 * 1000);
        vector<string>plan = getQueryPlan(resultpath);
        if(plan.size() < id){
            save = save + "There may be errors generating query plans.";
        }
        else{
            save = save + plan[0] + "\n----------------\n";
            save = save + plan[id-1] + "\n----------------\n";
        }
        save = save + "*/";
#endif
        res.push_back(save);
    }
    // if(res.empty()){
    //     printf("%s\n", (void*)mem);
    //     assert(0); // not empty
    // }
}

void* get_reduced_testcase(){
    if(cnt_res >= res.size()){
        res.clear();
        return NULL;
    }
    return (void*)(res[cnt_res++].c_str());
}

int get_reduced_length(){
    if(cnt_res >= res.size()){
        res.clear();
        return -1;
    }
    return res[cnt_res].size();
}
