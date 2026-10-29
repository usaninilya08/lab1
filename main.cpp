#include "memory_lab.h"
#include <limits>

int main() {
    printTypeSizes();

    printIntBits(42);
    printIntBits(-42);
    printIntBits(0);
    printIntBits(2147483647);
    printIntBits(-2147483647 - 1);
    std::cout << "\n";

    printFloatBits(3.14159f);
    printFloatBits(-2.5f);
    printFloatBits(0.0f);
    
    float denormal = 1.4e-45f;
    printFloatBits(denormal);

    float inf = std::numeric_limits<float>::infinity();
    printFloatBits(inf);

    printDoubleBits(3.141592653589793);
    printDoubleBits(-2.5);
    std::cout << "\n";

    int num = 8;
    printIntBits(num);

    num = modifyBit32(num, 0, BitOp::SET);
    printIntBits(num);

    num = modifyBit32(num, 3, BitOp::CLEAR);
    printIntBits(num);

    num = modifyBit32(num, 1, BitOp::FLIP);
    printIntBits(num);

    float positiveVal = 5.75f;
    printFloatBits(positiveVal);
    float invertedSignVal = modifyFloatBit(positiveVal, 31, BitOp::FLIP);
    printFloatBits(invertedSignVal);

    uint32_t testVal = 0b10110100;
    printIntBits(testVal);
    std::cout << "Bits set: " << countSetBitsKernighan(testVal) << "\n";

    return 0;
}