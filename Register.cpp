#include "Register.h"
#include <cmath>

Register::Register() { content = "00000000"; }

string Register::getRegister() { return content; }

void Register::clearRegister() { content = "00000000"; }

bool Register::operator==(Register reg) {
    return (content == reg.content);
}

int Register::twosComplementToDecimal(string binary) {
    int decimalValue = 0;
    int length = binary.size();
    bool negative = (binary[0] == '1');

    if (negative) {
        for (int i = 0; i < length; ++i) {
            if (binary[i] == '0') {
                decimalValue += pow(2, length - i - 1);
            }
        }
        decimalValue = -(decimalValue + 1);
    } else {
        for (int i = 0; i < length; ++i) {
            if (binary[i] == '1') {
                decimalValue += pow(2, length - i - 1);
            }
        }
    }

    return decimalValue;
}

bool Register::operator<(Register reg) {
    int firstValue = twosComplementToDecimal(content);
    int secondValue = twosComplementToDecimal(reg.content);
    return (firstValue < secondValue);
}

void Register::setRegister(string value) {
    content = value;
}
