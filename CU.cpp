#include "CU.h"
#include "CPU.h"
#include "Memory.h"
#include "ALU.h"

void loadWithPattern(int rIndex, string hexPattern, CPU &cpu) {
    string binPattern = cpu.alu.hexToBin(hexPattern);
    cpu.reg[rIndex].setRegister(binPattern);
}

void loadFromMemory(int registerIndex, string memoryCellAdress, CPU &cpu, Memory &memory) {
    bitset <8> address(cpu.alu.hexToBin(memoryCellAdress));
    int idx = address.to_ullong();
    string binPattern = cpu.alu.hexToBin(memory.getCell(idx));
    cpu.reg[registerIndex].setRegister(binPattern);
}

void store(int rIndex, string memoryAdress, Memory& memory,CPU &cpu){
    ALU alu;
    string binIdx =  alu.hexToBin(memoryAdress);
    bitset <8> bit1(binIdx);
    int idx = bit1.to_ullong();
    string hexPattern = alu.binToHex(cpu.reg[rIndex].getRegister());
    memory.setCell(idx,hexPattern);
}

void move(int S, int R, CPU &cpu){
    cpu.reg[S] = cpu.reg[R];
}

void equalJump(int rIndex, CPU &cpu) {
    if (cpu.reg[0] == cpu.reg[rIndex]) {
        string hexa = "";
        hexa += cpu.IR[2];
        hexa += cpu.IR[3];
        cpu.PC = cpu.alu.hexToDecimal(hexa);
    }
}

void greaterJump(int rIndex, CPU& cpu) {
    if (cpu.reg[0] < cpu.reg[rIndex]) {
        string hexa = "";
        hexa += cpu.IR[2];
        hexa += cpu.IR[3];
        cpu.PC = cpu.alu.hexToDecimal(hexa);
    }

}
