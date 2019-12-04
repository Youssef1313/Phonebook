#include <stdlib.h>
#include "Delete.h"
#include "PhonebookEntry.h"

void DeleteEntry(PhonebookEntries *pEntries, int indexToDelete)
{
    free(pEntries->pEntries[indexToDelete]);
    for (indexToDelete++; indexToDelete < pEntries->actualNumber; indexToDelete++)
    {
        pEntries->pEntries[indexToDelete - 1] = pEntries->pEntries[indexToDelete];
    }
    pEntries->actualNumber--;
    // 0 1 2 3 4 5 6
    // SEND 2 as index.
    // free 2
    // inc index to 3
    // arr[2] = arr[3]        0 1 3 3 4 5 6
    // arr[3] = arr[4]        0 1 3 4 4 5 6
    // arr[4] = arr[5]        0 1 3 4 5 5 6
    // arr[5] = arr[6]        0 1 3 4 5 6 6, the last element is unused since actualNumber is decreased.
}