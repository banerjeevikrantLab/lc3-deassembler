#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


int codeBetween(int n, int i, int j){
    //shifts to the location of the first bit
    n = n >> i;
    int q = (1 << (j-i+1))-1;
    // AND with 2^(j-i input)-1 to find the int
    n = n & q;
    return n;
}


int findOPCode(int line){
    return codeBetween(line, 12, 15);
}

int twosComplement(int offs){
    offs = ~offs;
    return offs + 1;
}

string deasem_ANDnADD(int line, int opcode){

    int direct = codeBetween(line, 5, 5);
    string cmd;

    if(direct == 0){
        int dr = codeBetween(line, 9, 11);
        int sr1 = codeBetween(line, 6, 8);
        int sr2 = codeBetween(line, 0, 2);

        if(opcode == 1){
            return cmd + "ADD " + "R" + to_string(dr) + ", R" + to_string(sr1) + ", R" + to_string(sr2);
        }
        else{
            return cmd + "AND " + "R" + to_string(dr) + ", R" + to_string(sr1) + ", R" + to_string(sr2);
        }

    } else{
        int dr = codeBetween(line, 9, 11);
        int sr1 = codeBetween(line, 6, 8);
        int imm5 = codeBetween(line, 0, 4);

        if(imm5 > 15){
            imm5 = twosComplement(imm5);
        }

        if(opcode == 1){
            return cmd + "ADD " + "R" + to_string(dr) + ", R" + to_string(sr1) + ", #" + to_string(imm5);
        }
        else{
            return cmd + "AND " + "R" + to_string(dr) + ", R" + to_string(sr1) + ", #" + to_string(imm5);
        }

    }
}

string deasem_BR(int line){
    string cmd;
    int n = codeBetween(line, 11, 11);
    int z = codeBetween(line, 10, 10);
    int p = codeBetween(line, 9, 9);
    int offs = codeBetween(line, 0, 8);

    if(offs > 255){
        offs = twosComplement(offs);
    }

    return cmd + "BR" + to_string(n) + to_string(z) + to_string(p) + " " + to_string(offs);
}

string deasem_JMP(int line){
    string cmd;
    int baseR = codeBetween(line, 6, 8);

    if(baseR != 7){
        return "JMP R" + to_string(baseR);
    }else{
        return "RET";
    }
}

string deasem_JSR(int line){
    string cmd;
    if(codeBetween(line, 11, 11) == 1){
        int offs = codeBetween(line, 0, 10);
        if(offs > 1023){
            offs = twosComplement(offs);
        }
        return cmd + "JSR #" + to_string(offs);
    }
    else{
        int baseR = codeBetween(line, 6, 8);
        
        return cmd + "JSRR R" + to_string(baseR);
    }
}
string deasem_LOAD(int line){
    string cmd;
    int opCode = findOPCode(line);
    int offs_9 = codeBetween(line, 0, 8);
    int dr = codeBetween(line, 9, 11);

    if(offs_9 > 255){
        offs_9 = twosComplement(offs_9);
    }

    // 2 = LD, 6 = LDR, 10 = LDI, 14 = LEA

    if(opCode == 2){

        return cmd + "LD R" + to_string(dr) + ", #" + to_string(offs_9);

    }else if(opCode == 6){
        int offs_6 = codeBetween(line, 0, 5);
        int baseR = codeBetween(line, 6, 8);

        if(offs_6 > 31){
            offs_6 = twosComplement(offs_6);
        }
        return cmd + "LDR R" + to_string(dr) + ", R" + to_string(baseR) + ", #" + to_string(offs_6);

    }else if(opCode == 10){

        return cmd + "LDI R" + to_string(dr) + ", #" + to_string(offs_9);

    }else{

        return cmd + "LEA R" + to_string(dr) + ", #" + to_string(offs_9);
    }
}

string deasem_NOT(int line){
    string cmd; 
    int dr = codeBetween(line, 9, 11);
    int sr = codeBetween(line, 6, 8);

    return cmd + "NOT R" + to_string(dr) + ", R" + to_string(sr);
}

string deasem_RTI(){
    return "RTI";
}

string writeAssemblyCode(int line){
    int opCode = findOPCode(line);

    switch (opCode){
    case 0:
        
        break;
    case 1:
        return deasem_ANDnADD(line, opCode);
        break;
    case 2:
        
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:
        return deasem_ANDnADD(line, opCode);
        break;
    case 7:

        break;
    case 8:

        break;
    case 9:

        break;
    case 10:

        break;
    case 11:

        break;
    case 12:

        break;
    case 13:

        break;
    case 14:

        break;
    case 15:

        break;
    default:
        break;
    }

    return "Error";
}

int main() {
    string nextLineString;

    ifstream MyReadFile("program.txt");

    while (getline(MyReadFile, nextLineString)) {
        stringstream n; 
  
        int nextLine = 0; 
        n << hex << nextLineString; 
        n >> nextLine;
  
        cout << writeAssemblyCode(nextLine) << "\n";
    }


    MyReadFile.close();
}

