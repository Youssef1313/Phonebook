#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PhonebookEntry.h"
#include "Save.h"

void SaveEntries(PhonebookEntries entries, char *fileName)
{
    FILE *pFile = fopen(fileName, "w");
    if (!pFile)
    {
        printf("UNABLE TO OPEN FILE FOR WRITING. THE PROGRAM WILL EXIT.\n");
        exit(-1);
    }
    for (int i = 0; i < entries.actualNumber; i++)
    {
        char parsedBirthdate[11];
        sprintf(parsedBirthdate, "%02d-%02d-%04d", entries.pEntries[i]->birthDate.day, entries.pEntries[i]->birthDate.month, entries.pEntries[i]->birthDate.year);
        fprintf(pFile, "%s,%s,%s,%s,%s,%s\n", entries.pEntries[i]->lastName, entries.pEntries[i]->firstName, parsedBirthdate, entries.pEntries[i]->address, entries.pEntries[i]->email, entries.pEntries[i]->phone);
    }
    fclose(pFile);
}