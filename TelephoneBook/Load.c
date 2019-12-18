#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_COLOR_CONSTANTS.h"
#include "Add.h"
#include "Load.h"
#include "PhonebookEntry.h"
#include "Validation.h"

#define MAX_LINE_LENGTH (2 * MAX_NAME_LENGTH + MAX_ADDRESS_LENGTH + MAX_EMAIL_LENGTH + MAX_PHONE_LENGTH + 16) // 16 is for: 5 commas, 1 '\n', and  for birthdate (e.g. 07-03-1999).

PhonebookEntries Load(char *fileName)
{
    PhonebookEntries entries;
    entries.actualNumber = 0;
    entries.allocated = 4;
    entries.pEntries = malloc(sizeof(PhonebookEntry *) * entries.allocated);
    if (!entries.pEntries)
    {
        printf(ANSI_COLOR_RED"Failed to allocate memory. Program will exit.\n"ANSI_COLOR_RESET);
        exit(-1);
    }
    if (fileName == NULL) return entries;

    FILE *pFile = fopen(fileName, "r");
    if (!pFile)
    {
        entries.actualNumber = -1;
        return entries;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), pFile))
    {
        int length = strlen(line);
        if (line[length - 1] == '\n') line[length - 1] = '\0';
        PhonebookEntry *pEntry = ParseLine(line);
        if (!pEntry)
        {
            printf(ANSI_COLOR_YELLOW"WARNING: Cannot parse the following line:\n"ANSI_COLOR_RESET);
            printf("%s\n", line);
            continue;
        }
        AddEntry(&entries, pEntry);
    }
    fclose(pFile);
    return entries;
}

// Returns a pointer to PhonebookEntry on success. Returns NULL on failure.
PhonebookEntry *ParseLine(char *line)
{
    char *lineDup = _strdup(line);
    char *lastName = strtok(lineDup, ",");
    if (!lastName) return NULL;
    char *firstName = strtok(NULL, ",");
    if (!firstName) return NULL;
    char *birthDate = strtok(NULL, ",");
    if (!birthDate) return NULL;
    char *address = strtok(NULL, ",");
    if (!address) return NULL;
    char *email = strtok(NULL, ",");
    if (!email || !IsValidEmail(email)) return NULL;
    char *phone = strtok(NULL, ",");
    if (!phone || !IsValidPhone(phone)) return NULL;
    if (strtok(NULL, ",")) return NULL;
    Date birthDateStruct;
    if (!IsValidDate(birthDate, &birthDateStruct)) return NULL;

    return ConstructPhonebookEntry(lastName, firstName, birthDateStruct, address, email, phone);
}
