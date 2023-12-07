#ifndef _MYSQL_CUS_CLIENT_H_
#define _MYSQL_CUS_CLIENT_H_

#include "log.h"
#include "new_mutate.h"

#define MULTI_PLAN      // Switch on/off multi-plan execution for client

enum SQLSTATUS {
    kNormal,
    kConnectFailed,
    KSetThreadIDFailed,
    kServerCrash,
    kOutofSync,
    kExecuteError,
    kTimeout,
    kLogicBug,
    kMayLogicBug,
};

struct MYSQL;

class MysqlClient {
public:
    MysqlClient(const char *host, char *user_name, char *passwd, unsigned int *server_pid):host_(host), user_name_(user_name), passwd_(passwd), m_(NULL), server_pid_(server_pid), syn_err_all_num(0), sem_err_all_num(0), total_all_num(0){
        for(int i=0; i<STMT_TYPE_MAX; i++) {
            syntax_err_num[i]=0;
            semantic_err_num[i]=0;
            stmt_num[i]=0;
        }
        log.log_server_init("clientlog", LOG_LEVEL_DEBUG);  // miss log init fail check
    };

    bool connect();
    void disconnect();
    bool check_connect();   // return TRUE when connection is alive

    bool setup_thread_id();
    void reset_thread_id();

    // void process_result(MYSQL_RES *result);
    SQLSTATUS err_statistics(unsigned int err_no, stmt_type_t stype);
    SQLSTATUS clean_up_connection(stmt_type_t stype);
    bool reset_database();
    bool check_server_alive();

    SQLSTATUS execute(std::vector<stmtstr_with_info> &new_sqls);
    SQLSTATUS prepare_execution();
    SQLSTATUS do_one_exeucute(stmtstr_with_info &stmt);

#ifdef MULTI_PLAN
    SQLSTATUS execute_multiplan(std::vector<stmtstr_with_info> &new_sqls);
    SQLSTATUS mysql_real_query_multi(MYSQL *mysql, stmtstr_with_info &stmt, int& plan_numbers);
#endif

    LogServer log;
    unsigned long int syntax_err_num[STMT_TYPE_MAX];
    unsigned long int semantic_err_num[STMT_TYPE_MAX];
    unsigned long int stmt_num[STMT_TYPE_MAX];  // stmt_num - syntax_err_num - semantic_err_num == correct_num
    unsigned long int plan_one_num;
    unsigned long int syn_err_all_num;
    unsigned long int sem_err_all_num;
    unsigned long int total_all_num;            // total_all_num = stmt_num[0] + stmt_num[1] + ... + stmt_num[STMT_TYPE_MAX-1]

private:
    MYSQL *m_;
    const char * host_;
    char * user_name_;
    char * passwd_;
    unsigned int *server_pid_;
};

#endif