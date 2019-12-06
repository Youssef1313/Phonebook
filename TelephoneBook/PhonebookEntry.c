#pragma once

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
        printf("Failed to allocate memory. Program will exit.\n");
        exit(-1);
    }
    strcpy(pEntry->lastName, lastName); // TODO: Optimization. Prevent buffer overflow.
    strcpy(pEntry->firstName, firstName); // TODO: Optimization. Prevent buffer overflow.
    pEntry->birthDate = birthDate;
    strcpy(pEntry->address, address); // TODO: Optimization. Prevent buffer overflow.
    strcpy(pEntry->email, email); // TODO: Optimization. Prevent buffer overflow.
    strcpy(pEntry->phone, phone); // TODO: Optimization. Prevent buffer overflow.
    return pEntry;
}

void PrintEntries(PhonebookEntries *pEntries)
{
    printf("\n");
    if (pEntries->actualNumber == 0)
    {
        printf("No records are found.\n\n");
        return;
    }
    printf(ANSI_COLOR_BLUE"Printing %d record(s)\n\n"ANSI_COLOR_RESET, pEntries->actualNumber);
    for (int i = 0; i < pEntries->actualNumber; i++)
    {
        printf(ANSI_COLOR_MAGENTA"First name: %s, Last name: %s\n", pEntries->pEntries[i]->firstName, pEntries->pEntries[i]->lastName);
        printf("Address: %s, Birthdate: %02d-%02d-%04d\n", pEntries->pEntries[i]->address, pEntries->pEntries[i]->birthDate.day, pEntries->pEntries[i]->birthDate.month, pEntries->pEntries[i]->birthDate.year);
        printf("Email: %s, Phone: %s\n\n"ANSI_COLOR_RESET, pEntries->pEntries[i]->email, pEntries->pEntries[i]->phone);
    }
}

void PrintNumberedEntries(PhonebookEntries *pEntries)
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
        printf(ANSI_COLOR_MAGENTA"Record number: %d\n", i + 1);
        printf("First name: %s, Last name: %s\n", pEntries->pEntries[i]->firstName, pEntries->pEntries[i]->lastName);
        printf("Address: %s, Birthdate: %02d-%02d-%04d\n", pEntries->pEntries[i]->address, pEntries->pEntries[i]->birthDate.day, pEntries->pEntries[i]->birthDate.month, pEntries->pEntries[i]->birthDate.year);
        printf("Email: %s, Phone: %s\n\n"ANSI_COLOR_RESET, pEntries->pEntries[i]->email, pEntries->pEntries[i]->phone);
    }
}