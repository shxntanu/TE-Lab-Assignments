# Author: Shantanu Wable

import re as regex
import itertools
import json
import os

os.system('cls' if os.name == 'nt' else 'clear')

# Creating the MDT file 
with open("Macro-Assembler/Pass-1/output/mdt.asm",'w') as file:
    pass
file.close()

# Input File(s)
inputFile = 'Macro-Assembler/Pass-1/input/program.asm'

# Output File(s)
mdtFile = open('Macro-Assembler/Pass-1/output/mdt.asm', 'a')

# Regex pattern to split on occurrence of one or more spaces
pattern = r'\s+'

# Flags
mSign = False
mDef = False

# Tables
mnt = {}
pntab = {}
kpdtab = {}

# Storage variables
macroName = ""
kpdtabIndex = 1
mntIndex = 1
mdtLoc = 1

# Loop through lines in file
for line in inputFile:
    # Skip blank lines and remove beginning and trailing whitespace(s)
    if line == '\n': continue
    line = line.strip()

    # Split the line into words
    cmd = regex.split(pattern, line.rstrip())

    # When 'MACRO' is encountered, set the macro signature flag
    if len(cmd) == 1 and cmd[0] == 'MACRO':
        mSign = True
        continue

    # If macro definition has been encountered, process its right next line
    if mSign:
        macroName = cmd.pop(0)
        pntab[macroName] = {}
        paramCnt = 0
        
        pp = 0
        kp = 0
        
        
        # Now, cmd contains the list of all the parameters
        for parameter in cmd:
            if '&' in parameter and '=' not in parameter:
                paramCnt += 1
                pp += 1
                
                paramName = parameter[1::]

                pntab[macroName][paramCnt] = paramName
                pp += 1
                
            elif '&' in parameter and '=' in parameter:
                paramCnt += 1
                kp += 1
                
                # Get the index of the '=' sign and 
                eqIndex = parameter.index('=')
                
                paramName = parameter[1:eqIndex:]
                paramDefValue = parameter[eqIndex + 1::]

                pntab[macroName][paramCnt] = paramName
                
                kpdtab[kpdtabIndex] = {
                    'index' : kpdtabIndex, 
                    'name' : paramName, 
                    'value' : paramDefValue if paramDefValue else '---',
                }
                
                kpdtabIndex += 1
                
            else:
                pass
                
        mSign = False
        mDef = True
        mnt[mntIndex] = {
            'index' : mntIndex,
            'name' : macroName,
            'pp' : pp,
            'kp' : kp,
            'mdtp' : mdtLoc,
            'kpdtp' : kpdtabIndex if kp else '---',
        }
        mntIndex += 1
        continue
    
    if mDef:
        mdtLoc += 1
        callLine = ""
        
        for command in cmd:
            if '&' in command:
                replParamValue = f'(P,{pntab[macroName].index(command[1::])})'
                callLine += replParamValue + " "
            else:
                callLine += command + " "    
                
        mdtFile.write(callLine + '\n')
        continue
    
    if len(cmd) == 1 and cmd[0] == 'MEND':
        mdtLoc += 1
        mDef = False
        mdtFile.write('MEND\n')
        continue
    
     
