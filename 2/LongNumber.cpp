#include "LongNumber.h"

LongNumber ReadBinFile(const char* file)
{
	FILE* in = fopen(file, "rb");
	LongNumber number;
	number.size = 0;

	fseek(in, 0, SEEK_END);
	unsigned int quotient, remainder, size = ftell(in);

	quotient = size / sizeof(unsigned int);
	remainder = size % sizeof(unsigned int);

	if(remainder==0)
		number = allocate(number, quotient);
	else
		number = allocate(number, quotient+1);

	fseek(in, SEEK_SET, 0);  //переход на начало строки

	for (int i = 0; i < quotient; i++)
		fread(&number.pointer[i], sizeof(unsigned int), 1, in);

	number.size = quotient;

	if (remainder != 0)
	{
		unsigned char ch;
		number.size++;
		number.pointer[quotient] = 0;
		for(int j = 0; j<remainder; j++)
		{
			fread(&ch, sizeof(unsigned char), 1, in);
			number.pointer[quotient] |= (ch << j*8);
		}
	}

	fclose(in);		

	return number;
}

void WriteBinFile(const char* file, LongNumber number)
{
	FILE* out = fopen(file,"wb");

	for (int i = 0 ; i < number.size; i++)
		fwrite(&number.pointer[i], sizeof(unsigned int), 1, out);

	fclose(out);
}

LongNumber ReadTextFile(const char* file)
{
	LongNumber bin, number;
	char ch;

	number.size = 0;

	FILE *in = fopen(file, "r");

	fseek(in, 0, SEEK_END);
	number.size = ftell(in);

	fseek(in, SEEK_SET, 0);  //переход на начало строки

	number = allocate(number, number.size);
	number = zero(number, number.size);

	bin.size = number.size / 9 + 1;

	bin = allocate(bin, bin.size);
	bin = zero(bin, bin.size);

	unsigned int a, carry = 0, tmp, current, j, x;

	long long int i = number.size-1;

	while((ch = getc(in))!=EOF)
		number.pointer[i--] = ch - '0';

	fclose(in);
	
	current = 1;
	j = 0;
	x = 0;

	while (number.size != 1 || number.pointer[0]!=0)
	{
		carry = 0;

		for (i = number.size - 1; i >= 0; i--)
		{
			tmp = carry * 10 + number.pointer[i];
			number.pointer[i] = tmp / 2;
			carry = tmp - number.pointer[i] * 2;
		}

		number = Normalize(number);

		bin.pointer[j] = ((current << x) * carry) | bin.pointer[j];

		x++;

		if(x == 32)
		{
			x = 0;
			j++;
		}
	}

	number = clear(number);

	bin = Normalize(bin);

	return bin;
}

void WriteTextFile(const char* file, LongNumber number)
{
	FILE* out = fopen(file, "w");

	LongNumber decimal;

	decimal.size = number.size*10;

	decimal = allocate(decimal, decimal.size);
	decimal = zero(decimal, decimal.size);

	unsigned int a, j = 0;
	long long int tmp, i = number.size-1;
	char carry =0;

	while (number.size != 1 || number.pointer[0]!=0)
	{
		carry = 0;

		for (i = number.size - 1; i >= 0; i--)
		{
			tmp = carry * BASE + number.pointer[i];
			number.pointer[i] = tmp / 10;
			carry = tmp - (long long int) number.pointer[i] * 10;
		}

		carry += '0';

		decimal.pointer[j] = carry;
		j++;

		number = Normalize(number);
	}

	decimal = Normalize(decimal);

	for (int i = decimal.size - 1 ; i > -1; i--)
			fprintf(out, "%c", decimal.pointer[i]);

	fclose(out);
}

LongNumber clear(LongNumber number)
{
	free(number.pointer);
	return number;
}

LongNumber allocate(LongNumber number, unsigned int size)
{
	number.pointer = (unsigned int*)malloc(sizeof(unsigned int)*(size));
	return number;
}

LongNumber zero(LongNumber number, unsigned int size)
{
	memset(number.pointer, 0, size * sizeof(unsigned int));
	return number;
}

LongNumber copy(LongNumber from)
{
    LongNumber cpy;

    cpy.size = from.size;
    cpy = allocate(cpy, cpy.size);
    memcpy(cpy.pointer, from.pointer, cpy.size * sizeof(unsigned int));

    return cpy;
}

int compare(LongNumber a, LongNumber b)  // функция сравнения двух больших чисел
{   
	// функция возвращает: 0 - если числа равны, >0 - если A больше, <0 - если A меньше.
	
	if(a.size > b.size)
		return 1;

	if(a.size < b.size)
		return -1;

	int i = a.size - 1;

	while (a.pointer[i] == b.pointer[i] && i > 0)
		i--;
	
	if(a.pointer[i] > b.pointer[i])
		return 1;

	if(a.pointer[i] < b.pointer[i])
		return -1;

	if(a.pointer[i] == b.pointer[i])
		return 0;
}

LongNumber ADD(LongNumber a, LongNumber b)
{
	unsigned long long int tmp;
	unsigned int carry = 0, i;
	LongNumber res;

	if (a.size < b.size)
	{
		return ADD(b,a);
	}

	res.size = a.size + 1;
	res = allocate(res, res.size);
	res = zero(res, res.size);

	for (i=0; i<b.size; i++) 
	{
		tmp = (unsigned long long int) a.pointer[i] + (unsigned long long int) b.pointer[i] + (unsigned long long int) carry;
		if (tmp >= BASE) 
		{ 
			res.pointer[i] = tmp - BASE;
			carry = 1;
		} 
		else 
		{
			res.pointer[i] = tmp;
			carry = 0;
		}
	}

	for (; i < a.size; i++) 
	{
		tmp = (unsigned long long int) a.pointer[i] + (unsigned long long int) carry;

		if (tmp >= BASE) 
		{
			res.pointer[i] = tmp - BASE;
			carry = 1;
		} 
		else 
		{
			res.pointer[i] = tmp;
			carry = 0;
		}
	}

	if (carry==1) 
	{
		res.pointer[i] = carry;
		res.size = a.size + 1;
	}
	else
		res.size = a.size;

	return res;
}

LongNumber SUB(LongNumber a, LongNumber b)
{
	long long int tmp;
	unsigned int carry = 0, i;
	LongNumber res;

	if (compare(a, b) < 0)
	{
		res = SUB(b,a);
		return res;
	}

	res.size = a.size;
	res = allocate(res, res.size);
	res = zero(res, res.size);

	for (i=0; i<b.size; i++) 
	{
		tmp = (long long int)a.pointer[i] - (long long int) b.pointer[i] - (long long int) carry;

		if (tmp < 0) 
		{
			res.pointer[i] = tmp + BASE;
			carry = 1;
		} 
		else 
		{
			res.pointer[i] = tmp;
			carry = 0;
		}
	}

	for (; i<a.size; i++) 
	{
		tmp = a.pointer[i] - carry;

		if (tmp < 0) 
		{
			res.pointer[i] = tmp + BASE;
			carry = 1;
		} 
		else 
		{
			res.pointer[i] = tmp;
			carry = 0;
		}
	}

	res = Normalize(res);

	return res;
}

LongNumber MUL(LongNumber a, LongNumber b)
{
	unsigned long long int tmp;
	unsigned int carry = 0, i, j;

	LongNumber res;

    res.size = a.size + b.size;
    res = allocate(res, res.size);
    res = zero(res, res.size); //заполняет массив нулями

    for (i = 0; i < b.size; i++)
    {
        carry = 0;

        for (j = 0; j < a.size; j++)
        {
            tmp = (unsigned long long int) b.pointer[i] * (unsigned long long int) a.pointer[j] + carry + res.pointer[i + j];
            carry = tmp / BASE;
            res.pointer[i + j] = tmp % BASE;
        }
        res.pointer[i + a.size] = carry;
    }

    res = Normalize(res);

    return res;
}

LongNumber DIV(LongNumber a, LongNumber b, int sumbols)
{
	LongNumber remainder; // остаток от деления

    if (compare(a, b) < 0)  // если делимое меньше делителя
    {
        LongNumber res;
        res.size = 1;
        res = allocate(res, res.size);
        res.pointer[0] = 0;

		if(sumbols == 1)
			return res;
		else
			return a;
    }

    if (b.size == 1)  // если необходимо делить на одноразрядное число
    {
		if (b.pointer[0] == 0) // если делитель равен нулю
        {
            remainder.size = 0;
            remainder.pointer = NULL;

            return remainder;
        }

		LongNumber res = SmallDIV(a, b.pointer[0]);

        remainder = SUB(a, SmallMul(res,b.pointer[0]));

        if(sumbols == 1)
			return res;
		else
			return remainder;
    }

    // деление на многоразрядное число
	
	remainder = copy(a);

    LongNumber res;
    res.size = a.size - b.size + 1;
    res = allocate(res, res.size);
	res = zero(res, res.size); //заполняет массив нулями

    unsigned int i;
	
    for (i = a.size - b.size + 1; i != 0; i--)
    {
        unsigned long long int qGuessMax = BASE, qGuessMin = 0, qGuess; 
		
        // цикл - подбор бинарным поиском числа qGuess
        while (qGuessMax - qGuessMin > 1)
        {
            qGuess = (qGuessMax + qGuessMin) / 2;
			
            // получаем tmp = qGuess * divider * BASE^i;
            LongNumber tmp = SmallMul(b, qGuess);
            tmp = shiftLeft(tmp, i - 1);    // сдвигает число на (i - 1) разрядов влево
            if (compare(tmp, remainder) > 0)
                qGuessMax = qGuess;
            else
                qGuessMin = qGuess;
            
            tmp = clear(tmp);
        }

        // получаем tmp = qGuessMin * divider * BASE ^ (i - 1) 
        LongNumber tmp = SmallMul(b, qGuessMin);
        tmp = shiftLeft(tmp, i - 1);
		
        //получаем remainder = remainder - tmp;
        remainder = SUB(remainder, tmp);

		tmp = clear(tmp);
        
        res.pointer[i - 1] = qGuessMin;
    }

	////////////////////////////////////////////////////////////////

	remainder = Normalize(remainder);

	////////////////////////////////////////////////////////////////

	res = Normalize(res);

	////////////////////////////////////////////////////////////////

    if(sumbols == 1)
		return res;
	else
		return remainder;
}

LongNumber SmallMul(LongNumber a, unsigned long long int b)
{
	unsigned long long int tmp, carry = 0;
	unsigned int i, j;

	LongNumber res;

    res.size = a.size + 1;
    res = allocate(res, res.size);
    res = zero(res, res.size); //заполняет массив нулями

	carry = 0;

	for (j = 0; j < a.size; j++)
	{
		tmp = b * (unsigned long long int) a.pointer[j] + carry + res.pointer[j];
		carry = tmp / BASE;
        res.pointer[j] = tmp % BASE;
    }

    res.pointer[a.size] = carry;

    res = Normalize(res);

    return res;
}

LongNumber shiftLeft(LongNumber a, unsigned int s) // сдвигает число a на s разрядов влево
{
    LongNumber current;
	
	current.size = a.size + s;
	current = allocate(current, current.size);
	current = zero(current, s);

	for(int i = s; i < a.size + s; i++)
		current.pointer[i] = a.pointer[i-s];

    return current;
}

LongNumber DEGREE(LongNumber a, LongNumber b, LongNumber c)
{ 
	LongNumber res;
	if(a.size < c.size)
		res.size = c.size + c.size;
	else
		res.size = a.size + a.size;

	res = allocate(res, res.size);
    res = zero(res, res.size); //заполняет массив нулями
	res.pointer[0] = 1;

	LongNumber com;
	com.size = 1;
	com = allocate(com, com.size);
	com.pointer[0] = 0;

	LongNumber value;
	value.size = res.size;
	value = allocate(value, value.size);
    value = zero(value, value.size); //заполняет массив нулями

	memcpy(value.pointer, a.pointer, a.size * sizeof(unsigned int));

	LongNumber pow = copy(b);

	while((compare(pow,com)) > 0)
	{
		if((pow.pointer[0] & 1)==1)
		{
			res = MUL(res, value);
			res = DIV(res, c, 2);
		}

		value = MUL(value, value);
		value = DIV(value, c, 2);
		pow = SmallDIV(pow, 2);
	}

	com = clear(com);
	pow = clear(pow);
	value = clear(value);

	return res;
}

LongNumber SmallDIV(LongNumber a, unsigned long long int b)
{
		unsigned long long int tmp;
		unsigned int carry = 0;
		int i;

        LongNumber res;
        res.size = a.size;
        res = allocate(res, res.size);
		res = zero(res, res.size); //заполняет массив нулями

        for (i = a.size - 1; i > -1; i--)
        {	
            tmp = (unsigned long long int) carry * BASE + a.pointer[i];
            res.pointer[i] = tmp / b;
            carry = tmp - (unsigned long long int) res.pointer[i] * (unsigned long long int) b;
        }

        res = Normalize(res);

		return res;
}

LongNumber Normalize(LongNumber a)
{
	unsigned int i = a.size-1;

	while ( (i>0) && (a.pointer[i]==0) ) 
		i--;

	a.size = i+1;

	return a;
}




