#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int twosComplement(int offs){
    offs = ~offs;
    return offs + 1;
}

string deasem_ANDnADD(int line, int opcode){

    int direct = codeBetween(line, 5, 5);
    if(direct == 0){
        int dr = codeBetween(line, 9, 11);
        int sr1 = codeBetween(line, 6, 8);
        int sr2 = codeBetween(line, 0, 2);

        if(opcode == 1){
            return "ADD " + "R" + dr + ", R" + sr1 + ", R" + sr2;
        }
        else{
            return "AND " + "R" + dr + ", R" + sr1 + ", R" + sr2;
        }

    } else{
        int dr = codeBetween(line, 9, 11);
        int sr1 = codeBetween(line, 6, 8);
        int imm5 = codeBetween(line, 0, 4);

        if(imm5 > 15){
            imm5 = twosComplement(imm5);
        }

        if(opcode == 1){
            return "ADD " + "R" + dr + ", R" + sr1 + ", #" + imm5;
        }
        else{
            return "AND " + "R" + dr + ", R" + sr1 + ", #" + imm5;
        }

    }
}



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

int writeAssemblyCode(int line){
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
    }

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

