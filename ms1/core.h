// Full Name  : Samarth Shaileleshkumar Patel
// Email      : sspatel74@myseneca.ca

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// 1.check the entered value and validate for an integer value
int inputInt(void);

// 2.check the entered value and validate for and positive integer non-zero value
int inputIntPositive(void);

// 3.check the entered two values and validate for the values enterewd between lowerbound and upperbound
int inputIntRange(int lower_bound, int upper_bound);

// 4.get the single char value and validate for the charater if it matches to the received charactes of c string argument
char inputCharOption(const char matchstring[]);

// 5.receives a C string value within the specified given range speciefied by the 2nd and 3rd arguments.
void inputCString(char pointer[], int min, int max);

// 6.the purpose of this function is to display an array of 10 digit as formatted phonenumber.
void displayFormattedPhone(const char *cstring);