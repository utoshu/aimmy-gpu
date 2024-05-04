import subprocess
import time

def typewrite(text):
    for char in text:
        time.sleep(0.05)
        print(char, end='', flush=True)
    print()

def main():
    process = subprocess.Popen(["wmic", "path", "win32_VideoController", "get", "name"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    output = output.decode("utf-8")
    lines = output.splitlines()
    if len(lines) < 2:
        print("nothing is here...")
        return
    text = '\n'.join(lines[1:]).strip()
    print("\033[35m") 
    print(r"""                      _            _ 
   __ _ _ __  _   _  | |_ ___  ___| |_ 
  / _` | '_ \| | | | | __/ _ \/ __| __|
 | (_| | |_) | |_| | | ||  __/\__ \ |_ 
  \__, | .__/ \__,_|  \__\___||___/\__|
  |___/|_|                             """)
    
    print("\033[34m")  
    print(text)
    if "RTX" in text:
        print("\033[32m", end='') 
        typewrite("will work well")
    elif "GTX" in text or "XT" in text or "RX" in text:
        print("\033[33m", end='') 
        typewrite("will work fine")
    elif "VEGA" in text:
        print("\033[31m", end='')  
        typewrite("probably won't work")
    else:
        print("\033[31m", end='')  
        typewrite("couldn't get GPU, probably won't work with aimmy")
    print("press enter to exit...")
    input()
    
if __name__ == "__main__":
    main()