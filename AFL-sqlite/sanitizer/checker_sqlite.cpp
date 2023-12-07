#include <bits/stdc++.h>
#include <fstream>
#include "checker_sqlite.h"
using namespace std;
#ifndef LOG_DIFF
#define LOG_DIFF
#endif

bool errorDiff = false; // if true then error differences will be taken into account
const string ressep = "***********************************************"; // separator between distinct plans
const string endsep = "-----------------------------------------------"; // end of query with exception
const string endstmt = "END OF A STATEMENT"; // end of query
const string erroccr = "ERROR OCCURRED!"; // result when an error occur
const string preproc = "**The above is the pre-processing information**"; // pre-processing
const string noterr = "NO ERROR";
pair<string, string>pr;
int compareWithoutOrder(ifstream &fp){
    string line;
    bool firsterr = false;
    vector<string>v1, v2;
    // first resultset:
    v1.clear();
    while(getline(fp, line) && line != ressep){
        // no exceptions at the end of resultset
        if(line == endstmt || line == endsep)return 0;
        if(line.find(erroccr) != string::npos)firsterr = true;
        v1.push_back(line);
    }
    // if error difference is intended to be ignored but error occurred, return false
    if(!errorDiff && firsterr)return 0;
    sort(v1.begin(), v1.end());
    // subsequent resultset(s):
    bool thiserr = false;
    int cnt = 1;
    while(getline(fp,line)){
        if(line == ressep) {
            cnt++;
            if(firsterr ^ thiserr){
                if(errorDiff){
                    if(firsterr)pr.first = erroccr;
                    else pr.first = noterr;
                    if(thiserr)pr.second = erroccr;
                    else pr.second = noterr;
                    return cnt;
                }
                goto label;
            }
            sort(v2.begin(), v2.end());
            if(v1 != v2){
                string concat;
                for(auto& x : v1)concat = concat + x + "\n";
                //if(concat.size() && concat.back() == '\n')concat.pop_back();
                pr.first = concat;
                concat.clear();
                for(auto& x : v2)concat = concat + x + "\n";
                //if(concat.size() && concat.back() == '\n')concat.pop_back();
                pr.second = concat;
                return cnt;
            }
        label:
            thiserr = false;
            v2.clear();
        } else if(line == endstmt || line == endsep) return 0;
        else{
            thiserr |= (line.find(erroccr) != string::npos);
            v2.push_back(line);
        }
    }
    return 0;
}

const char* getFirstResult(){
    return pr.first.c_str();
}

const char* getSecondResult(){
    return pr.second.c_str();
}

// only return whether it's different, no matter which stmt causes difference
int compare_sqlresult(const char *path){
    string zSql, line;
    ifstream fp(path);
    while(getline(fp, line)){
        if(line.substr(0, strlen("SELECT")) == "SELECT"){
            while(line.size() && line.back() == ' ') line = line.substr(0, line.size()-1);
            zSql = line;
            while(line.size() && line.back() != ';'){
            // && line.find("--") == string::npos){
                if(!getline(fp, line))break;
                while(line.size() && line.back() == ' ') line = line.substr(0, line.size()-1);
                zSql = zSql + "\n" + line;
            }
            if(zSql.size() && zSql.back() == '\n')zSql.pop_back();
            int x = compareWithoutOrder(fp);
            if(x){
                fp.close();
                // ofstream testlog("test.log", ios::app);
                // testlog << "[LOG] diff in " << zSql << " between 1 and " << x << endl;
                // testlog << getFirstResult() << endl;
                // testlog << "******************" << endl;
                // testlog << getSecondResult() << endl;
                // testlog << "END" << endl;
                // testlog.close();
                assert(strcmp(getFirstResult(), getSecondResult()));
                return x;
            }
        }
    }
    fp.close();
    remove(path);
    return 0;
}

static bool isExplainQueryPlan(string stmt){
    for(auto & x : stmt)
    if(islower(x))x = x - 'a' + 'A';
    if(stmt.find("EXPLAIN QUERY PLAN") == string::npos)return false;
    return stmt.find("EXPLAIN QUERY PLAN") < 3 && stmt.rfind(";") > stmt.size() - 3;
}

// make sure execute explain query plan stmt first.
vector<string> getQueryPlan(const char *path){
    vector<string> qp;
    string zSql, str, plan;
    ifstream fp(path);
    zSql.clear();
    while(getline(fp, str)){
        zSql = zSql + str;
        if(isExplainQueryPlan(zSql))break;
    }
    while(getline(fp, str)){
        if(str == ressep){
            if(plan.size() && plan.back() == '\n')plan.pop_back();
            qp.push_back(plan);
            plan.clear();
        }
        else if(str == endsep || str == endstmt)break;
        else plan = plan + str + "\n";
    }
    fp.close();
    return qp;
}
