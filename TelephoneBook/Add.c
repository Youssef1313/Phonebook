#include "PhonebookEntry.h"
#include "Add.h"

void AddEntry(PhonebookEntries *pEntries, PhonebookEntry *pEntry)
{
    if (pEntries->actualNumber >= pEntries->allocated)
    {
        pEntries->allocated *= 2;
        pEntries->pEntries = realloc(pEntries->pEntries, sizeof(PhonebookEntry *) * pEntries->allocated);
        // TODO: Check if re-allocation failed.
    }
    pEntries->pEntries[pEntries->actualNumber] = pEntry;
    pEntries->actualNumber++;

}