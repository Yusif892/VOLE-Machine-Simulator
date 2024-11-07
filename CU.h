#ifndef CU_H
#define CU_H

#include <string>
#include "CPU.h"
#include "Memory.h"
#include "ALU.h"

class CU {
public:
    void loadWithPattern(int rIndex, std::string hexPattern, CPU &cpu);
    void loadFromMemory(int registerIndex, std::string memoryCellAdress, CPU &cpu, Memory &memory);
    void store(int rIndex, std::string memoryAdress, Memory& memory, CPU &cpu);
    void move(int S, int R, CPU &cpu);
    void equalJump(int rIndex, CPU &cpu);
    void greaterJump(int rIndex, CPU& cpu);
};

#endif
