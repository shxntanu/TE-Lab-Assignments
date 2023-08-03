import re as regex
import sys
import json
import os

os.system('cls' if os.name == 'nt' else 'clear')

mnemonics = json.load(open('assembler/mnemonics.json'))
msize = json.load(open('assembler/mnemonic-size.json'))

# filename = sys.argv[1]
# file = open(filename, "r")

file = open('assembler/test.asm', 'r')
icFile = open('assembler/ic.txt', 'a')
symbols = 'assembler/symbols.json'

pattern = r'\b\w+\b'

registers = {
    "areg" : 1,
    "breg" : 2,
    "creg" : 3,
    "dreg" : 4
}

label = instruction = op1 = op2 = op1code = op2code = ""
current = 0
previous = 0
relativeAddresses = []
IC = []
stCnt = 1

symbolTable = {}
literalTable = {}

# Looping through lines in file
for line in file: 

    cmd = regex.findall(pattern, line)
    cmd = list(map(lambda x: x.lower(), cmd))

    if cmd[0] == 'start':
        current = int(cmd[1])
        continue

    if len(cmd) == 4:
        label = cmd[0]
        instruction = cmd[1]
        op1 = cmd[2]
        op2 = cmd[3]

    else:
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

    if instruction in mnemonics:
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
            op1code = registers.get(op1)

        else:
            if op1 in symbolTable:
                op1code = symbolTable.get(op1)[0]
            else:
                symbolTable[op1] = [stCnt, op1, previous]
                op1code = stCnt
                stCnt += 1

        if op2 in registers:
            op2code = registers.get(op2)

        else:
            if op2 in symbolTable:
                op2code = symbolTable.get(op2)[0]
            else:
                symbolTable[op2] = [stCnt, op2, previous]
                op2code = stCnt
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
        icFile.write(str((opcode, op1code, op2code))+ "\n")

    else:
        print("Instruction not defined. Exiting the program...")
        exit(0)

with open(symbols, 'w') as json_file:
    json.dump(symbolTable, json_file, indent=4)
