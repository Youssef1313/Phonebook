#pragma once

#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_ADDRESS_LENGTH 300
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_LENGTH 15

typedef struct
{
    short day;
    short month;
    short year;
} Date;

typedef struct
{
    char lastName[MAX_NAME_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    Date birthDate;
    char address[MAX_ADDRESS_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} PhonebookEntry;

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