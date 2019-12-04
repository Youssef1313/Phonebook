#include "PhonebookEntry.h"

PhonebookEntry **Search(char *lastName, PhonebookEntry **entries, int numberOfTotalEntries, int *pNumberOfMatches)
{
    int internalSize = 4;
    PhonebookEntry **pResult = malloc(sizeof(PhonebookEntry *) * internalSize);
    *pNumberOfMatches = 0;
    for (int i = 0; i < numberOfTotalEntries; i++)
    {
        if (!_stricmp(entries[i]->lastName, lastName))
        {
            if (*pNumberOfMatches >= internalSize)
            {
                internalSize *= 2;
                pResult = realloc(pResult, sizeof(PhonebookEntry *) * internalSize);
                // TODO: Check if re-allocation failed.
            }
            pResult[*pNumberOfMatches] = entries[i];
            (*pNumberOfMatches)++;
        }
    }
    return pResult;
}