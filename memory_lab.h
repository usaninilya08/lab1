#pragma once

#include <iostream>
#include <cstdint>
#include <cstring>
#include <iomanip>

enum class BitOp {
    SET,
    CLEAR,
    FLIP
};

void printTypeSizes();
void printIntBits(int32_t value);
void printFloatBits(float value);
void printDoubleBits(double value);

uint32_t modifyBit32(uint32_t value, int bitIndex, BitOp op);
uint64_t modifyBit64(uint64_t value, int bitIndex, BitOp op);

float modifyFloatBit(float value, int bitIndex, BitOp op);
double modifyDoubleBit(double value, int bitIndex, BitOp op);

int countSetBitsKernighan(uint32_t value);