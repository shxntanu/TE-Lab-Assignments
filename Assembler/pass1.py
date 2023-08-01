# TO BE COMPLETED

import re as regex
import sys
import json

mnemonics = json.load(open('assembler/mnemonics.json'))
msize = json.load(open('assembler/mnemonic-size.json'))

# filename = sys.argv[1]
# file = open(filename, "r")

file = open('assembler/test.asm', 'r')

pattern = r'\b\w+\b'

registers = {
    "areg" : 1,
    "breg" : 2,
    "creg" : 3,
    "dreg" : 4
}

label = instruction = op1 = op2 = op1code = op2code = ""
RA = 0
current = 0
previous = 0
relativeAddresses = []
machineCode = []

symbolTable = {}
literalTable = {}

# Looping through lines in file
for line in file: 

    cmd = regex.findall(pattern, line)
    cmd = list(map(lambda x: x.lower(), cmd))

    if cmd[0] == 'start':
        current = cmd[1]
        continue

    if len(cmd) == 4:
        label = cmd[0]
        instruction = cmd[1]
        op1 = cmd[2]
        op2 = cmd[3]

    else:
        try:
            label = cmd[0] if (cmd[0]in mnemonics) else None
            instruction = cmd[1] if label else cmd[0]
            op1 = cmd[2] if (instruction == cmd[1]) else cmd[1]
            op2 = None if (op1 == cmd[2]) else cmd[2]
        except:
            op2 = None

    if instruction in mnemonics:
        opcode = mnemonics.get(instruction)
        size = msize.get(instruction)

        previous = current
        current += size

        relativeAddresses.append(RA)
        machineCode.append(instruction)

        if label:
            if label in symbolTable:
                pass
            else:
                symbolTable[label] = previous

        if op1 in registers:
            op1code = registers.get(op1)

        else:
            if op1 in symbolTable:
                op1code = symbolTable.get(op1)
            else:
                symbolTable[op1] = previous

        if op2 in registers:
            op2code = registers.get(op2)

        else:
            if op2 in symbolTable:
                op2code = symbolTable.get(op2)
            else:
                symbolTable[op2] = previous

        print(instruction, opcode, op1code, op2code)

    else:
        print("Instruction not defined. Exiting the program...")
        exit(0)

    
