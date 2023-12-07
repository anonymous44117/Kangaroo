#ifndef _STATEMENT_TYPE_H_
#define _STATEMENT_TYPE_H_

enum stmt_type_t {
    STMT_TYPE_UNKNOW = 0,
    // STMT_TYPE_TOP,
    STMT_TYPE_CREATE,
    STMT_TYPE_CREATE_RELATION,
    STMT_TYPE_CREATE_INDEX,
    STMT_TYPE_INSERT,
    STMT_TYPE_DROP,
    STMT_TYPE_SELECT,
    STMT_TYPE_UPDATE,
    STMT_TYPE_DELETE,
    STMT_TYPE_ALTER,
    STMT_TYPE_MAX,
};

#endif