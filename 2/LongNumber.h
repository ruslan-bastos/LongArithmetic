#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 4294967296

struct LongNumber
{
    unsigned int size;
    unsigned int* pointer;
};

LongNumber ReadBinFile(const char* file);
void WriteBinFile(const char* file, LongNumber number);

LongNumber ReadTextFile(const char* file);
void WriteTextFile(const char* file, LongNumber number);

LongNumber ADD(LongNumber a, LongNumber b);
LongNumber SUB(LongNumber a, LongNumber b);
LongNumber MUL(LongNumber a, LongNumber b);

LongNumber DIV(LongNumber a, LongNumber b, int sumbols);
LongNumber SmallMul(LongNumber a, unsigned long long int b);
LongNumber shiftLeft(LongNumber a, unsigned int s);

LongNumber DEGREE(LongNumber a, LongNumber b, LongNumber c);
LongNumber SmallDIV(LongNumber a, unsigned long long int b);

LongNumber clear(LongNumber number);
LongNumber allocate(LongNumber number, unsigned int size);
LongNumber zero(LongNumber number, unsigned int size);

int compare(LongNumber a, LongNumber b);
LongNumber copy(LongNumber from);
LongNumber Normalize(LongNumber a);
