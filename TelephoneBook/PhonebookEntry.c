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
