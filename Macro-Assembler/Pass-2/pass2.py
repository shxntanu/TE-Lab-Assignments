# Author: Shantanu Wable

import re as regex
import itertools
import json
import os

# Clear the terminal before starting the program
os.system('cls' if os.name == 'nt' else 'clear')

# Funtion to get key from a dictionary based on value
def get_key(val: str, dict: dict) -> any:
    for key, value in dict.items():
        if val == value:
            return key

# Input File(s)
kpdtabFile = open('Macro-Assembler/Pass-2/input/kpdtab.json', 'r')
mdtFile = open('Macro-Assembler/Pass-2/input/mdt.asm', 'r')
mntFile = open('Macro-Assembler/Pass-2/input/mnt.json', 'r')
pntabFile = open('Macro-Assembler/Pass-2/input/pntab.json', 'r')
callsFile = open('Macro-Assembler/Pass-2/input/calls.asm', 'r')

# Expanded Code (Output) File
expcodeFile = open('Macro-Assembler/Pass-2/output/expcode.asm', 'a')

# Tables
kpdtab = json.load(kpdtabFile)
mnt = json.load(mntFile)
pntab = json.load(pntabFile)

# Regex pattern to split on occurrence of one or more spaces
pattern = r'\s+'

for line in callsFile:

    # Skip blank lines and remove beginning and trailing whitespace(s)
    if line == '\n': continue
    line = line.strip()

    # Split the line into words
    cmd = regex.split(pattern, line.rstrip())

    macroName = cmd[0]
    MPList = cmd[1::]

    mdtPointer, kpdtPointer, npp, nkp = "","","",""
    # print(cmd)

    for key,value in mnt.items():
        # print(key, value)
        if value['name'] == macroName:
            mdtPointer = value['mdtp']
            kpdtPointer = value['kpdtp']
            npp = value['pp']
            nkp = value['kp']
            break
    
    tot = npp + nkp

    APTAB = pntab[macroName].copy()
    aptPointer = 1

    if mdtPointer == "":
        print("No such macro exists")
        continue

    # Processing parameters, building APTAB
    for parameter in MPList:

        if parameter[-1] == ',':
            parameter = parameter.replace(',','',1)

        # Keyword Parameter
        if '=' in parameter:
            eqIndex = parameter.index('=')
            paramName = parameter[0:eqIndex:]
            paramValue = parameter[eqIndex + 1::]

            APTAB[get_key(paramName, APTAB)] = paramValue

        else:
            APTAB[str(aptPointer)] = parameter
            aptPointer += 1

    
    print(APTAB)
    APTAB = ""
