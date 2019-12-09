#include <stdlib.h>
#include <string.h>

#include "Modify.h"
#include "PhonebookEntry.h"

void ModifyRecord(PhonebookEntry *pOldEntry, PhonebookEntry *pNewEntry)
{
    if(*(pNewEntry->lastName)) strcpy(pOldEntry->lastName, pNewEntry->lastName);
    if(*(pNewEntry->firstName)) strcpy(pOldEntry->firstName, pNewEntry->firstName);
    if(*(pNewEntry->address)) strcpy(pOldEntry->address, pNewEntry->address);
    if(*(pNewEntry->email)) strcpy(pOldEntry->email, pNewEntry->email);
    if(*(pNewEntry->phone)) strcpy(pOldEntry->phone, pNewEntry->phone);
    if (pNewEntry->birthDate.day) pOldEntry->birthDate = pNewEntry->birthDate;
    free(pNewEntry);
}
