#ifndef _AFL_FUZZ_H
#define _AFL_FUZZ_H

#include "types.h"

    void write_to_testcase(void* mem, u32 len);
    u8 run_target(char** argv, u32 timeout, int exec_type);
    /* Execution status fault codes */
    enum {
    /* 00 */ FAULT_NONE,
    /* 01 */ FAULT_TMOUT,
    /* 02 */ FAULT_CRASH,
    /* 03 */ FAULT_LOGIC,
    /* 04 */ FAULT_MLOGIC,
    /* 05 */ FAULT_ERROR,
    /* 06 */ FAULT_NOINST,
    /* 07 */ FAULT_NOBITS
    };
#endif