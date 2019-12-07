#include <string.h>

#include "PhonebookEntry.h"
#include "ComparatorFunctions.h"

int CompareEntriesByDate(const void *p1, const void *p2)
{
    PhonebookEntry **first = (PhonebookEntry **)p1;
    PhonebookEntry **second = (PhonebookEntry **)p2;
    return CompareDates((*first)->birthDate, (*second)->birthDate);
}

int CompareEntriesByLastName(const void *p1, const void *p2)
{
    PhonebookEntry **first = (PhonebookEntry **)p1;
    PhonebookEntry **second = (PhonebookEntry **)p2;
    return _stricmp((*first)->lastName, (*second)->lastName);
}

int CompareDates(Date date1, Date date2)
{
    if (date1.year > date2.year) return 1;
    if (date1.year < date2.year) return -1;

    if (date1.month > date2.month) return 1;
    if (date1.month < date2.month) return -1;

    if (date1.day > date2.day) return 1;
    if (date1.day < date2.day) return -1;
    return 0;
}