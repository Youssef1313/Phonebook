#pragma once

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

Date *ConstructDate(short day, short month, short year)
{
    Date *pDate = malloc(sizeof(Date));
    // TODO: check if allocation failed.
    pDate->day = day;
    pDate->month = month;
    pDate->year = year;
    return pDate;
}