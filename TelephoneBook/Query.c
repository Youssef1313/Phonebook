#include <stdlib.h>
#include <string.h>
#include "PhonebookEntry.h"
#include "Query.h"

PhonebookEntries Search(char *lastName, PhonebookEntries *pEntries)
{
    PhonebookEntries filteredEntries;
    filteredEntries.actualNumber = 0;
    filteredEntries.allocated = 4;
    filteredEntries.pEntries = malloc(sizeof(PhonebookEntry *) * filteredEntries.allocated);
    for (int i = 0; i < pEntries->actualNumber; i++)
    {
        if (!_stricmp(pEntries->pEntries[i]->lastName, lastName))
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