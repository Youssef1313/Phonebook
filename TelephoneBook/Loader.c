#pragma once

#include <stdio.h>
#include "PhonebookEntry.h"

#define MAX_LINE_LENGTH (2 * MAX_NAME_LENGTH + MAX_ADDRESS_LENGTH + MAX_EMAIL_LENGTH + MAX_PHONE_LENGTH + 16) // 16 is for: 5 commas, 1 '\n', and  for birthdate (e.g. 07-03-1999).

PhonebookEntry *Load(char *fileName, int *pNumberOfRecords)
{
    *pNumberOfRecords = 0;
    int internalNumberOfRecords = 4;
    PhonebookEntry **pEntries = malloc(sizeof(PhonebookEntry *) * internalNumberOfRecords);
    // TODO: Check if allocation failed and take appropriate action.
    FILE *pFile = fopen(fileName, "r");
    while (!feof(pFile))
    {
        (*pNumberOfRecords)++;
        if (*pNumberOfRecords > internalNumberOfRecords)
        {
            internalNumberOfRecords *= 2;
            pEntries = realloc(pEntries, sizeof(PhonebookEntry *) * internalNumberOfRecords);
        }
        char line[MAX_LINE_LENGTH]; 
        fgets(line, sizeof(line), pFile);
        pEntries[*pNumberOfRecords] = ParseLine(line);
    }

    fclose(pFile);
}