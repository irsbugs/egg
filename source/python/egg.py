#!/usr/bin/env python3
#
# egg.py
# Egg timer program in Python.
# Does not employ using C executables exported functions
#
import time
import sys
import os

PATH_FILE = "/tmp/egg.data" 

menu = """
    1. Start Egg Timer
    2. Elapsed Time
    3. Time Remaining
    4. Stop Egg Timer

Enter Choice: """

def get_menu_selection():
    while True:
        response = input(menu)
        try:
            value = int(response)
            if value >= 1 and value <= 4:
                return value
        except:
            continue

def start_egg_timer(duration = 60):        
    """
    1. Start Egg Timer
    Write a timestamp and a cooking duration to a tmp file:
    """   
    ts = int(time.time()) #1590824805.3866053 1590824805
    s = "{},{}".format(ts,duration) 
    
    with open(PATH_FILE, "w") as fout:
        fout.write(s)
    print("Egg Cooking Duration: {}".format(duration))
        
def elapsed_time():
    """
    2. Elapsed Time
    Read the data from /tmp/egg.data
    Calculate the elapsed time
    """    
    try:
        with open(PATH_FILE, "r") as fin:
            data = fin.read()
            data_list = data.split(",")
            ts_begin = int(data_list[0])
            ts_now = int(time.time())
            return (ts_now - ts_begin)            
    except:
        return 0
      
def time_remaining(): 
    """
    3. Time Remaining():
    Read the data from /tmp/egg.data
    Calculate the remaining time     
    """
    try:
        with open(PATH_FILE, "r") as fin:
            data = fin.read()
            data_list = data.split(",")
            ts_begin = int(data_list[0])
            ts_duration = int(data_list[1])
            ts_now = int(time.time())
            return ((ts_begin + ts_duration) - ts_now)
    except:
        return 0

def stop_egg_timer():
    """
    4. Stop Egg Timer
    If it exists delete the /tmp/ file
    """
    try:
        os.remove(PATH_FILE)
    except:
        pass
    sys.exit("Enjoy your eggs.")    
           

def main():       
    while True:

        value = get_menu_selection()
        print() #"value:", value)
        
        if value == 1:
            """
            1. Start Egg Timer
            """
            try:
                if len(sys.argv) > 1:
                    duration = int(sys.argv[1])
                    start_egg_timer(duration)
                else:
                    start_egg_timer()
            except:
                start_egg_timer()
           
        if value == 2:
            """
            2. Elapsed Time
            """
            elapsed = elapsed_time()
            print("Elapsed Time: {}".format(elapsed))
            
        if value == 3:
            """
            3. Time Remaining
            """
            remain = time_remaining()
            print("Time Remaining: {}".format(remain))         
                    
        if value == 4:
            """
            4. Stop Egg Timer
            """
            stop_egg_timer()

if __name__ == "__main__":      
     main()
