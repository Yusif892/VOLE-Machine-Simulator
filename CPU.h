#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <string>
#include "Register.h"
#include "ALU.h"
#include "CU.h"

using namespace std;

class CPU {
public:
    CU cu;
    vector<Register> reg;
    string IR;
    ALU alu;
    int PC;
    CPU();
    void showRegisters();
    void setPC();
};

#endif // CPU_H
