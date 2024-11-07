#ifndef MACHINE_H
#define MACHINE_H

#include <bits/stdc++.h>
#include "CPU.h"
#include "Memory.h"

class Machine {
private:
    std::string hexScreenOutput;
    std::string ASCIIScreenOutput;
    CPU processor;
    Memory RAM;

public:
    Machine();
    void readInstructions();
    void displayMemory();
    void displayRegisters();
    bool fileExists(const std::string& filename);
    std::string InputFilePath();
    void fetch(bool stepByStep);
    void decode();
};

#endif
