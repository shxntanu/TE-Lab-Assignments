import json
import re as regex

symboltable=json.load(open('symboltable.json','r'))
literaltable=json.load(open('literaltable.json','r'))
icfile=open('ic.txt','r')
opfile2=open('Pass2.txt','a')
opcode=op1code=op2code=""
lc=""
# word=""
cnt=-1
pattern=r'\s+'
for line in icfile:
    opcode=op1code=op2code=""
    # print(line)
    if line=='\n':
        continue
    line=line.strip()
    # print(line)
    ipwords=regex.split(pattern,line.rstrip())
    # ipwords=[]

    if len(ipwords)==4:
        # LC OPCODE OP1CODE OP2CODE
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        
        op1code=ipwords[2].replace('(',"")
        op1code=op1code.replace(')',"")
        cnt=ipwords[3].split(',')[1].replace(')',"")
        if 'S' in ipwords[3]:
            for symbol,[stcnt,symb,value] in symboltable.items():
                if stcnt==int(cnt):
                    # print(symbol)
                    op2code=value
                    # print(op2code)    
        elif 'L' in ipwords[3]:
            for literal,[ltcnt,literal,value] in literaltable.items():
                if ltcnt==int(cnt):
                    # print(symbol)
                    op2code=value
    elif len(ipwords)==3:
         #LC OPCODE CONSTANT*** FOR DL opcode
        print(ipwords)
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        cnt=ipwords[2].split(',')[1].replace(')',"")
        if 'C' in ipwords[2]:
            op1code=ipwords[2].split(',')[1].replace(')',"")
        elif 'S' in ipwords[2]:
            for symbol,[stcnt,symb,value] in symboltable.items():
                if stcnt==int(cnt):
                    # print(symbol)
                    op1code=value
        op2code=""
    elif len(ipwords)==2:
        # print(ipwords)
        if 'IS' in ipwords[1]:
            lc=ipwords[0]
            opcode=opcode=ipwords[1].split(',')[1].replace(')',"")
            op1code=""
            op2code=""
        else:
            continue
    else:
        continue
        
    
    opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")
        
