#include <bits/stdc++.h>
#include "Machine.h"
using namespace std;

int main() {
    cout << "welcome to the VOLE Machine simulator\n";
    cout << "Please select an option:\n";
    cout << "1:Run the program as whole\n";
    cout << "2:Run a step by step program\n";
    string option;
    getline(cin,option);
    while (option != "1" && option != "2") {
        cout << "Invalid option please try again: \n";
        getline(cin,option);
    }
    cout << "\n========================\n";
    Machine VOLE;
    VOLE.readInstructions();
    option == "1" ? VOLE.fetch() : VOLE.fetch(true);
    cout << "Final memory status: \n\n";
    VOLE.displayMemory();
    cout << "========================\n";
    cout << "Final registers status: \n\n";
    VOLE.displayRegisters();
    cout << "\n========================\n";
    cout << "Thanks for using the program, good bye";
}
// g++ Main.cpp Machine.cpp -o main