#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_COLOR_CONSTANTS.h"
#include "Add.h"
#include "Load.h"
#include "PhonebookEntry.h"

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
        AddEntry(&entries, ParseLine(line));
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

    short day = atoi(strtok(birthDate, "-/"));
    short month = atoi(strtok(NULL, "-/"));
    short year = atoi(strtok(NULL, "-/"));
    
    return ConstructPhonebookEntry(lastName, firstName, (Date) { day, month, year }, address, email, phone);
}
