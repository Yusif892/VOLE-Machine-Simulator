#ifndef ALU_H
#define ALU_H

#include <bits/stdc++.h>
#include "CPU.h"
class CPU;
class ALU {
public:
    std::string AND(int r1Index, int r2Index, CPU &cpu);
    std::string OR(int r1Index, int r2Index, CPU &cpu);
    std::string XOR(int r1Index, int r2Index, CPU &cpu);
    void rotate(int rIndex, int times, CPU &cpu);
    std::string hexToBin(const std::string hex);
    std::string binToHex(std::string bin);
    double SEMToDecimal(uint8_t value);
    uint8_t DecimalToSEM(double value);
    std::string addTwoRegistersFloat(int SIndex, int TIndex, int RIndex, CPU &cpu);
    std::string addTwoRegistersTwosComp(int SIndex, int TIndex, int RIndex, CPU &cpu);
    int hexToDecimal(const std::string& hex);
};

#endif
