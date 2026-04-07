import os
import sys
import random
import time

start_time = time.time()
rand1 = random.randint(1, 10)
rand2 = random.randint(1, 10)

pid_fils1 = os.fork()

if pid_fils1 == 0:
    time.sleep(rand1)
    print("Fils 1: ", time.time() - start_time)
else:
    pid_fils2 = os.fork()
    if pid_fils2 == 0:
        time.sleep(rand2)
        print("Fils 2: ", time.time() - start_time)
    else:
        os.wait()
    os.wait()
