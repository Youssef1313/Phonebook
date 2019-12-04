#include "PhonebookEntry.h"
#include "Query.h"

// TODO: For later improvment, make the function take an address of entries, and return address of entries.
PhonebookEntries Search(char *lastName, PhonebookEntries entries)
{
    PhonebookEntries filteredEntries;
    filteredEntries.actualNumber = 0;
    filteredEntries.allocated = 4;
    filteredEntries.pEntries = malloc(sizeof(PhonebookEntry *) * filteredEntries.allocated);
    for (int i = 0; i < entries.actualNumber; i++)
    {
        if (!_stricmp(entries.pEntries[i]->lastName, lastName))
        {
            if (filteredEntries.actualNumber >= filteredEntries.allocated)
            {
                filteredEntries.allocated *= 2;
                filteredEntries.pEntries = realloc(filteredEntries.pEntries, sizeof(PhonebookEntry *) * filteredEntries.allocated);
                // TODO: Check if re-allocation failed.
            }
            filteredEntries.pEntries[filteredEntries.actualNumber++] = entries.pEntries[i];
        }
    }
    return filteredEntries;
}