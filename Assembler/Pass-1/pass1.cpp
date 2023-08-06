/*
    Author: Shantanu Wable
*/

#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <string>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int main() {

    clearScreen();

    // Mnemonic Table
    map<string, int> mnemonics = {
        {"stop", 1},
        {"add", 2},
        {"sub", 3},
        {"mult", 4},
        {"mover", 5},
        {"movem", 6},
        {"comp", 7},
        {"bc", 8},
        {"div", 9},
        {"read", 10},
        {"print", 11},
        {"start", 12},
        {"end", 13},
        {"origin", 14},
        {"equ", 15},
        {"ltorg", 16},
        {"dc", 17},
        {"ds", 18}
    };
    
    ifstream file("test.asm");
    ofstream icFile("ic.txt", ios_base::app);
    string symbolsFile = "symbols.json";

    // Regex pattern denotes Alphanumeric Characters between word boundary
    regex pattern(R"(\b\w+\b)"); 

    // Register Map
    map<string, int> registers = {
        {"areg", 1},
        {"breg", 2},
        {"creg", 3},
        {"dreg", 4}
    };

    string label, instruction, op1, op2;
    int current = 0, previous = 0, stCnt = 1;
    vector<int> relativeAddresses;
    vector<tuple<int, int, int>> IC;

    map<string, tuple<int, string, int>> symbolTable;
    map<string, tuple<int, string, int>> literalTable;

    string line;
    while (getline(file, line)) {
        smatch cmdMatch;
        vector<string> cmd;
        
        // Tokenize the line
        while (regex_search(line, cmdMatch, pattern)) {
            cmd.push_back(cmdMatch.str());
            line = cmdMatch.suffix();
        }

        // Converting the tokens into lowercase
        for (string& token : cmd) {
            transform(token.begin(), token.end(), token.begin(), ::tolower);
        }

        // Start the line counting at the start address
        if (cmd[0] == "start") {
            current = stoi(cmd[1]);
            continue;
        }

        if (cmd.size() == 4) {
            label = cmd[0];
            instruction = cmd[1];
            op1 = cmd[2];
            op2 = cmd[3];
        } 
        
        else {
            int cmdIndex = -1;
            for (size_t i = 0; i < cmd.size(); ++i) {
                if (mnemonics.find(cmd[i]) != mnemonics.end()) {
                    cmdIndex = static_cast<int>(i);
                    break;
                }
            }

            instruction = cmd[cmdIndex];
            if (cmdIndex == 0) {
                op1 = cmd[1];
                op2 = cmd[2];
            } else {
                op1 = cmd[cmdIndex - 1];
                op2 = cmd[cmdIndex + 1];
            }
        }

        // If instruction exists in the Mnemonics table
        if (mnemonics.find(instruction) != mnemonics.end()) {
            int opcode = mnemonics[instruction];
            int size = 0;

            previous = current;
            current += size;

            relativeAddresses.push_back(previous);

            if (!label.empty()) {
                if (symbolTable.find(label) != symbolTable.end()) {
                    // Do nothing
                } else {
                    symbolTable[label] = make_tuple(stCnt, label, previous);
                    stCnt++;
                }
            }

            int op1code = 0, op2code = 0;

            if (registers.find(op1) != registers.end()) {
                op1code = registers[op1];
            } else {
                if (symbolTable.find(op1) != symbolTable.end()) {
                    op1code = get<0>(symbolTable[op1]);
                } else {
                    symbolTable[op1] = make_tuple(stCnt, op1, previous);
                    op1code = stCnt;
                    stCnt++;
                }
            }

            if (registers.find(op2) != registers.end()) {
                op2code = registers[op2];
            } else {
                if (symbolTable.find(op2) != symbolTable.end()) {
                    op2code = get<0>(symbolTable[op2]);
                } else {
                    symbolTable[op2] = make_tuple(stCnt, op2, previous);
                    op2code = stCnt;
                    stCnt++;
                }
            }

            IC.push_back(make_tuple(opcode, op1code, op2code));
            cout << opcode << " " << op1code << " " << op2code << endl;
            icFile << "(" << opcode << ", " << op1code << ", " << op2code << ")" << endl;
        } else {
            cout << "Instruction not defined. Exiting the program..." << endl;
            exit(0);
        }
    }

    ofstream symbolsJson(symbolsFile);
    symbolsJson << "{" << endl;
    for (const auto& entry : symbolTable) {
        symbolsJson << "\"" << entry.first << "\" : {"
                    << "\"index\": \"" << get<0>(entry.second) << "\", "
                    << "\"label\": \"" << get<1>(entry.second) << "\", "
                    << "\"address\": \"" << get<2>(entry.second) << "\"}," << endl;
    }
    symbolsJson.seekp(-2, symbolsJson.cur);
    symbolsJson << "}" << endl;

    return 0;
}
