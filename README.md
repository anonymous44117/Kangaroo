# Kangaroo
Prototype of a DBMS fuzzing framework.

**System requeirement:**  
+ `Linux sgx 5.4.0 #18.04.1-Ubuntu x86_64`
+ `LLVM-6.0` for afl-llvm
+ `gcc/g++ > 8.0` for MySQL

**1. Prerequisites**  
```bash
sudo apt-get -y update && apt-get -y upgrade
sudo apt-get -y install gdb bison flex git make cmake build-essential gcc-multilib g++-multilib xinetd libreadline-dev zlib1g-dev
sudo apt-get -y install clang libssl-dev libncurses5-dev

# Compile AFL, which is used for instrumenting the DBMSs
git clone https://github.com/google/AFL.git
cd AFL
sed -i  's/#define MAP_SIZE_POW2       16/#define MAP_SIZE_POW2       19/' config.h
make
cd llvm_mode/
make
```

**2. Patch DBMS**  
Download the source of specific version of DBMSs.  
```bash
# SQLite
git clone https://github.com/sqlite/sqlite.git --depth=1 -b version-3.34.0
# Postgres
git clone https://github.com/postgres/postgres.git --depth=1 -b REL_14_2
# MySQL
git clone https://github.com/mysql/mysql-server.git --depth=1 -b mysql-cluster-8.0.29

```

Apply corresponding patch to DBMS to enable multi-plan execution (MPE).  
The patches for all three DBMSs are put in folder `DBMS-multiplan-patch`.
```bash
# Copy the patch to DBMS source code path before applying
git apply xxxx.patch
```

**3. Instrument DBMS**  

+ SQLite
```bash
cd sqlite
mkdir bld
cd bld
CC=/path/to/afl-gcc CXX=/path/to/afl-g++ ../configure --prefix=/path/to/install
CC=/home/sgx/research/AFL/afl-gcc CXX=/home/sgx/research/AFL/afl-g++ ../configure --prefix=/home/sgx/research/Kangaroo/test/SQLITE
make -j4
make install
```

+ MySQL
```bash
cd mysql-server
mkdir bld
cmake .. -DDOWNLOAD_BOOST=1 -DWITH_BOOST=../boost -DWITH_ASAN=1 -DWITH_ASAN_SCOPE=1 -DWITH_DEBUG=1 -DCPACK_MONOLITHIC_INSTALL=1 -DCMAKE_C_COMPILER=/path/to/afl-gcc -DCMAKE_CXX_COMPILER=/path/to/afl-g++ -DCMAKE_INSTALL_PREFIX=/path/to/install
make
make install
```

+ PostgreSQL
```bash
cd postgres/
mkdir bld
CC=/path/to/afl-gcc CXX=/path/to/afl-g++ ../configure --prefix=/path/to/install
make -j4
make install
```

4. **Build fuzzer**  

+ SQLite
```bash
cd AFL-sqlite
make afl-fuzz
```

+ MySQL
``` bash
cd AFL-cs
make mysql
```

+ PostgreSQL
```bash
cd AFL-cs
make postgres
```

**4. Run fuzzer** 

+ SQLite
```bash
# Copy the previously built fuzzer(afl-fuzz) to path fuzz_root/SQLite 
cd fuzz_root/SQLite
./afl-fuzz -i input -o fuzz_output /path/to/sqlite3 --bail
```

+ MySQL
```bash
# initialize database. Note that, only do this once
path/to/mysqld --initialize-insecure

# Copy the previously built fuzzer(afl-fuzz-mysql) to path fuzz_root/MySQL
cd fuzz_root/MySQL
# configure the run.py setting before run it
python3 run.py
tmux a -t fuzzing
```

+ PostgreSQL
```bash
# initialize database. Note that, only do this once
path/to/pg_ctl initdb -D /path/to/data
path/to/createuser -s postgres
path/to/createdb test

# Copy the previously built fuzzer(afl-fuzz-postgres) to path fuzz_root/PostgeSQL
cd fuzz_root/PostgeSQL
# configure the run.py setting before run it
python3 run.py
tmux a -t fuzzing
```
