#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>
using namespace std;

class Memory {
private:
    vector<string> cells;

public:
    Memory();
    void setCell(int index, string value);
    string getCell(int index);
    void clear();
    void display();
};

#endif // MEMORY_H
