#include "LN_Class.h"


LN_Class& LN_Class::operator=(const LN_Class& right)
{
	this->num = copy(right.num);
	return *this;
}

LN_Class LN_Class::operator+(LN_Class &right) 
{
	LN_Class res;
	res.num = ADD(this->num, right.num);
	return res;
}

LN_Class LN_Class::operator-(LN_Class &right) 
{
	LN_Class res;
	res.num = SUB(this->num, right.num);
	return res;;
}

LN_Class LN_Class::operator*(LN_Class &right) 
{
	LN_Class res;
	res.num = MUL(this->num, right.num);
	return res;
}

LN_Class LN_Class::operator/(LN_Class &right) 
{
	LN_Class res;
	res.num = DIV(this->num, right.num, 1);
	return res;
}

LN_Class LN_Class::operator%(LN_Class &right) 
{
	LN_Class res;
	res.num = DIV(this->num, right.num, 2);
	return res;
}

void LN_Class::ReadText(const char* filename)
{
	LN_Class res;
	res.num = ReadTextFile(filename);
	*this = res;
}

void LN_Class::ReadBin(const char* filename)
{
	LN_Class res;
	res.num = ReadBinFile(filename);
	*this = res;
}

void LN_Class::WriteText(const char* filename)
{
	WriteTextFile(filename, this->num);
}

void LN_Class::WriteBin(const char* filename)
{
	WriteBinFile(filename, this->num);
}

void LN_Class::ClearMemory()
{
	free((*this).num.pointer);
}

LN_Class PowMod(LN_Class &base, LN_Class &exp, LN_Class &mod)
{
	LN_Class res;
	res.num = DEGREE(base.num, exp.num, mod.num);
	return res;
}