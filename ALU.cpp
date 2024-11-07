#include <bits/stdc++.h>
#include "CPU.h"
#include "ALU.h"
#include "Register.h"

string AND(int r1Index, int r2Index, CPU &cpu)
{
    string pattern1 = cpu.reg[r1Index].getRegister();
    string pattern2 = cpu.reg[r2Index].getRegister();
    bitset <8> bits1(pattern1), bits2(pattern2);
    return (bits1&bits2).to_string();
}

string OR(int r1Index, int r2Index, CPU& cpu)
{
    string pattern1 = cpu.reg[r1Index].getRegister();
    string pattern2 = cpu.reg[r2Index].getRegister();
    bitset <8> bits1(pattern1), bits2(pattern2);
    return (bits1|bits2).to_string();
}

string XOR(int r1Index, int r2Index, CPU& cpu)
{
    string pattern1 = cpu.reg[r1Index].getRegister();
    string pattern2 = cpu.reg[r2Index].getRegister();
    bitset <8> bits1(pattern1), bits2(pattern2);
    return (bits1^bits2).to_string();
}

void rotate(int rIndex, int times, CPU& cpu)
{
    string pattern1 = cpu.reg[rIndex].getRegister();
    int  sz = pattern1.size(), n = times%sz;
    cpu.reg[rIndex].setRegister(pattern1.substr(sz-times,times) + pattern1.substr(0,sz-times));
}

string hexToBin(const string hex) {
    string bin = "";

    for (char ch : hex) {
        int hexRes;

        if (ch >= '0' && ch <= '9') {
            hexRes = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            hexRes = ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'f') {
            hexRes = ch - 'a' + 10;
        } else {
            cerr << "Invalid hex character: " << ch << endl;
            return "";
        }

        string binSegment = bitset<4>(hexRes).to_string();
        bin += binSegment;
    }
    return bin;
}

string binToHex(string bin)
{
    for (char ch : bin) {
        if (ch != '0' && ch != '1') {
            cerr << "Invalid binary character: " << ch << endl;
            return "";
        }
    }
    string paddedBin =  bin;
    while (paddedBin.size()%4 != 0 ){
        paddedBin.insert(paddedBin.begin(),'0');
    }
    const string table = "0123456789ABCDEF";
    string hex = "";
    for (int i = 0; i < paddedBin.size(); i+=4) {
        string fourBits = paddedBin.substr(i,4);
        int index = stoi(fourBits, nullptr,2);
        hex += table[index];
    }
    return hex;
}
double SEMToDecimal(uint8_t value) {
    int sign = (value >> 7) & 0b1;
    int exponent = (value >> 4) & 0b111;
    exponent -= 4;
    int mantissa = value & 0b1111;

    double mantissaDecimal = 1.0;
    if (mantissa != 0) {
        mantissaDecimal += static_cast<double>(mantissa) / 16.0;
    }
    double result = mantissaDecimal * pow(2, exponent);

    if (sign == 1) {
        result = -result;
    }

    return result;
}
uint8_t DecimalToSEM(double value) {
    if (value == 0) {
        return 0;
    }

    int sign = value < 0 ? 1 : 0;
    value = abs(value);

    int exponent = 0;
    while (value >= 2.0) {
        value /= 2.0;
        exponent++;
    }
    while (value < 1.0) {
        value *= 2.0;
        exponent--;
    }

    int bias = 4;
    exponent += bias;

    if (exponent < 0 || exponent > 7) {
        throw out_of_range("Exponent is out of range for 3 bits.");
    }

    int mantissa = static_cast<int>((value - 1) * 16);
    mantissa &= 0b1111;

    uint8_t result = (sign << 7) | (exponent << 4) | mantissa;

    return result;
}

string addTwoRegistersFloat(int SIndex, int TIndex, int RIndex, CPU &cpu) {
    try {
        uint8_t value1 = static_cast<uint8_t>(bitset<8>(cpu.reg[SIndex].getRegister()).to_ulong());
        uint8_t value2 = static_cast<uint8_t>(bitset<8>(cpu.reg[TIndex].getRegister()).to_ulong());

        double firstValue = SEMToDecimal(value1);
        double secondValue = SEMToDecimal(value2);

        double res = firstValue + secondValue;

        if (res > 15.9375 || res < -15.9375) {
            throw overflow_error("Result exceeds SEM representable range.");
        }

        uint8_t resultSEM = DecimalToSEM(res);
        cpu.reg[RIndex].setRegister(bitset<8>(resultSEM).to_string());
        return cpu.reg[RIndex].getRegister();

    } catch (const overflow_error& e) {
        cerr << "Error: " << e.what() << endl;
        return " Overflow in SEM conversion.";
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return "Error: Unexpected error occurred.";
    }
}

string addTwoRegistersTwosComp(int SIndex, int TIndex, int RIndex, CPU &cpu)
{
    uint8_t Svalue = static_cast<uint8_t>(bitset<8>(cpu.reg[SIndex].getRegister()).to_ulong());
    uint8_t TValue = static_cast<uint8_t>(bitset<8>(cpu.reg[TIndex].getRegister()).to_ulong());
    int16_t result = static_cast<int16_t>(Svalue) + static_cast<int16_t>(TValue);

    // if (result > INT8_MAX || result < INT8_MIN) {
    //     throw overflow_error("Addition overflow in two's complement.");
    // }

    cpu.reg[RIndex].setRegister(bitset<8>(result).to_string());
    return cpu.reg[RIndex].getRegister();

}

int hexToDecimal(const std::string& hex) {
    int decimalValue = 0;
    int base = 1;
    for (int i = hex.length() - 1; i >= 0; --i) {
        char currentChar = hex[i];
        if (currentChar >= '0' && currentChar <= '9') {
            decimalValue += (currentChar - '0') * base;
        } else if (currentChar >= 'A' && currentChar <= 'F') {
            decimalValue += (currentChar - 'A' + 10) * base;
        } else if (currentChar >= 'a' && currentChar <= 'f') {
            decimalValue += (currentChar - 'a' + 10) * base;
        } else {
            cerr << "Invalid hexadecimal character encountered: " << currentChar << endl;
            return -1;
        }
        base *= 16;
    }
    return decimalValue;
}
