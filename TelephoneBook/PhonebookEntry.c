#pragma once

#include <stdlib.h>
#include <string.h>
#include "Load.h"
#include "PhonebookEntry.h"

PhonebookEntry *ConstructPhonebookEntry(char *lastName, char *firstName, Date birthDate, char *address, char *email, char *phone)
{
    PhonebookEntry *pEntry = malloc(sizeof(PhonebookEntry));
    // TODO: check if allocation failed.
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
    printf("Printing %d record(s)\n\n", pEntries->actualNumber);
    for (int i = 0; i < pEntries->actualNumber; i++)
    {
        printf("First name: %s, Last name: %s\n", pEntries->pEntries[i]->firstName, pEntries->pEntries[i]->lastName);
        printf("Address: %s\n", pEntries->pEntries[i]->address);
        printf("Email: %s, Phone: %s\n\n", pEntries->pEntries[i]->email, pEntries->pEntries[i]->phone);
    }
}