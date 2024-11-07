#ifndef REGISTER_H
#define REGISTER_H

#include <string>
using namespace std;

class Register {
private:
    string content;

public:
    Register();
    string getRegister();
    void clearRegister();
    bool operator==(Register reg);
    int twosComplementToDecimal(string binary);
    bool operator<(Register reg);
    void setRegister(string value);
};

#endif // REGISTER_H
