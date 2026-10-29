#include "memory_lab.h"

void printTypeSizes() {
    std::cout << std::left << std::setw(15) << "Type" 
              << std::setw(10) << "Size" << "Notes\n";
    std::cout << "------------------------------------------\n";
    std::cout << std::setw(15) << "bool" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(15) << "char" << sizeof(char) << " bytes\n";
    std::cout << std::setw(15) << "short int" << sizeof(short) << " bytes\n";
    std::cout << std::setw(15) << "int" << sizeof(int) << " bytes\n";
    std::cout << std::setw(15) << "long int" << sizeof(long) << " bytes\n";
    std::cout << std::setw(15) << "long long" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(15) << "float" << sizeof(float) << " bytes\n";
    std::cout << std::setw(15) << "double" << sizeof(double) << " bytes\n";
    std::cout << std::setw(15) << "long double" << sizeof(long double) << " bytes\n\n";
}

void printIntBits(int32_t value) {
    uint32_t raw;
    std::memcpy(&raw, &value, sizeof(value));

    std::cout << "Value: " << std::setw(11) << value << " | Bits: [";
    int signBit = (raw >> 31) & 1;
    std::cout << signBit << "] ";

    for (int i = 30; i >= 0; --i) {
        std::cout << ((raw >> i) & 1);
        if (i > 0 && i % 4 == 0) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

void printFloatBits(float value) {
    uint32_t raw;
    std::memcpy(&raw, &value, sizeof(value));

    uint32_t sign = (raw >> 31) & 0x1;
    uint32_t exponent = (raw >> 23) & 0xFF;
    uint32_t mantissa = raw & 0x7FFFFF;

    std::cout << "float: " << value << "\n";
    std::cout << "  sign     : " << sign << "\n";
    std::cout << "  exponent : ";
    for (int i = 7; i >= 0; --i) {
        std::cout << ((exponent >> i) & 1);
    }
    std::cout << " (" << (int)exponent - 127 << ")\n";

    std::cout << "  mantissa : ";
    for (int i = 22; i >= 0; --i) {
        std::cout << ((mantissa >> i) & 1);
        if (i % 4 == 0 && i > 0) std::cout << ' ';
    }
    std::cout << "\n  raw      : [" << sign << "] [";
    for (int i = 7; i >= 0; --i) std::cout << ((exponent >> i) & 1);
    std::cout << "] [";
    for (int i = 22; i >= 0; --i) std::cout << ((mantissa >> i) & 1);
    std::cout << "]\n\n";
}

void printDoubleBits(double value) {
    uint64_t raw;
    std::memcpy(&raw, &value, sizeof(value));

    uint64_t sign = (raw >> 63) & 0x1;
    uint64_t exponent = (raw >> 52) & 0x7FF;
    uint64_t mantissa = raw & 0x000FFFFFFFFFFFFFULL;

    std::cout << "double: " << value << "\n";
    std::cout << "  sign     : " << sign << "\n";
    std::cout << "  exponent : ";
    for (int i = 10; i >= 0; --i) {
        std::cout << ((exponent >> i) & 1);
    }
    std::cout << " (" << (int64_t)exponent - 1023 << ")\n";

    std::cout << "  mantissa : ";
    for (int i = 51; i >= 0; --i) {
        std::cout << ((mantissa >> i) & 1);
        if (i % 8 == 0 && i > 0) std::cout << ' ';
    }
    std::cout << "\n  raw      : [" << sign << "] [";
    for (int i = 10; i >= 0; --i) std::cout << ((exponent >> i) & 1);
    std::cout << "] [";
    for (int i = 51; i >= 0; --i) std::cout << ((mantissa >> i) & 1);
    std::cout << "]\n\n";
}

uint32_t modifyBit32(uint32_t value, int bitIndex, BitOp op) {
    if (bitIndex < 0 || bitIndex > 31) return value;
    switch (op) {
        case BitOp::SET:   return value | (1U << bitIndex);
        case BitOp::CLEAR: return value & ~(1U << bitIndex);
        case BitOp::FLIP:  return value ^ (1U << bitIndex);
    }
    return value;
}

uint64_t modifyBit64(uint64_t value, int bitIndex, BitOp op) {
    if (bitIndex < 0 || bitIndex > 63) return value;
    switch (op) {
        case BitOp::SET:   return value | (1ULL << bitIndex);
        case BitOp::CLEAR: return value & ~(1ULL << bitIndex);
        case BitOp::FLIP:  return value ^ (1ULL << bitIndex);
    }
    return value;
}

float modifyFloatBit(float value, int bitIndex, BitOp op) {
    uint32_t raw;
    std::memcpy(&raw, &value, sizeof(value));
    raw = modifyBit32(raw, bitIndex, op);
    float result;
    std::memcpy(&result, &raw, sizeof(result));
    return result;
}

double modifyDoubleBit(double value, int bitIndex, BitOp op) {
    uint64_t raw;
    std::memcpy(&raw, &value, sizeof(value));
    raw = modifyBit64(raw, bitIndex, op);
    double result;
    std::memcpy(&result, &raw, sizeof(result));
    return result;
}

int countSetBitsKernighan(uint32_t value) {
    int count = 0;
    while (value > 0) {
        value &= (value - 1);
        count++;
    }
    return count;
}