#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_COLOR_CONSTANTS.h"
#include "Load.h"
#include "PhonebookEntry.h"

PhonebookEntry *ConstructPhonebookEntry(char *lastName, char *firstName, Date birthDate, char *address, char *email, char *phone)
{
    PhonebookEntry *pEntry = malloc(sizeof(PhonebookEntry));
    if (!pEntry)
    {
        printf(ANSI_COLOR_RED"Failed to allocate memory. Program will exit.\n"ANSI_COLOR_RESET);
        exit(-1);
    }
    strncpy(pEntry->lastName, lastName, sizeof(pEntry->lastName));
    strncpy(pEntry->firstName, firstName, sizeof(pEntry->firstName));
    pEntry->birthDate = birthDate;
    strncpy(pEntry->address, address, sizeof(pEntry->address));
    strncpy(pEntry->email, email, sizeof(pEntry->email));
    strncpy(pEntry->phone, phone, sizeof(pEntry->phone));

    // strncpy doesn't ensure that the string is null-terminated. Do it manually.
    pEntry->lastName[sizeof(pEntry->lastName) - 1] = '\0';
    pEntry->firstName[sizeof(pEntry->firstName) - 1] = '\0';
    pEntry->address[sizeof(pEntry->address) - 1] = '\0';
    pEntry->email[sizeof(pEntry->email) - 1] = '\0';
    pEntry->phone[sizeof(pEntry->phone) - 1] = '\0';
    return pEntry;
}

void PrintEntries(PhonebookEntries *pEntries, int isNumberedOutput)
{
    printf("\n");
    if (pEntries->actualNumber == 0)
    {
        printf(ANSI_COLOR_RED"No records are found.\n\n"ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_BLUE"Printing %d record(s)\n\n"ANSI_COLOR_RESET, pEntries->actualNumber);
    for (int i = 0; i < pEntries->actualNumber; i++)
    {
        if (isNumberedOutput) printf(ANSI_COLOR_MAGENTA"Record number: %d\n", i + 1);
        printf(ANSI_COLOR_MAGENTA"First name: %s, Last name: %s\n", pEntries->pEntries[i]->firstName, pEntries->pEntries[i]->lastName);
        printf("Address: %s, Birthdate: %02d-%02d-%04d\n", pEntries->pEntries[i]->address, pEntries->pEntries[i]->birthDate.day, pEntries->pEntries[i]->birthDate.month, pEntries->pEntries[i]->birthDate.year);
        printf("Email: %s, Phone: %s\n\n"ANSI_COLOR_RESET, pEntries->pEntries[i]->email, pEntries->pEntries[i]->phone);
    }
}
