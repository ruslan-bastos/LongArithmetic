#include "LongNumber.h"

class LN_Class
{
	LongNumber num;

public:

	LN_Class() {} // конструктор по умолчанию, вызывается без аргументов

	// операторы
	LN_Class& operator=(const LN_Class& rhv); // оператор присвания
	LN_Class operator+(LN_Class &right);
	LN_Class operator-(LN_Class &right);
	LN_Class operator*(LN_Class &right);
	LN_Class operator/(LN_Class &right);
	LN_Class operator%(LN_Class &right);

	// методы
	void ReadText(const char* filename);
	void WriteText(const char* filename);
	void ReadBin(const char* filename);
	void WriteBin(const char* filename);
	void ClearMemory();

	friend LN_Class PowMod(LN_Class &base, LN_Class &exp, LN_Class &mod); // дружественная функция
};
