#include <stdlib.h>

#include "Delete.h"
#include "PhonebookEntry.h"

void DeleteEntry(PhonebookEntries *pEntries, PhonebookEntry *pEntry)
{
    int index = 0;
    for (; index < pEntries->actualNumber; index++)
    {
        if (pEntries->pEntries[index] == pEntry)
        {
            free(pEntries->pEntries[index++]);
            break;
        }
    }
    
    for (; index < pEntries->actualNumber; index++)
    {
        pEntries->pEntries[index - 1] = pEntries->pEntries[index];
    }
    pEntries->actualNumber--;
}