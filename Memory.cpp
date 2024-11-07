#include "Memory.h"
#include <iostream>
#include <stdexcept>

Memory::Memory() : cells(256) {
    for (int i = 0; i < 256; i++) {
        cells[i] = "00";
    }
}

void Memory::setCell(int index, string value) {
    if (index < 0 || index > 255) {
        throw out_of_range("Memory access out of range");
    }
    cells[index] = value;
}

string Memory::getCell(int index) {
    if (index < 0 || index > 255) {
        throw out_of_range("Memory access out of range");
    }
    return cells[index];
}

void Memory::clear() {
    for (int i = 0; i < 256; i++) {
        cells[i] = "00";
    }
}

void Memory::display() {
    for (int i = 0; i < 256; i++) {
        cout << cells[i] << ' ';
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
}
