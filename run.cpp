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

int writeAssemblyCode(int line){
    int OPCode = findOPCode(line);

    return OPCode;
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

