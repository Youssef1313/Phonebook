#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_COLOR_CONSTANTS.h"
#include "PhonebookEntry.h"
#include "Query.h"

PhonebookEntries Search(PhonebookEntry *pEntryToSearchFor, PhonebookEntries *pEntries)
{
    PhonebookEntries filteredEntries;
    filteredEntries.actualNumber = 0;
    filteredEntries.allocated = 4;
    filteredEntries.pEntries = malloc(sizeof(PhonebookEntry *) * filteredEntries.allocated);
    if (!filteredEntries.pEntries)
    {
        printf(ANSI_COLOR_RED"Failed to allocate memory. Program will exit now.\n"ANSI_COLOR_RESET);
        exit(-1);
    }
    for (int i = 0; i < pEntries->actualNumber; i++)
    {
        if (
            (!*pEntryToSearchFor->lastName || !_stricmp(pEntries->pEntries[i]->lastName, pEntryToSearchFor->lastName)) &&
            (!*pEntryToSearchFor->firstName || !_stricmp(pEntries->pEntries[i]->firstName, pEntryToSearchFor->firstName)) &&
            (!*pEntryToSearchFor->address || !_stricmp(pEntries->pEntries[i]->address, pEntryToSearchFor->address)) &&
            (!*pEntryToSearchFor->email || !_stricmp(pEntries->pEntries[i]->email, pEntryToSearchFor->email)) &&
            (!*pEntryToSearchFor->phone || !_stricmp(pEntries->pEntries[i]->phone, pEntryToSearchFor->phone)) &&
            ((!pEntryToSearchFor->birthDate.day && !pEntryToSearchFor->birthDate.month && !pEntryToSearchFor->birthDate.year) || (pEntries->pEntries[i]->birthDate.day == pEntryToSearchFor->birthDate.day && pEntries->pEntries[i]->birthDate.month == pEntryToSearchFor->birthDate.month && pEntries->pEntries[i]->birthDate.year == pEntryToSearchFor->birthDate.year))
            )
        {
            if (filteredEntries.actualNumber >= filteredEntries.allocated)
            {
                filteredEntries.allocated *= 2;
                PhonebookEntry **pTemp = realloc(filteredEntries.pEntries, sizeof(PhonebookEntry *) * filteredEntries.allocated);
                if (!pTemp)
                {
                    printf(ANSI_COLOR_RED"Failed to re-allocate memory. Program will exit.\n"ANSI_COLOR_RESET);
                    exit(-1);
                }
                filteredEntries.pEntries = pTemp;

            }
            filteredEntries.pEntries[filteredEntries.actualNumber++] = pEntries->pEntries[i];
        }
    }
    return filteredEntries;
}
