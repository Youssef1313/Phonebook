#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PhonebookEntry.h"
#include "Validation.h"

bool IsValidDate(char *dateString, Date *date)
{
    char *tok = strtok(dateString, "-/");
    if (!tok) return false;
    date->day = atoi(tok);

    tok = strtok(NULL, "-/");
    if (!tok) return false;
    date->month = atoi(tok);

    tok = strtok(NULL, "-/");
    if (!tok) return false;
    date->year = atoi(tok);

    if (!strtok(NULL, "-/"))
    {
        if (date->year < 1500 || date->year > 3000)
            return false;

        if (date->month == 1 || date->month == 3 || date->month == 5 || date->month == 7 || date->month == 8 || date->month == 10 || date->month == 12)
            return date->day >= 1 && date->day <= 31;

        if (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11)
            return date->day >= 1 && date->day <= 31;

        if (date->month == 2 && IsLeapYear(date->year))
            return date->day >= 1 && date->day <= 29;

        if (date->month == 2 && !IsLeapYear(date->year))
            return date->day >= 1 && date->day <= 28;

    }

    return false;
}

bool IsLeapYear(short year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}


bool StringContains(char *s, char c)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == c) return true;
    }
    return false;
}


