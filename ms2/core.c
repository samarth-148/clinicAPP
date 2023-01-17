// Full Name  : Samarth Shaileleshkumar Patel
// Email      : sspatel74@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"

// Clear the standard input buffer
void clearInputBuffer(void)
{
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n')
	{
		; // do nothing!
	}
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

// 1.check the entered value and validate for an integer value
int inputInt(void)
{
	int value = 0;
	char newline = '0';
	while (newline != '\n')
	{
		scanf("%d%c", &value, &newline);
		if (newline != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	}
	return value;
};

// 2.check the entered value and validate for and positive integer non-zero value
int inputIntPositive(void)
{

	int count = 1;
	int positive_int = 0;
	while (count)
	{
		positive_int = inputInt();
		if (positive_int <= 0)
		{
			printf("ERROR! Value must be > 0: ");
		}
		else
		{
			count = 0;
		}
	}
	return positive_int;
};

// 3. checks the entered two values and validate for the values enterewd between lowerbound and upperbound
int inputIntRange(int lower_bound, int upper_bound)
{
	int range = 0;
	int count = 1;
	while (count)
	{
		range = inputInt();
		if (range < lower_bound || range > upper_bound)
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
		}
		else
		{
			count = 0;
		}
	}
	return range;
};

// 4.get the single char value and validate for the charater if it matches to the received charactes of c string argument
char inputCharOption(const char matchstring[])
{
	int count = 0, i;
	char char_value = '0';
	char char_value1 = '0';
	int continue_loop = 1;
	for (i = 0; matchstring[i] != '\0'; i++)
	{
		count++;
	}
	while (continue_loop)
	{
		scanf("%c%c", &char_value, &char_value1);
		if (char_value1 == '\n')
		{
			for (i = 0; i < count && continue_loop; i++)
			{
				if (char_value == matchstring[i])
				{
					continue_loop = 0;
				}
			}
			if (continue_loop)
			{
				printf("ERROR: Character must be one of [%s]: ", matchstring);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", matchstring);
		}
	}
	return char_value;
};

// 5.receives a C string value within the specified given range speciefied by the 2nd and 3rd arguments.
void inputCString(char pointer[], int min, int max){
	{int j = 0, k = 0;
int count = 0;
int continue_loop = 1;
char inputCString[500];
while (continue_loop)
{
	scanf("%500[^\n]", inputCString);
	clearInputBuffer();
	count = 0;
	for (j = 0; inputCString[j] != '\0'; j++)
	{
		count++;
	}
	if (count < min && (min != max))
	{
		printf("ERROR: String length must be between %d and %d chars: ", min, max);
	}
	else if (count > max && (min != max))
	{
		printf("ERROR: String length must be no more than %d chars: ", max);
	}
	else if ((count < min || count > max) && min == max)
	{
		printf("ERROR: String length must be exactly %d chars: ", min);
	}
	else
	{
		for (k = 0; k < count + 1; k++)
		{
			pointer[k] = inputCString[k];
		}
		continue_loop = 0;
	}
}
}
}
;

// 6.the purpose of this function is to display an array of 10 digit as formatted phonenumber.
void displayFormattedPhone(const char cstring[])
{
	const int max_length = 10;
	int count = 0;
	int i, j;
	char matchstring[10] = "0123456789";
	if (cstring != NULL)
	{
		for (i = 0; cstring[i] != '\0'; i++)
		{
			count++;
		}
		if (count == 10)
		{
			// printf("\n%d\n", count);
			for (j = 0; j < max_length; j++)
			{
				// printf("\n%c%c\n", cstring[j], matchstring[0]);
				if (cstring[j] != matchstring[0] && cstring[j] != matchstring[1] && cstring[j] != matchstring[2] && cstring[j] != matchstring[3] && cstring[j] != matchstring[4] && cstring[j] != matchstring[5] && cstring[j] != matchstring[6] && cstring[j] != matchstring[7] && cstring[j] != matchstring[8] && cstring[j] != matchstring[9])
				{
					printf("(___)___-____");
					j = max_length;
				}
				else
				{
					if (j == 9)
					{
						printf("(%c%c%c)%c%c%c-%c%C%C%c", cstring[0], cstring[1], cstring[2], cstring[3], cstring[4], cstring[5], cstring[6], cstring[7], cstring[8], cstring[9]);
					}
				}
			}
		}
		else
		{
			printf("(___)___-____");
		}
	}
	else
	{
		printf("(___)___-____");
	}
};