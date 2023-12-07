import libtmux
import re
import time
import os

# setting
postgres_install_path = "/home/sgx/research/Kangaroo/test/pg"
postgres_bin_path = postgres_install_path+"/bin/"
postgres_lib_path = postgres_install_path+"/lib/"
postgres_data_path = postgres_install_path+"/data"

######################################################
server = libtmux.Server()
session = server.new_session(session_name="fuzzing")

afl_window = session.new_window(attach=False, window_name="afl")
afl_pane = afl_window.attached_pane

afl_pane.send_keys("export LD_LIBRARY_PATH="+postgres_lib_path)
afl_pane.send_keys("./afl-fuzz-postgres -i input -o ./fuzz_output fuzz_pg")
time.sleep(15)
result = afl_pane.cmd("capture-pane", "-p").stdout

shm_str = ""
for s in result:
    if(s.startswith("SHM_ENV_VAR")):
            shm_str = s[s.find(":")+2:]

print(shm_str)
env_str = "export __AFL_SHM_ID=%s" % shm_str

server_window = session.new_window(attach=False, window_name="PostgreSever")
server_pane = server_window.attached_pane
server_pane.send_keys(env_str)
server_pane.send_keys(postgres_bin_path+"postgres -D "+postgres_data_path)

afl_pane.send_keys("")
time.sleep(10)
