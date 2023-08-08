# Author: Shantanu Wable

import re as regex
import sys
import json
import os

os.system('cls' if os.name == 'nt' else 'clear')

# Command line arguments

# filename = sys.argv[1]
# file = open(filename, "r")

file = open('test.asm', 'r')
icFile = open('ic.txt', 'a')

symbols = 'symbols.json'
literals = 'literals.json'

pattern = r'\b[a-zA-Z0-9\-="]+\b'

mnemonics = {
    "stop" : "(IS, 00)",
    "add" : "(IS, 01)",
    "sub" : "(IS, 02)",
    "mult" : "(IS, 03)",
    "mover" : "(IS, 04)",
    "movem" : "(IS, 05)",
    "comp" : "(IS, 06)",
    "bc" : "(IS, 07)",
    "div" : "(IS, 08)",
    "read" : "(IS, 09)",
    "print" : "(IS, 10)",
    "dc" : "(DL, 01)",
    "ds" : "(DL, 02)",
}

msize = {
    "stop" : 1,
    "add" : 1,
    "sub" : 1,
    "mult" : 1,
    "mover" : 1,
    "movem" :1,
    "comp" : 1,
    "bc" : 1,
    "div" : 1,
    "read" : 1,
    "print" : 1,
    "start" : 1,
    "end" : 1,
    "origin" : 1,
    "equ" : 1,
    "ltorg" : 1,
    "dc" : 1,
    "ds" : 1
}

registers = {
    "areg" : 1,
    "breg" : 2,
    "creg" : 3,
    "dreg" : 4
}

conditionCodes = {
    "lt" : 1,
    "le" : 2,
    "eq" : 3,
    "gt" : 4,
    "ge" : 5,
    "any" : 6
}

directives = {
    "start" : "(AD, 01)",
    "end" : "(AD, 02)",
    "origin" : "(AD, 03)",
    "equ" : "(AD, 04)",
    "ltorg" : "(AD, 05)",
}

label = instruction = op1 = op2 = op1code = op2code = ""
current = 0
previous = 0
relativeAddresses = []
IC = []
stCnt = 1
ltCnt = 1

symbolTable = {}
literalTable = {}

# Looping through lines in file
for line in file: 

    # Skip blank lines
    if line == '\n': continue

    cmd = regex.findall(pattern, line)
    cmd = list(map(lambda x: x.lower(), cmd))
    
    if len(cmd) == 4:

        # Command is of the format: LABEL INSTRUCTION OP1 OP2
        
        label = cmd[0]
        instruction = cmd[1]
        op1 = cmd[2]
        op2 = cmd[3]

    elif len(cmd) == 3:

        # Command is of the format: OP1 INSTRUCTION OP2
        #                                   OR
        #                           INSTRUCTION OP1 OP2

        cmdIndex = None
        for command in cmd:
            if command in mnemonics:
                cmdIndex = cmd.index(command)
                break
        
        instruction = cmd[cmdIndex]
        if cmdIndex == 0:
            op1 = cmd[1]
            op2 = cmd[2]
        
        else:
            op1 = cmd[cmdIndex - 1]
            op2 = cmd[cmdIndex + 1]
    
    elif len(cmd) == 2:

        # Command is of the format: INSTRUCTION OP1

        instruction = cmd[0]
        op1 = cmd[1]

    else:

        # Command is of the format: INSTRUCTION 

        instruction = cmd[0]

    if instruction in directives:
        if instruction == 'start':
            current = int(cmd[1])
            opcode = directives.get(instruction)
            op1code = f"(C, {current})"
            icFile.write(f"{opcode} {op1code}\n")
            continue

        elif instruction == 'end':
            opcode = directives.get(instruction)
            # size = int(msize.get(instruction))
            icFile.write(str((opcode))+ "\n")
            break

        elif instruction == 'origin':
            opcode = directives.get(instruction)
            op1 = cmd[1]
            if "-" in op1:
                label = op1.split('-')[0]
                offset = op1.split('-')[1]
                op1code = f"(S, {symbolTable.get(label)[0]})-{offset}"
                previous = current
                current = symbolTable.get(op1)[2] - int(offset)
                relativeAddresses.append(previous)

            else:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
                previous = current
                current = symbolTable.get(op1)[2]
                relativeAddresses.append(previous)
            
        elif instruction == 'equ':
            pass
        
        elif instruction == 'ltorg':
            pass

    elif instruction in mnemonics:
        opcode = mnemonics.get(instruction)
        size = int(msize.get(instruction))

        previous = current
        current += size

        relativeAddresses.append(previous)

        if label:
            if label in symbolTable:
                pass
            else:
                symbolTable[label] = [stCnt, label, previous]
                stCnt += 1

        if op1 in registers:
            op1code = f"({registers.get(op1)})"

        elif "=" in op1:
            literal = op1.split('=')[1][1]
            if op1 in literalTable:
                op1code = f"(L, {literalTable.get(literal)[0]})"
            else:
                literalTable[op1] = [ltCnt, literal, -1]
                op1code = f"(L, {ltCnt})"
                ltCnt += 1

        else:
            if op1 in symbolTable:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
            else:
                symbolTable[op1] = [stCnt, op1, previous]
                op1code = f"(S, {stCnt})"
                stCnt += 1

        if op2 in registers:
            op2code =  f"({registers.get(op2)})"
            
        elif "=" in op2:
            literal = op2.split('=')[1][1]
            if op2 in literalTable:
                op2code = f"(L, {literalTable.get(literal)[0]})"
            else:
                literalTable[op2] = [ltCnt, literal, -1]
                op1code = f"(L, {ltCnt})"
                ltCnt += 1

        else:
            if op2 in symbolTable:
                op2code = f"(S, {symbolTable.get(op2)[0]})"
            else:
                symbolTable[op2] = [stCnt, op2, previous]
                op2code = f"(S, {stCnt})"
                stCnt += 1

        # print({
        #     "Instruction" : instruction,
        #     "Instruction Code" : opcode,
        #     "Operand 1" : op1,
        #     "Operand 1 Code" : op1code,
        #     "Operand 2" : op2,
        #     "Operand 2 Code" : op2code,
        # })

        IC.append((opcode, op1code, op2code))
        print(IC, relativeAddresses, instruction, opcode, op1code, op2code)
        icFile.write(f"{opcode} {op1code} {op2code}\n")

    else:
        print("Instruction not defined. Exiting the program...")
        exit(0)

with open(symbols, 'w') as json_file:
    json.dump(symbolTable, json_file, indent=4)

with open(literals, 'w') as json_file:
    json.dump(literalTable, json_file, indent=4)
