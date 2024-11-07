#include "CPU.h"
#include <bits/stdc++.h>

CPU::CPU() : reg(16), PC(16), IR("") {
    cout << "Please select an option: \n";
    cout << "1: Set PC\n";
    cout << "2: Set PC as default (0x10)\n";
    string choice;
    getline(cin, choice);
    while (choice != "1" && choice != "2") {
        cout << "Invalid choice, please select 1 or 2\n";
        getline(cin, choice);
    }
    if (choice == "1") {
        string hexValue;
        cout << "Please enter a hexadecimal value: ";
        getline(cin, hexValue);
        PC = alu.hexToDecimal(hexValue);  // Convert hexadecimal to decimal and set PC
    } else {
        PC = 0x10;  // Default value if "2" is selected
    }
}

void CPU::showRegisters() {
    for (int i = 0; i < 16; i++) {
        string hexPattern = alu.binToHex(reg[i].getRegister());
        cout << hexPattern << ' ';
    }
    cout << endl;
}

void CPU::setPC() {
    int start;
    cout << "Set the program counter: \n";
    cin >> start;
    if (cin.fail()) {
        cin.clear();  // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        throw invalid_argument("Non-numeric value entered");
    }
    if (start < 0 || start > 255) {
        throw out_of_range("Memory access out of range");
    }
    PC = start;
}
