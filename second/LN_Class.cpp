#include "LN_Class.h"

LN_Class::LN_Class()
{ 
    this->num.pointer = (unsigned int*)malloc(sizeof(unsigned int)*(1));
	this->num.pointer[0] = 0;
    this->num.size = 1;
}

LN_Class::LN_Class(const LongNumber &right)
{
	num = copy(right);
}

LN_Class::LN_Class(const char* string)
{
	this->num = ReadString(string);
}

LN_Class::LN_Class(const LN_Class &right)
{
	this->num = copy(right.num);
}

LN_Class::LN_Class(const unsigned long long int value)
{
	this->num = ReadNumber(value);
}

LN_Class::~LN_Class()
{
	if (this->num.size) 
		delete[] this->num.pointer;
}

/////////////////////////////////////////////////////////////////////////////

char* LN_Class::__str__()
{
	LN_Class RoRoRo = copy(this->num);
	return PrintNumber(RoRoRo.num);
}

char* LN_Class::__repr__()
{
	LN_Class RoRoRo = copy(this->num);
	return PrintNumber(RoRoRo.num);
}

/////////////////////////////////////////////////////////////////////////////

LN_Class LN_Class::operator=(const LN_Class &right)
{
	this->num = copy(right.num);
	return *this;
}

LN_Class LN_Class::operator+(const LN_Class &right) 
{
	return ADD(this->num, right.num);
}

LN_Class LN_Class::operator-(const LN_Class &right) 
{
	return SUB(this->num, right.num);
}

LN_Class LN_Class::operator*(const LN_Class &right) 
{
	return MUL(this->num, right.num);
}

LN_Class LN_Class::operator/(const LN_Class &right) 
{
	return DIV(this->num, right.num, 1);
}

LN_Class LN_Class::operator%(const LN_Class &right) 
{
	return DIV(this->num, right.num, 2);
}

/////////////////////////////////////////////////////////////////////////////

LN_Class LN_Class::operator+(unsigned long long int value) 
{
	return ADD(this->num, ReadNumber(value));
}

LN_Class LN_Class::operator-(unsigned long long int value) 
{
	return SUB(this->num, ReadNumber(value));
}

LN_Class LN_Class::operator*(unsigned long long int value) 
{
	return MUL(this->num, ReadNumber(value));
}

LN_Class LN_Class::operator/(unsigned long long int value) 
{
	return DIV(this->num, ReadNumber(value), 1);
}

LN_Class LN_Class::operator%(unsigned long long int value) 
{
	return DIV(this->num, ReadNumber(value), 2);
}

/////////////////////////////////////////////////////////////////////////////

void LN_Class::ReadText(const char* filename)
{
	*this = ReadTextFile(filename);
}

void LN_Class::ReadBin(const char* filename)
{
	*this = ReadBinFile(filename);
}

void LN_Class::WriteText(const char* filename)
{
	LN_Class RoRoRo = copy(this->num);
	WriteTextFile(filename, RoRoRo.num);
}

void LN_Class::WriteBin(const char* filename)
{
	LN_Class RoRoRo = copy(this->num);
	WriteBinFile(filename, RoRoRo.num);
}

/////////////////////////////////////////////////////////////////////////////

LN_Class PowMod(LN_Class &base, LN_Class &exp, LN_Class &mod)
{
	return DEGREE(base.num, exp.num, mod.num);
}

LN_Class PowMod(LN_Class &base, LN_Class &exp, unsigned long long int mod)
{
	return DEGREE(base.num, exp.num, ReadNumber(mod));
}

LN_Class PowMod(LN_Class &base, unsigned long long int exp, LN_Class &mod)
{
	return DEGREE(base.num, ReadNumber(exp), mod.num);
}

LN_Class PowMod(unsigned long long int base, LN_Class &exp, LN_Class &mod)
{
	return DEGREE(ReadNumber(base), exp.num, mod.num);
}

LN_Class PowMod(LN_Class &base, unsigned long long int exp, unsigned long long int mod)
{
	return DEGREE(base.num, ReadNumber(exp), ReadNumber(mod));
}

LN_Class PowMod(unsigned long long int base, LN_Class &exp, unsigned long long int mod)
{
	return DEGREE(ReadNumber(base), exp.num, ReadNumber(mod));
}

LN_Class PowMod(unsigned long long int base, unsigned long long int exp, LN_Class &mod)
{
	return DEGREE(ReadNumber(base), ReadNumber(exp), mod.num);
}
