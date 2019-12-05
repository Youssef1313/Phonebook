#include <stdlib.h>
#include <string.h>
#include "PhonebookEntry.h"
#include "Query.h"

PhonebookEntries MultiSearch(PhonebookEntry *pEntryToSearchFor, PhonebookEntries *pEntries)
{
    PhonebookEntries filteredEntries;
    filteredEntries.actualNumber = 0;
    filteredEntries.allocated = 4;
    filteredEntries.pEntries = malloc(sizeof(PhonebookEntry *) * filteredEntries.allocated);
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
                filteredEntries.pEntries = realloc(filteredEntries.pEntries, sizeof(PhonebookEntry *) * filteredEntries.allocated);
                // TODO: Check if re-allocation failed.
            }
            filteredEntries.pEntries[filteredEntries.actualNumber++] = pEntries->pEntries[i];
        }
    }
    return filteredEntries;
}