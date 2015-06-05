#include "LongNumber.h"

class LN_Class
{
	LongNumber num;

public:

	LN_Class();
	LN_Class(const char *string);
	LN_Class(const LN_Class &right);
	LN_Class(const LongNumber &right);
	LN_Class(const unsigned long long int value);
	~LN_Class();

	char* __str__();
	char* __repr__();

	LN_Class operator=(const LN_Class &right);
	LN_Class operator+(const LN_Class &right);
	LN_Class operator-(const LN_Class &right);
	LN_Class operator*(const LN_Class &right);
	LN_Class operator/(const LN_Class &right);
	LN_Class operator%(const LN_Class &right);

	LN_Class operator+(unsigned long long int value);
	LN_Class operator-(unsigned long long int value);
	LN_Class operator*(unsigned long long int value);
	LN_Class operator/(unsigned long long int value);
	LN_Class operator%(unsigned long long int value);

	void ReadText(const char *filename);
	void WriteText(const char *filename);
	void ReadBin(const char *filename);
	void WriteBin(const char *filename);

	friend LN_Class PowMod(LN_Class &base, LN_Class &exp, LN_Class &mod); // res = LN_Class.PowMod(a,b,c)
	friend LN_Class PowMod(LN_Class &base, LN_Class &exp, unsigned long long int mod);
	friend LN_Class PowMod(LN_Class &base, unsigned long long int exp, LN_Class &mod);
	friend LN_Class PowMod(unsigned long long int base, LN_Class &exp, LN_Class &mod);
	friend LN_Class PowMod(LN_Class &base, unsigned long long int exp, unsigned long long int mod);
	friend LN_Class PowMod(unsigned long long int base, LN_Class &exp, unsigned long long int mod);
	friend LN_Class PowMod(unsigned long long int base, unsigned long long int exp, LN_Class &mod);
};
