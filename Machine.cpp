#include "Machine.h"

#include <bits/stdc++.h>
using namespace std;

Machine::Machine(): hexScreenOutput(""),ASCIIScreenOutput("") {}

void Machine:: readInstructions(){
    ifstream file(this->InputFilePath());
    string line;
    int counter = processor.PC;
    while (getline(file , line)){
        istringstream iss(line);
        string word;
        while (iss >> word){
            if (word.size() == 4) {
                string i1 = word.substr(0, 2);
                string i2 = word.substr(2, 2);

                if (counter < 256){
                    RAM.setCell(counter++,i1);
                    RAM.setCell(counter++,i2);
                }
                else {
                    throw out_of_range("Memory is full! You Can't store more instructions." );
                }
            }
            else {
                cout << "The Instruction is not valid" << endl;
                exit(0);
            }
        }
    }
    file.close();
}

void Machine::displayMemory(){
    RAM.display();
}
void Machine::displayRegisters() {
    processor.showRegisters();
}
bool Machine:: fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

string Machine:: InputFilePath() {
    string filename;
    while (true) {
        cout << "Enter the file path you want to include (without the double quotes) : ";
        getline(cin, filename);

        cout << "You entered: " << filename << endl;

        if (fileExists(filename)) {
            cout << "File exists!" << endl;
            break;
        } else {
            cout << "Error: File does not exist. Please try again." << endl;
        }
    }
    return filename;
}

/*********************************************************************************************************************************** */
void Machine::fetch(bool stepByStep) {
    try {
        while (processor.PC < 256) {
            processor.IR = "";
            processor.IR += RAM.getCell(processor.PC++);
            if (processor.PC == 256) {
                if (RAM.getCell(255) != "00") {
                    throw std::bad_alloc();
                }
                break;
            }
            processor.IR += RAM.getCell(processor.PC++);
            if (stepByStep) {
                cout << "\n========================\n";
                cout << "Current instruction to be decoded: " << processor.IR << '\n';
                if (!hexScreenOutput.empty()){
                    cout << "Screen output in hexadecimal: " << hexScreenOutput << '\n';
                    cout << "Screen output in ASCII: " << ASCIIScreenOutput << '\n';
                    cout << "\n========================\n";
                }
                cout << "\n========================\n";
                cout << "Current memory status:\n";
                RAM.display();
                cout << "\n========================\n";
                cout << "Current registers status:\n";
                processor.showRegisters();
                cout << "\n========================\n";
                cout << "Press enter to continue: ";
                string s; getline(cin,s);
            }
            if (processor.IR == "C000") {
                break;
            }
            this->decode();
        }
    }
    catch (const std::bad_alloc& e) {
        cout << "Caught exception: " << e.what() << " - Last instruction is incomplete\n";
        exit(-1);
    }
    cout << "\nExecution is done\n";
    if (!hexScreenOutput.empty()){
        cout << "Screen output in hexadecimal: " << hexScreenOutput << '\n';
        cout << "Screen output in ASCII: " << ASCIIScreenOutput << '\n';
    }
    cout << "\n========================\n";
}

void Machine::decode() {
    // printing instruction, it is separated to be easier to implement
    if (processor.IR[0] == '3' && processor.IR.substr(2,2) == "00") {
        int rIndex = processor.IR[1]-'0';
        string result = processor.alu.binToHex(processor.reg[rIndex].getRegister());
        hexScreenOutput += result + ' ';
        int temp = processor.alu.hexToDecimal(result);
        ASCIIScreenOutput += char(temp);
    }
    string temp;
    char opCode = processor.IR[0];
    if (opCode == '1') {
        temp = "";
        temp += processor.IR[1];
        int rIndex = processor.alu.hexToDecimal(temp);
        string memAdress ="";
        memAdress += processor.IR[2];
        memAdress += processor.IR[3];

        processor.cu.loadFromMemory(rIndex,memAdress,processor,RAM);
    }
    else if (opCode == '2') {
        string pattern = "";
        pattern += processor.IR[2];
        pattern += processor.IR[3];
        temp = "";
        temp+=processor.IR[1];
        int rIndex = processor.alu.hexToDecimal(temp);

        processor.cu.loadWithPattern(rIndex,pattern,processor);
    }
    else if(opCode == '3'){
        temp = "";
        temp += processor.IR[1];
        int rIndex = processor.alu.hexToDecimal(temp);
        string memoryAdress = "";
        memoryAdress += processor.IR[2];
        memoryAdress += processor.IR[3];
        processor.cu.store(rIndex,memoryAdress,RAM,processor);

    }
    else if(opCode == '4'){
        temp = "";
        temp+=processor.IR[2];
        int R = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int S = processor.alu.hexToDecimal(temp);
        processor.cu.move(S,R,processor);
    }
    else if (opCode == '5') {
        temp = "";
        temp+=processor.IR[2];
        int S = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int T = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[1];
        int R = processor.alu.hexToDecimal(temp);

        processor.alu.addTwoRegistersTwosComp(S,T,R,processor);
    }
    else if (opCode == '6') {
        temp = "";
        temp+=processor.IR[2];
        int S = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int T = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[1];
        int R = processor.alu.hexToDecimal(temp);

        processor.alu.addTwoRegistersFloat(S,T,R,processor);
    }
    else if (opCode == '7') {
        temp = "";
        temp+=processor.IR[2];
        int S = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int T = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[1];
        int R= processor.alu.hexToDecimal(temp);

        string result = processor.alu.OR(S,T,processor);
        processor.reg[R].setRegister(result);
    }
    else if (opCode == '8') {
        temp = "";
        temp+=processor.IR[2];
        int S = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int T = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[1];
        int R= processor.alu.hexToDecimal(temp);

        string result = processor.alu.AND(S,T,processor);
        processor.reg[R].setRegister(result);
    }
    else if (opCode == '9') {
        temp = "";
        temp+=processor.IR[2];
        int S = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[3];
        int T = processor.alu.hexToDecimal(temp);
        temp = "";
        temp+=processor.IR[1];
        int R= processor.alu.hexToDecimal(temp);

        string result = processor.alu.XOR(S,T,processor);
        processor.reg[R].setRegister(result);
    }
    else if (opCode == 'A') {
        temp = "";
        temp += processor.IR[1];
        int r1Index = processor.alu.hexToDecimal(temp);
        temp = "";
        temp += processor.IR[3];
        int numberOftimes = processor.alu.hexToDecimal(temp);
        processor.alu.rotate(r1Index,numberOftimes,processor);
    }
    else if(opCode == 'B'){
        temp = "";
        temp += processor.IR[1];
        int rIndex = processor.alu.hexToDecimal(temp);
        processor.cu.equalJump(rIndex,processor);
    }
    else if(opCode == 'D'){
        temp = "";
        temp += processor.IR[1];
        int rIndex = processor.alu.hexToDecimal(temp);
        processor.cu.greaterJump(rIndex,processor);
    }
}