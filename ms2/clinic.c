// Full Name  : Samarth Shaileleshkumar Patel
// Email      : sspatel74@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
void inputPhoneData2(struct Phone *phone)
{
    int selection;
    // get the phone info as user input
    printf("Phone Information\n"
           "-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    if (selection == 1)
    {
        printf("Contact: ");
        puts("CELL");
        strcpy(phone->description, "CELL");
    }
    if (selection == 2)
    {
        printf("Contact: ");
        puts("HOME");
        strcpy(phone->description, "HOME");
    }
    if (selection == 3)
    {
        printf("Contact: ");
        puts("WORK");
        strcpy(phone->description, "WORK");
    }
    if (selection == 4)
    {
        strcpy(phone->description, "TBD");
    }
    else
    {
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
    }
}

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        // putchar('\n');

        if (selection == 1)
        {
            printf("\nName  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            printf("\n");
            inputPhoneData2(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
    printf("\n");
}

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int counter = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            if (i == 0)
                displayPatientTableHeader();
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)", patient[i].phone.description);
            printf("\n");
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("* No records found *\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 1;
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
        if (selection != 0)
        {
            char c;
            scanf("%c", &c);
            suspend();
        }
    } while (selection != 0);
    printf("\n");
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i;
    int counter = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            // int selection = 0;
            patient[i].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[i]);
            counter++;
            break;
        }
    }
    if (counter == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patient_number;
    printf("Enter the patient number: ");
    scanf("%d", &patient_number);
    printf("\n");
    int result = findPatientIndexByPatientNum(patient_number, patient, max);
    if (result == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[result]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{

    int patient_number;
    // int i = 0;
    char a;
    printf("Enter the patient number: ");
    scanf("%d", &patient_number);
    int result = findPatientIndexByPatientNum(patient_number, patient, max);

    if (result == -1)
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    else
    {
        printf("\n");
        displayPatientData(&patient[result], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        getchar();
        a = getchar();

        if (a == 'Y' || a == 'y')
        {
            patient[result].patientNumber = 0;
            patient[result].name[strlen(patient[result].name) - 1] = '\0';
            patient[result].phone.description[result] = '\0';
            patient[result].phone.number[result] = '\0';
            printf("Patient record has been removed!\n\n");
        }
        else if (a == 'N' || a == 'n')
        {
            printf("Operation aborted.\n\n");
        }
    }
    clearInputBuffer();
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patient_number;
    printf("\n");
    printf("Search by patient number: ");
    scanf("%d", &patient_number);
    printf("\n");
    int result = findPatientIndexByPatientNum(patient_number, patient, max);
    if (result == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[result], FMT_FORM);
    }
    printf("\n");
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phonenumber[100];
    printf("\nSearch by phone number: ");
    inputCString(phonenumber, 10, 10);
    printf("\n");
    int i, j;
    int counter = 0, flag = 0;

    for (i = 0; i < max; i++)
    {
        if (i == 0)
            displayPatientTableHeader();

        flag = 0;
        for (j = 0; j < strlen(patient[i].phone.number); j++)
        {
            if (phonenumber[j] == patient[i].phone.number[j])
            {
                flag++;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag == 10)
        {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)", patient[i].phone.description);
            printf("\n");
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int LargestPatientNum = 0;
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > LargestPatientNum)
        {
            LargestPatientNum = patient[i].patientNumber;
        }
    }
    return LargestPatientNum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    inputPhoneData(&patient->phone);
    printf("\n");
}

// Get user input for phone contact information
void inputPhoneData(struct Phone *phone)
{
    int choice;
    // get the phone info as user input
    printf("\nPhone Information\n"
           "-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    choice = inputIntRange(1, 4);
    putchar('\n');
    if (choice == 1)
    {
        printf("Contact: ");
        puts("CELL");
        strcpy(phone->description, "CELL");
    }
    if (choice == 2)
    {
        printf("Contact: ");
        puts("HOME");
        strcpy(phone->description, "HOME");
    }
    if (choice == 3)
    {
        printf("Contact: ");
        puts("WORK");
        strcpy(phone->description, "WORK");
    }
    if (choice == 4)
    {
        strcpy(phone->description, "TBD");
    }
    else
    {
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
    }
    printf("*** New patient record added ***\n");
}