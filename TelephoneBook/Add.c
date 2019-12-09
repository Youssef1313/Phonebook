#include <stdio.h>
#include <stdlib.h>

#include "Add.h"
#include "PhonebookEntry.h"

void AddEntry(PhonebookEntries *pEntries, PhonebookEntry *pEntry)
{
    if (pEntries->actualNumber >= pEntries->allocated)
    {
        pEntries->allocated *= 2;
        PhonebookEntry **pTemp = realloc(pEntries->pEntries, sizeof(PhonebookEntry *) * pEntries->allocated);
        if (!pTemp)
        {
            printf("Failed to re-allocate memory. Program will exit.\n");
            exit(-1);
        }
        pEntries->pEntries = pTemp;
    }
    pEntries->pEntries[pEntries->actualNumber] = pEntry;
    pEntries->actualNumber++;
}
