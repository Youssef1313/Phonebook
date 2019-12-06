#include <stdio.h>
#include <stdlib.h>
#include "Add.h"
#include "PhonebookEntry.h"

void AddEntry(PhonebookEntries *pEntries, PhonebookEntry *pEntry)
{
    if (pEntries->actualNumber >= pEntries->allocated)
    {
        pEntries->allocated *= 2;
        pEntries->pEntries = realloc(pEntries->pEntries, sizeof(PhonebookEntry *) * pEntries->allocated);
        if (!pEntries->pEntries)
        {
            printf("Failed to re-allocate memory. Program will exit.\n");
            exit(-1);
        }
    }
    pEntries->pEntries[pEntries->actualNumber] = pEntry;
    pEntries->actualNumber++;

}