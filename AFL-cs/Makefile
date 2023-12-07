#
# american fuzzy lop - makefile
# -----------------------------
#
# Written and maintained by Michal Zalewski <lcamtuf@google.com>
# 
# Copyright 2013, 2014, 2015, 2016, 2017 Google LLC All rights reserved.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
# 
#   http://www.apache.org/licenses/LICENSE-2.0
#

PROGNAME    = afl
VERSION     = $(shell grep '^\#define VERSION ' config.h | cut -d '"' -f2)

#####################################################################
# setting for PostgreSQL
PGSQL_INSTALL_PATH = /home/sgx/research/Kangaroo/test/pg

#####################################################################
# Setting for MySQL
MYSQL_INSTALL_PATH = /home/sgx/research/Kangaroo/test/MYSQL

######################################################################
# Seting for MariaDB
MARIA_INSTALL_PATH =  /home/postgres/mariadb-10.11.1-multiplan
MARIA_LIB_PATH   = $(MARIA_INSTALL_PATH)/lib
MARIA_INSTALL_HEADER_PATH = $(MARIA_INSTALL_PATH)/include/mysql

################################################################


RE2_LIB_OPTION = -lre2 -lpthread

PREFIX     ?= /usr/local
BIN_PATH    = $(PREFIX)/bin
HELPER_PATH = $(PREFIX)/lib/afl
DOC_PATH    = $(PREFIX)/share/doc/afl
MISC_PATH   = $(PREFIX)/share/afl


DEPEN_INCLUDE = ../include
DEPEN_LIB_PATH  = ../lib
PG_DEPEN_LIB   = mutate-postgres
MYSQL_DEPEN_LIB = mutate-mysql
DEPEN_SANITIZER = sanitizer

# PROGS intentionally omit afl-as, which gets installed elsewhere.

PROGS       = afl-fuzz

CC         = g++
CFLAGS     ?= -fpermissive --std=c++17
CFLAGS     += -g -w \
	      -DAFL_PATH=\"$(HELPER_PATH)\" -DDOC_PATH=\"$(DOC_PATH)\" \
	      -DBIN_PATH=\"$(BIN_PATH)\"
CFLAGS     += -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

ifneq "$(filter Linux GNU%,$(shell uname))" ""
  LDFLAGS  += -ldl
endif

ifeq "$(findstring clang, $(shell $(CC) --version 2>/dev/null))" ""
  TEST_CC   = afl-gcc
else
  TEST_CC   = afl-clang
endif

COMM_HDR    = alloc-inl.h config.h debug.h types.h

all: postgres

postgres: afl-fuzz.cpp $(COMM_HDR)
	$(CC) $(CFLAGS) -DTARGET_POSTGRES -I./ -I$(PGSQL_INSTALL_PATH)/include -I$(DEPEN_INCLUDE) -I$(DEPEN_SANITIZER) afl-fuzz.cpp -o afl-fuzz-postgres $(LDFLAGS) -L$(DEPEN_LIB_PATH) -l$(PG_DEPEN_LIB) -lpgclient -L$(PGSQL_INSTALL_PATH)/lib -ldl -lpq $(RE2_LIB_OPTION)

mysql: afl-fuzz.cpp $(COMM_HDR)
	$(CC) $(CFLAGS) -DTARGET_MYSQL -g afl-fuzz.cpp -I$(DEPEN_INCLUDE) -o afl-fuzz-mysql $(LDFLAGS) -L$(DEPEN_LIB_PATH) -l$(MYSQL_DEPEN_LIB) -lMysqlClient -L$(MYSQL_INSTALL_PATH)/lib -lmysqlclient $(RE2_LIB_OPTION)

mariadb: afl-fuzz.cpp $(COMM_HDR)
	$(CC) $(CFLAGS) -DTARGET_MARIADB -g afl-fuzz.cpp $(DEPEN_SANITIZER)/checker_mysql.cpp $(DEPEN_SANITIZER)/filter_mysql.cpp -I$(MARIA_INSTALL_HEADER_PATH) -I$(DEPEN_INCLUDE) -I$(DEPEN_SANITIZER) -o afl-fuzz-mariadb $(LDFLAGS) -L$(DEPEN_LIB_PATH) -l$(DEPEN_LIB) -L$(MARIA_LIB_PATH) -lmariadb -Wl,-rpath,$(MARIA_LIB_PATH) $(RE2_LIB_OPTION)

.NOTPARALLEL: clean

clean:
	rm -f $(PROGS) afl-as as afl-g++ afl-clang afl-clang++ *.o *~ a.out core core.[1-9][0-9]* *.stackdump test .test test-instr .test-instr0 .test-instr1 qemu_mode/qemu-2.10.0.tar.bz2 afl-qemu-trace
