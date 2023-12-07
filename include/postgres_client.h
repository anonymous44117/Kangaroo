#ifndef _POSTGRES_CLIENT_H_
#define _POSTGRES_CLIENT_H_

#include "libpq-fe.h"
#include "log.h"
#include "new_mutate.h"

enum SQLSTATUS {
    kNormal = 0,
    kConnectFailed,
    KSetThreadIDFailed,
    kServerCrash,
    kOutofSync,
    kExecuteError,
    kTimeout,
    kLogicBug,
    kMayLogicBug,
};

class PostgresClient {
public:
    PostgresClient(): syn_err_all_num(0), sem_err_all_num(0), total_all_num(0),plan_one_num(0), total_plan_numbers(0) {
        for(int i=0; i<STMT_TYPE_MAX; i++) {
            syntax_err_num[i]=0;
            semantic_err_num[i]=0;
            stmt_num[i]=0;
        }
        if(!log.log_server_init("clientlog", LOG_LEVEL_DEBUG)) {
            printf("Fail to init client log!\n");
            exit(-1);
        }
    }

    PGconn * connect();
    void disconnect(PGconn * conn);
    void reset_database(PGconn* conn);
    bool check_status(PGconn * conn);
    SQLSTATUS execute(std::vector<stmtstr_with_info> &input);
    SQLSTATUS execute_multiplan(std::vector<stmtstr_with_info> &input);

    void count_plan(const char* sql);

    LogServer log;
    unsigned long int syntax_err_num[STMT_TYPE_MAX];
    unsigned long int semantic_err_num[STMT_TYPE_MAX];
    unsigned long int stmt_num[STMT_TYPE_MAX];  // stmt_num - syntax_err_num - semantic_err_num == correct_num
    unsigned long int syn_err_all_num;
    unsigned long int sem_err_all_num;
    unsigned long int total_all_num;            // total_all_num = stmt_num[0] + stmt_num[1] + ... + stmt_num[STMT_TYPE_MAX-1]
    unsigned long int plan_one_num;
    unsigned long int total_plan_numbers;
};

#endif