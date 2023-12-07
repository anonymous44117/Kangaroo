#include <bits/stdc++.h>
#include <unistd.h>
#include "checker_sqlite.h"
#include "filter_sqlite.h"
#include "afl-fuzz.h"
using namespace std;

string buf;

bool checkBareColumn(){
    return false;
}

bool checkJson(){
    string str = buf;
    for(auto & x : str)
        if(isupper(x))x = x - 'A' + 'a';
    if(str.find("json") != string::npos)return true;
    return false;
}


bool checkBound(){
    string str = buf;
    if(str.find("9223372036854775807") != string::npos)return true;
    return false;
}

bool checkLoadExtension(){
    string str = buf;
    for(auto & x : str)
        if(isupper(x))x = x - 'A' + 'a';
    if(str.find("load_extension") != string::npos)return true;
    return false;
}

bool checkRandom(){
    string str = buf;
    for(auto & x : str)
        if(isupper(x))x = x - 'A' + 'a';
    if(str.find("random") != string::npos)return true;
    return false;
}

bool checkLeftJoin(){
    string str = buf;
    for(auto & x : str)
        if(islower(x))x = x - 'a' + 'A';
    if(str.find("LEFT JOIN") != string::npos)return true;    
    if(str.find("LEFT OUTER JOIN") != string::npos)return true;
    return false;
}

const char *window_function_list[] = {"row_number", "rank", "dense_rank",   \
                                       "percent_rank", "cume_dist", "ntile", \
                                       "lag", "lead", "first_value",         \
                                       "last_value", "nth_value"
                                      };
const char *aggregate_function_list[] = {"avg", "count", "group_concat",    \
                                          "max", "min", "sum", "total"
                                         };
bool checkWindowFunction(){
    string str = buf;
    for(auto & x : str)
        if(isupper(x))x = x - 'A' + 'a';
    for(int i = 0; i<sizeof(window_function_list)/sizeof(const char *); i++){
        if(str.find(window_function_list[i]) != string::npos && str.find(" over ") != string::npos)
            return true;
    }
    return false;
}

bool checkAggregate(){
    string str = buf;
    for(auto & x : str)
        if(isupper(x))x = x - 'A' + 'a';
    for(int i = 0; i<sizeof(aggregate_function_list)/sizeof(const char *); i++){
        if(str.find(aggregate_function_list[i]) != string::npos)return true;
    }
    return false;
}

bool checkPrecision(char** argv, void* mem, u32 len, const char* path){
    bool ret = false;
    write_to_testcase(mem, len);
    u8 fault = run_target(argv, 5000);
    if(fault == FAULT_ERROR || fault == FAULT_TMOUT)ret = false;
    ifstream fp(path);
    string str;
    // int infLoop = 0;
    while(getline(fp, str)){
        // assert(++infLoop < 1000000);
        if(str.find("integer overflow") != string::npos)ret = true;
    }
    return ret;
}

bool checkDistinct(char** argv, void* mem, u32 len, const char* path) {
    string str = buf;
    bool flag = false;
    while(str.find("DISTINCT") != string::npos){
        str.replace(str.find("DISTINCT"), strlen("DISTINCT"), "");
        flag = true;
    }
    while(str.find("distinct") != string::npos){
        str.replace(str.find("distinct"), strlen("distinct"), "");
        flag = true;
    }
    if(!flag)return false; // no DISTINCT keyword
    u8 fault;
    // run once with origin
    write_to_testcase((void*)buf.c_str(), buf.size());
    fault = run_target(argv, 5000);
    if(fault == FAULT_ERROR || fault == FAULT_TMOUT)return false;
    bool first = compare_sqlresult(path);
    // run again with modified
    write_to_testcase((void*)str.c_str(), str.size());
    fault = run_target(argv, 5000);
    if(fault == FAULT_ERROR || fault == FAULT_TMOUT)return false;
    bool second = compare_sqlresult(path);
    return first == true && second == false;
}

bool checkMultiAggregate(char** argv, void* mem, u32 len, const char* path){
    bool ret = false;
    write_to_testcase(mem, len);
    u8 fault = run_target(argv, 5000);
    if(fault == FAULT_ERROR || fault == FAULT_TMOUT)return false;
    ifstream fp(path);
    string str;
    while(getline(fp, str)){
        if(str.find("a GROUP BY clause is required before HAVING") != string::npos)ret = true;
    }
    remove(path);
    return ret;
}

bool checkMatch(char** argv, void* mem, u32 len, const char* path){
    bool ret = false;
    write_to_testcase(mem, len);
    u8 fault = run_target(argv, 5000);
    if(fault == FAULT_ERROR || fault == FAULT_TMOUT)return false;
    ifstream fp(path);
    string str;
    while(getline(fp, str)){
        if(str.find("unable to use function MATCH in the requested context") != string::npos)ret = true;
    }
    remove(path);
    return ret;
}

bool checkGroupBy(){
    string str = buf;
    for(auto & x : str)
        if(islower(x))x = x - 'a' + 'A';
    if(str.find("GROUP BY") != string::npos)return true;
    return false;
}

bool checkRtree(){
    string str = buf;
    int pos, len;
    // in case of \r\n
    pos = str.find("[Log]: diff between");
    if(pos == string::npos)return false;
    pos = str.find("\n", pos) + 1;
    if(pos == string::npos)return false;
    len = str.find("----------------", pos);
    if(len == string::npos)return false;
    len -= pos;
    string res1 = str.substr(pos, len);
    while((pos = res1.find(".0")) != string::npos)
    res1.replace(pos, 2, "");
    // in case of \r\n
    pos = str.find("----------------");
    if(pos == string::npos)return false;
    pos = str.find("\n", pos) + 1;
    if(pos == string::npos)return false;
    len = str.find("----------------", pos);
    if(len == string::npos)return false;
    len -= pos;
    string res2 = str.substr(pos, len);
    while((pos = res2.find(".0")) != string::npos)
    res2.replace(pos, 2, "");
    if(res1 == res2)return true;
    return false;
}

const char* getNotbugTypeName(Notbug notbug){
    return NotbugName[notbug].c_str();
}

// return not-bug type, return NULL if it's not considered as a non-bug stmt
Notbug filter(char** argv, void* mem, unsigned int len, const char* path){
    buf = string((char*)mem);
    // assert(buf.size() == len || buf.size() == len-1);
    Notbug rc = NB_UNKNOWN;
    if(checkBareColumn()){
        rc = NB_BARE_COLUMN;
        goto label;
    }
    // if(checkBound()){
    //     rc = NB_BOUND;
    //     goto label;
    // }
    if(checkJson()){
        rc = NB_JSON;
        goto label;
    }
    if(checkLoadExtension()){
        rc = NB_LOAD_EXTENSION;
        goto label;
    }
    if(checkRandom()){
        rc = NB_RANDOM;
        goto label;
    }
    if(checkMatch(argv, mem, len, path)){
        rc = NB_MATCH;
        goto label;
    }
    if(checkGroupBy()){
        rc = NB_GROUP_BY;
        goto label;
    }
    if(checkWindowFunction()){
        rc = NB_WINDOW_FUNCTION;
        goto label;
    }
    if(checkAggregate()){
        rc = NB_AGGREGATE;
        goto label;
    }
    if(checkRtree()){
        rc = NB_RTREE;
        goto label;
    }
    if(checkPrecision(argv, mem, len, path)){
        rc = NB_PRECISION;
        goto label; 
    }
    if(checkDistinct(argv, mem, len, path)){
        rc = NB_DISTINCT;
        goto label;
    }
    if(checkMultiAggregate(argv, mem, len, path)){
        rc = NB_MULTI_AGGREGATE;
        goto label;
    }
    if(checkLeftJoin()){
        rc = NB_LEFT_JOIN;
        goto label;
    }

    label:
    return rc;
}
