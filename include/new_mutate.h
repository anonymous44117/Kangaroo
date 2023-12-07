#ifndef _MUTATE_ENGINE_H_
#define _MUTATE_ENGINE_H_
#include <string>
#include <vector>
#include <set>

#include "statement_type.h"


class global_info;
class root_analyze_visitor;
class SqlStmt;
class ast_root;
class node_library;
class stmtstr_with_info {
public:
    std::string stmt_str;
    stmt_type_t stmt_type;
    uint32_t flag;                  /* record the feature of quries (such as containt sub-queries, has non-determinstic feature */
    uint32_t server_response;
    SqlStmt *parse_tree;            /* origin parse tree for re-mutate if the mutated queries fail to pass check*/
    ast_root *semantic_tree;        /* callback function to update DBMS state */
};

/***************************************/

#define ME_MUTATE_MODE (0x1)
#define ME_RESET_CONTEXT (0x1 << 1)

class mutate_engine {
public:
    bool is_init;
    int statement_max_nodes;
    global_info *g_info;
    root_analyze_visitor *analyze;

    node_library *node_library_;

    mutate_engine(const char *config_path, const char *work_dir);
    ~mutate_engine();

    void set_current_schema(std::string schema);
    void reset_analyze_context();
    std::string * do_one_mutation(const char *sql, bool reset_context, bool need_mutate);
    bool do_one_mutation(const char *sql, std::vector<stmtstr_with_info> &ret, bool reset_context, bool need_mutate);
    std::string * preprocessing(const char *sql);
    stmtstr_with_info * mutate_one_stmt(const char *sql, uint64_t mode);
    stmtstr_with_info * mutate_one_stmt(SqlStmt *root, uint64_t mode);
    void do_update_state(stmtstr_with_info *stmt);
};

#endif