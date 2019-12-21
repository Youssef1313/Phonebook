#include <stdio.h>
#include <string.h>

#include "ComparatorFunctions.h"
#include "PhonebookEntry.h"

int CompareDates(Date date1, Date date2)
{
    if (date1.year != date2.year) return date1.year - date2.year;
    if (date1.month != date2.month) return date1.month - date2.month;
    return date1.day - date2.day;

    /*int hashCode1 = date1.year * 10000 + date1.month * 100 + date1.day; // 07-03-1999 --> 19990000 + 300 + 7  --> 19990307
    int hashCode2 = date2.year * 10000 + date2.month * 100 + date2.day; // 20-02-1999 ---> 19990000 + 200 + 20 --> 19990220
    if (hashCode1 > hashCode2) return 1;
    if (hashCode1 < hashCode2) return -1;
    return 0;*/

    /*
    char buff1[9];
    char buff2[9];
    sprintf(buff1, "%04d%02d%02d", date1.year, date1.month, date1.day);
    sprintf(buff2, "%04d%02d%02d", date2.year, date2.month, date2.day);
    return strcmp(buff1, buff2);
    */

    /*                            
    if (date1.year > date2.year) return 1;
    if (date1.year < date2.year) return -1;

    if (date1.month > date2.month) return 1;
    if (date1.month < date2.month) return -1;

    if (date1.day > date2.day) return 1;
    if (date1.day < date2.day) return -1;
    return 0;
    */
}

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
