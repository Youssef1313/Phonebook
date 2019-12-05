#include <stdlib.h>
#include <string.h>
#include "Modify.h"
#include "PhonebookEntry.h"

void ModifyRecord(PhonebookEntry *pOldEntry, PhonebookEntry *pNewEntry)
{
    strcpy(pOldEntry->lastName, pNewEntry->lastName);
    strcpy(pOldEntry->firstName, pNewEntry->firstName);
    strcpy(pOldEntry->address, pNewEntry->address);
    strcpy(pOldEntry->email, pNewEntry->email);
    strcpy(pOldEntry->phone, pNewEntry->phone);
    pOldEntry->birthDate = pNewEntry->birthDate;
    free(pNewEntry);
}