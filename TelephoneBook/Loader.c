#pragma once

#include <stdio.h>
#include "PhonebookEntry.h"
#include "Loader.h"

#define MAX_LINE_LENGTH (2 * MAX_NAME_LENGTH + MAX_ADDRESS_LENGTH + MAX_EMAIL_LENGTH + MAX_PHONE_LENGTH + 16) // 16 is for: 5 commas, 1 '\n', and  for birthdate (e.g. 07-03-1999).

PhonebookEntry **Load(char *fileName, int *pNumberOfRecords)
{
    *pNumberOfRecords = 0;
    int internalNumberOfRecords = 4;
    PhonebookEntry **pEntries = malloc(sizeof(PhonebookEntry *) * internalNumberOfRecords);
    // TODO: Check if allocation failed and take appropriate action.

    FILE *pFile = fopen(fileName, "r");
    if (!pFile)
    {
        printf("UNABLE TO READ THE FILE.\n");
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), pFile))
    {
        if (*pNumberOfRecords >= internalNumberOfRecords)
        {
            internalNumberOfRecords *= 2;
            pEntries = realloc(pEntries, sizeof(PhonebookEntry *) * internalNumberOfRecords);
            // TODO: Check if re-allocation failed.
        }
        pEntries[*pNumberOfRecords] = ParseLine(line);
        (*pNumberOfRecords)++;
       
    }
    fclose(pFile);
    return pEntries;
}

PhonebookEntry *ParseLine(char *line)
{
    PhonebookEntry *pEntry = malloc(sizeof(PhonebookEntry));
    char *lastName = strtok(line, ",");
    char *firstName = strtok(NULL, ",");
    char *birthDate = strtok(NULL, ",");
    char *address = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    char *phone = strtok(NULL, ",");

    strcpy(pEntry->lastName, lastName);
    strcpy(pEntry->firstName, firstName);
    strcpy(pEntry->address, address);
    strcpy(pEntry->email, email);
    strcpy(pEntry->phone, phone);
    
    short day = atoi(strtok(birthDate, "-"));
    short month = atoi(strtok(NULL, "-"));
    short year = atoi(strtok(NULL, "-"));
    
    pEntry->birthDate = (Date){ day, month, year };
    return pEntry;
}