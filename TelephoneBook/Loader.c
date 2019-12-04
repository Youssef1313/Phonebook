#pragma once

#include <stdio.h>
#include "PhonebookEntry.h"
#include "Loader.h"

#define MAX_LINE_LENGTH (2 * MAX_NAME_LENGTH + MAX_ADDRESS_LENGTH + MAX_EMAIL_LENGTH + MAX_PHONE_LENGTH + 16) // 16 is for: 5 commas, 1 '\n', and  for birthdate (e.g. 07-03-1999).

PhonebookEntries Load(char *fileName)
{
    PhonebookEntries entries;
    entries.actualNumber = 0;
    entries.allocated = 4;
    entries.pEntries = malloc(sizeof(PhonebookEntry *) * entries.allocated);;
    // TODO: Check if allocation failed and take appropriate action.

    FILE *pFile = fopen(fileName, "r");
    if (!pFile)
    {
        printf("UNABLE TO READ THE FILE.\n");
        entries.actualNumber = -1;
        return entries;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), pFile))
    {
        if (entries.actualNumber >= entries.allocated)
        {
            entries.allocated *= 2;
            entries.pEntries = realloc(entries.pEntries, sizeof(PhonebookEntry *) * entries.allocated);
            // TODO: Check if re-allocation failed.
        }
        entries.pEntries[entries.actualNumber] = ParseLine(line);
        entries.actualNumber++;
       
    }
    fclose(pFile);
    return entries;
}

PhonebookEntry *ParseLine(char *line)
{
    char *lastName = strtok(line, ",");
    char *firstName = strtok(NULL, ",");
    char *birthDate = strtok(NULL, ",");
    char *address = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    char *phone = strtok(NULL, ",");

    short day = atoi(strtok(birthDate, "-"));
    short month = atoi(strtok(NULL, "-"));
    short year = atoi(strtok(NULL, "-"));
    
    return ConstructPhonebookEntry(lastName, firstName, (Date) { day, month, year }, address, email, phone);
}