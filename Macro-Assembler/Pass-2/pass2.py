# Author: Shantanu Wable

import re as regex
import itertools
import json
import os

# Clear the terminal before starting the program
os.system('cls' if os.name == 'nt' else 'clear')

# Clear the Expanded code file before running
with open("Macro-Assembler/Pass-2/output/expcode.asm",'w') as file:
    pass
file.close()

def get_key(val: str, dict: dict) -> any:

    """
    Funtion to get key from a dictionary based on value
    """

    for key, value in dict.items():
        if val == value:
            return key
    return None

def process_params(param: str):

    """
    Function to process strings of the type "(P,1)", "(C,11)", etc.

    Returns a tuple of the character corresponding to the table
    and the position of the parameter
    """

    pattern = r'\(([^,]+),(\d+)\)'
    match = regex.match(pattern, param)
    if match:
        component1 = match.group(1)
        component2 = int(match.group(2))
        return component1, component2
    else:
        return None
    
def convert(lst):

    """
    Funtion to convert list of items into space separated values
    """

    return ' '.join(lst)

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
spacePattern = r'\s+'

for line in callsFile:

    # Skip blank lines and remove beginning and trailing whitespace(s)
    if line == '\n': continue
    line = line.strip()

    # Split the line into words
    cmd = regex.split(spacePattern, line.rstrip())

    macroName = cmd[0]      # 0th item of call statement is macro name
    MPList = cmd[1::]       # Remaining items are parameters of macro

    # npp: number of positional parameters
    # nkp: number of keyword parameters

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
    
    # total number of parameters in the macro
    tot = npp + nkp

    # Create the skeleton of the Actual Parameter table based on the
    # Parameter name table of the corresponding macro
    APTAB = pntab[macroName].copy()
    aptPointer = 1

    # Check to see if macro call corresponds to a valid macro definition
    if mdtPointer == "":
        print("No such macro exists")
        continue

    # Processing parameters, building APTAB
    for parameter in MPList:

        # Remove trailing commas
        if parameter[-1] == ',':
            parameter = parameter.replace(',','',1)

        # Keyword Parameter
        if '=' in parameter:
            eqIndex = parameter.index('=')
            paramName = parameter[0:eqIndex:]
            paramValue = parameter[eqIndex + 1::]

            APTAB[get_key(paramName, APTAB)] = paramValue

        # Positional parameter
        else:
            APTAB[str(aptPointer)] = parameter
            aptPointer += 1

    # Assign default values to parameters that haven't been
    # assiged a value in the call statement
    if nkp:
        for key,value in kpdtab.items():
            if (value["macro"] == macroName) and (value["value"] != "---"):
                if aptab[get_key(value["name"])]:
                    aptab[get_key(value["name"])] = value["value"]

    # List to keep track of expanded stamements of corresponding macro call
    macroStmts = []

    # Traverse to the macro definition in the MDT
    current_line_number = 0
    for mdtLine in mdtFile:
        current_line_number += 1
        if current_line_number == mdtPointer:
            macroStmts.append(mdtLine)  
            break
    
    # From the definition, traverse till you reach MEND
    for mdtLine in mdtFile:
        if 'MEND' in mdtLine:
            break
        macroStmts.append(mdtLine) 

    # Replace parameter references with parameter names from APTAB
    for macroStatementIndex in range(len(macroStmts)):
        macroStatement = macroStmts[macroStatementIndex]
        macroCmd = regex.split(spacePattern, macroStatement.rstrip())

        # print(macroCmd)
        for itemIndex in range(len(macroCmd)):
            item = macroCmd[itemIndex]

            # if the statement contains a parameter reference, e.g. (P,1)
            # then replace that with the corresponding parameter from APTAB

            if '(' in item:
                tab,pos = process_params(item)
                macroCmd[itemIndex] = APTAB[str(pos)]

        macroCmd[0] = "+" + macroCmd[0]     # Add a '+' at the beginning to denote expanded code
        macroStmts[macroStatementIndex] = convert(macroCmd)
        expcodeFile.write(macroStmts[macroStatementIndex] + '\n')
        
    # print(macroStmts)
    mdtFile.seek(0)
    expcodeFile.write('\n')
    # print(APTAB)
    APTAB = ""
    mdtLine=""

