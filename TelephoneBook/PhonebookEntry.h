#pragma once

#define MAX_NAME_LENGTH 20
#define MAX_ADDRESS_LENGTH 300
#define MAX_EMAIL_LENGTH 50
#define MAX_PHONE_LENGTH 16

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

typedef struct
{
    PhonebookEntry **pEntries;
    int actualNumber;
    int allocated;
} PhonebookEntries;

PhonebookEntry *ConstructPhonebookEntry(char *lastName, char *firstName, Date birthDate, char *address, char *email, char *phone);
void PrintEntries(PhonebookEntries *pEntries, int isNumberedOutput);
