#!python3
import libtmux
import re
import time
import os

# make sure MySQL database has been initialize
# To initialize database: ./bin/mysqld --initialize-insecure --datadir=data

# Setting
dbms_path = "/home/sgx/research/Kangaroo/test/MYSQL"
dbms_client_path=dbms_path+"/bin/mysql"
dbms_server_path=dbms_path+"/bin/mysqld"
dbms_lib = dbms_path+"/lib"


fuzz_root_path="/home/sgx/research/Kangaroo/fuzz_root/MySQL"
dbms_data_dir=dbms_path+"/data"

######################################################

server = libtmux.Server()
session = server.new_session(session_name="fuzzing")

######################################################

os.system("pgrep mysqld | sudo xargs -i  kill -9 {}")
# os.system("kill -9 `pidof mysqld`")

########################################

afl_window = session.new_window(attach=False, window_name="afl")
afl_pane = afl_window.attached_pane
afl_pane.send_keys("cd /sys/devices/system/cpu")
afl_pane.send_keys("echo performance | sudo tee cpu*/cpufreq/scaling_governor")
afl_pane.send_keys("cd "+fuzz_root_path)
afl_pane.send_keys("export LD_LIBRARY_PATH="+dbms_lib)
afl_pane.send_keys("export ASAN_OPTIONS=symbolize=1:disable_coredump=0:abort_on_error=1")
afl_pane.send_keys("sudo bash -c \"echo core >/proc/sys/kernel/core_pattern\"")
afl_pane.send_keys("sudo ulimit -c unlimited")
afl_pane.send_keys("./afl-fuzz-mysql -i input -o ./fuzz_output mysql")
time.sleep(15)
result = afl_pane.cmd("capture-pane", "-p").stdout

shm_str = ""
for s in result:
    if(s.startswith("SHM_ENV_VAR")):
        shm_str = s[s.find(":")+2:]

if shm_str == "":
    print("Fail to get SHM_ENV_VAR")
env_str = " __AFL_SHM_ID=%s " % shm_str

#######################################################
server_window = session.new_window(attach=False, window_name="mysqld")
envs = env_str + " ASAN_OPTIONS=abort_on_error=1,symbolize=0,detect_leaks=0"
server_pane = server_window.attached_pane
afl_pane.send_keys("cd "+fuzz_root_path)
server_pane.send_keys("sudo " + envs + " "+dbms_server_path+" --basedir="+dbms_path+" --datadir="+dbms_data_dir+" --user=root --log-error=mysqlerr.err --pid-file=mysqlpid.pid  --max_execution_time=1000 &")

afl_pane.send_keys("")
time.sleep(20)
