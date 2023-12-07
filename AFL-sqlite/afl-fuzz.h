#ifndef _AFL_FUZZ_H
#define _AFL_FUZZ_H

#include "types.h"
#include "count.h"
    void write_to_testcase(void* mem, u32 len);
    u8 run_target(char** argv, u32 timeout);
    /* Execution status fault codes */
    void write_to_file(char* dir, char* filename, void* mem, u32 len);
    enum {
    /* 00 */ FAULT_NONE,
    /* 01 */ FAULT_TMOUT,
    /* 02 */ FAULT_CRASH,
    /* 03 */ FAULT_ERROR,
    /* 04 */ FAULT_NOINST,
    /* 05 */ FAULT_NOBITS
    };
#endif