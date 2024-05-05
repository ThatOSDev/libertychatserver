
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096
#define MAX_LENGTH 22

char* charStr             = NULL;
char** strings            = NULL;
unsigned int stringsIndex = 0;
uint64_t                j = 0;

unsigned int that_getTotalStrings()
{
    return stringsIndex;
}

void printDoubles(double doubleNum, int numLength)
{
    int floatLength = (size_t)snprintf(NULL, 0, "%.15lf", doubleNum) + 1;
    char str[20];
    snprintf(str, floatLength, "%.15g", doubleNum);
    int t = (numLength + floatLength);
    charStr = realloc(charStr, sizeof(char) * t);
    for(int b = 0; j < t; j++, b++)
    {
        charStr[j] = str[b];
    }
    j++;
}

void printUInt64Digits(uint64_t num, uint64_t base, int numLength)
{
	const char* digits = "0123456789ABCDEF";
	uint64_t b = 0;
	char tempChar[64] = {'\0'};

	do
	{
		tempChar[b++] = digits[num % base];
        num /= base;
	} while(num > 0);

    tempChar[b--] = '\0';

    int t = numLength + b;
    charStr = realloc(charStr, sizeof(char) * t);

	for(uint64_t a = 0; a < b; a++, b--)
	{
		char  temp = tempChar[b];
		tempChar[b] = tempChar[a];
		tempChar[a] = temp;
	}

    b = 0;
    for(; j < t; j++, b++)
    {
        charStr[j] = tempChar[b];
    }
    j++;
}

void that_addString(const char* txt, ...)
{
	if(charStr != NULL)
    {
        free(charStr);
    }
	int len = strnlen(txt, MAX_STRING_LENGTH);
	charStr = malloc(sizeof(char) * (len + 1));

	va_list args;
	va_start(args, txt);
	uint64_t i = 0;
	j = 0;

	for(; txt[i] != '\0'; i++)
	{
		if(txt[i] == '%')
		{
			i++;
			switch(txt[i])
			{
                case 'c':
                {
                    j = (i - 1);
                    char* varString = va_arg(args, char*);
                    charStr = realloc(charStr, len + 1);
                    charStr[j] = *varString;
                    j++;
					break;
                }
				case 's':
				{
				    j = (i - 1);
					char* varString = va_arg(args, char*);
					int len2 = strnlen(varString, MAX_STRING_LENGTH);
					charStr = realloc(charStr, len + len2 + 1);
                    for(int t = 0; t < len2; t++)
                    {
                        charStr[j] = varString[t];
                        j++;
                    }
					break;
				}
				case 'd':
				{
				    j = (i - 1);
					int32_t number = va_arg(args, int32_t);

                    const char* digits = "0123456789";

                    char tempChar[11] = {'\0'};
                    int negative = (number < 0);
                    if(negative) {number = -number;}

                    uint64_t b = 0;
                    do
                    {
                        tempChar[b++] = digits[number % 10];
                        number /= 10;
                    } while(number > 0);

                    if(negative) {tempChar[b++] = '-';}
                    tempChar[b--] = '\0';

                    int t = len + b;
                    charStr = realloc(charStr, sizeof(char) * t);

                    uint64_t a = 0;
                    for(; a < b; a++, b--)
                    {
                        char  temp = tempChar[b];
                        tempChar[b] = tempChar[a];
                        tempChar[a] = temp;
                    }

                    b = 0;
                    for(; j < t; j++, b++)
                    {
                        charStr[j] = tempChar[b];
                    }
                    j++;
                    break;
				}
                case 'b':
				{
				    j = (i - 1);
					uint64_t bin = va_arg(args, uint64_t);
					printUInt64Digits(bin, 2, len);
					break;
                }
				case 'x':
				{
				    j = (i - 1);
					uint64_t hex = va_arg(args, uint64_t);
					printUInt64Digits(hex, 16, len);
					break;
				}
				case 'l':
				{
				    j = (i - 1);
					if(txt[i+1] == 'l' && txt[i+2] == 'u')
					{
						i+=2;
                        uint64_t num = va_arg(args, uint64_t);
						printUInt64Digits(num, 10, len);
					} else if(txt[i+1] == 'f')
                    {
                        i++;
                        double number = va_arg(args, double);
                        printDoubles(number, len);
                        break;
                    }
					break;
				}

			}
		} else {
		    if(txt[i] != '\n')
            {
                charStr[i] = txt[i];
            }
		}
	}

	va_end(args);

	if(j == 0)
    {
        charStr[i] = '\0';
    } else {
        charStr[j] = '\0';
    }

    if(strings == NULL)
    {
        strings = malloc(sizeof *strings);
    }
    else
    {
        strings = realloc(strings, sizeof *strings * (stringsIndex + 1));
    }

    len = strnlen(charStr, MAX_STRING_LENGTH);

    strings[stringsIndex] = malloc(len + 1); // The +1 so we can NULL Terminate.

    strncpy(strings[stringsIndex], charStr, len); // Copy charStr to the string.

    strings[stringsIndex][len] = 0; // NULL Terminate each string here.

    stringsIndex++;
}

char* that_getString(unsigned int strNumber)
{
    return strings[strNumber];
}

void that_printAllStrings()
{
    printf("\n-------STRINGS LIST-----------\n");
    for(unsigned int t = 0; t < stringsIndex; t++)
    {
        printf("DISPLAYING STRING -> #%d - %s\n", t, strings[t]);
    }
}

void that_removeString(unsigned int strNumber)
{
    if(strNumber < 1)
    {
        strNumber = 1;
    }

    if(strNumber > stringsIndex)
    {
        strNumber = stringsIndex;
    }

    // remove string from numbered position and copy from position to new strings
    char** tempStrings = NULL;
    tempStrings = malloc(sizeof *tempStrings);
    unsigned int newIndex = 0;
    if(stringsIndex > 0)
    {
        for(unsigned int t = 0; t < stringsIndex; t++)
        {
            if(t != (strNumber - 1))
            {
                int len = strnlen(strings[t], MAX_STRING_LENGTH);
                tempStrings = realloc(tempStrings, sizeof(*tempStrings) * (t + 1));
                tempStrings[newIndex] = malloc(len + 1);
                strncpy(tempStrings[newIndex], strings[t], len);
                tempStrings[newIndex][len] = 0;
                newIndex++;
            } else {
                printf("\nREMOVING STRING #%d : %s\n", t + 1, strings[t]);
            }
        }
    }

    for(unsigned int t = 0; t < stringsIndex; t++)
    {
        free(strings[t]);
    }
    free(strings);

    // COPY from tempStrings to strings
    strings = malloc(sizeof *strings);

    for(unsigned int t = 0; t < newIndex; t++)
    {
        strings = realloc(strings, sizeof(*strings) * (t + 1));
        int len = strnlen(tempStrings[t], MAX_STRING_LENGTH);
        strings[t] = malloc(len + 1);
        strncpy(strings[t], tempStrings[t], len);
        strings[t][len] = 0;
    }

    for(unsigned int t = 0; t < newIndex; t++)
    {
        free(tempStrings[t]);
    }

    free(tempStrings);
    stringsIndex = newIndex;
}

void that_cleanupStrings() // Cleans out the strings.
{
    printf("\n-------CLEANING LIST-----------\n");
    printf("TOTAL STRINGS : %d\n", stringsIndex);
    for(unsigned int t = 0; t < stringsIndex; t++)
    {
        printf("STRING : #%d - %s\n", t, strings[t]);
        free(strings[t]);
    }

    printf("\nFREEING strings\n");
    free(strings);
    free(charStr);
}


