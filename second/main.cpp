#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LN_Class.h"

int main(int argc, const char * argv[])
{
	if (argc < 5) 
	{
        printf("Error: Too few arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename>\n");
        return 0;
    }
    
    if (argc > 7) 
	{
        printf("Error: Too many arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename> <module_long_number_filename> <-b>\n");
        return 0;
    }
    
    FILE* firstLongNumFile = fopen(argv[1], "r");
    if (!firstLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[1]);
        return 0;
    }
	fclose(firstLongNumFile);

    const char* operation = argv[2];
    if ((strlen(operation) > 1 || operation[0] == '\0') || operation[0] != '+' && operation[0] != '-' && operation[0] != '*' && operation[0] != '/' && operation[0] != '%' && operation[0] != '^') 
	{
        printf("Error: Wrong operation: %s \n", operation);
        return 0;
    }
    
    FILE* secondLongNumFile = fopen(argv[3], "r");
    if (!secondLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[3]);
        return 0;
    }
    fclose(secondLongNumFile);

	FILE* resultLongNumFile = fopen(argv[4], "r");
    if (!resultLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[4]);
        return 0;
    }
    fclose(resultLongNumFile);

	////////////////////////////////////////////////////////////////////////////////

	int bin = 0;

	if (argc == 5)
		if (argv[2][0] == '^')
		{
			printf("Error: Input module file\n");
			return 0;
		}

    if (argc == 6) 
	{
		if (argv[2][0] == '^')
		{
			FILE* moduleLongNumFile = fopen(argv[5], "r");
			if (!moduleLongNumFile) 
			{
				printf("Error: Unable to open file: %s \n", argv[5]);
				return 0;
			}
			fclose(moduleLongNumFile);
		}
		else
		{
			if (strcmp(argv[5], "-b")) 
			{
				printf("Error: Invalid flag: %s \n", argv[5]);
				return 0;
			}
			bin = 1;
		}
		
    }

	if (argc == 7) 
	{
		FILE* moduleLongNumFile = fopen(argv[5], "r");
		if (!moduleLongNumFile) 
		{
			printf("Error: Unable to open file: %s \n", argv[5]);
			return 0;
		}
		fclose(moduleLongNumFile);

        if (strcmp(argv[6], "-b")) 
		{
            printf("Error: Invalid flag: %s \n", argv[6]);
            return 0;
        }
		bin = 1;
    }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	LN_Class a,b;

    //upload first large number--------------------------------------------------------------------------------------
	if(bin == 1)
		a.ReadBin(argv[1]);
	else
		a.ReadText(argv[1]);
    
    //upload second large number-------------------------------------------------------------------------------------
	if(bin == 1)
		b.ReadBin(argv[3]);
	else
		b.ReadText(argv[3]);
    
    //perform chosen operation----------------------------------------------------------------------------------------

    LN_Class result;
    
    switch (operation[0]) {
        case '+':
        {
            result = a + b;
            break;
        }
        case '-':
        {
            result = a - b;
            break;
        }
        case '*':
        {
            result = a * b;
            break;
        }
        case '/':
        {
            result = a / b;
            break;
        }
        case '%':
        {
            result = a % b;
            break;
        }
        case '^':
        {
			LN_Class c;
            if(bin == 1)
				c.ReadBin(argv[5]);
			else
				c.ReadText(argv[5]);

			result = PowMod(a, b, c);
            break;
        }
        default:
            break;
    }    
       
    //save result long number----------------------------------------------------------------------------------------
	if (bin == 1)
		result.WriteBin(argv[4]);
	else
		result.WriteText(argv[4]);

	return 0;
}