#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PhonebookEntry.h"
#include "Validation.h"

bool IsLeapYear(short year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool IsValidDate(char *dateString, Date *pDate)
{
    char *tok = strtok(dateString, "-/");
    if (!tok) return false;
    pDate->day = atoi(tok);

    tok = strtok(NULL, "-/");
    if (!tok) return false;
    pDate->month = atoi(tok);

    tok = strtok(NULL, "-/");
    if (!tok) return false;
    pDate->year = atoi(tok);

    if (!strtok(NULL, "-/"))
    {
        if (pDate->year < 1500 || pDate->year > 3000)
            return false;

        if (pDate->month == 1 || pDate->month == 3 || pDate->month == 5 || pDate->month == 7 || pDate->month == 8 || pDate->month == 10 || pDate->month == 12)
            return pDate->day >= 1 && pDate->day <= 31;

        if (pDate->month == 4 || pDate->month == 6 || pDate->month == 9 || pDate->month == 11)
            return pDate->day >= 1 && pDate->day <= 30;

        if (pDate->month == 2 && pDate->day <= 28 && pDate->day >= 1)
            return true;

        if (pDate->month == 2 && pDate->day <= 29 && pDate->day >= 1)
            return IsLeapYear(pDate->year);
    }
    return false;
}

bool IsValidEmail(char *email)
{
    int countAtSign = 0;
    int lastAtIndex;

    int countDotSign = 0;
    int lastDotIndex = 0;

    int length = strlen(email);
    for (int i = 0; i < length; i++)
    {
        if (email[i] == '@')
        {
            countAtSign++;
            lastAtIndex = i;
        }
        else if (email[i] == '.')
        {
            if (i - lastDotIndex == 1) return false; // 2 consecutive dots are not valid.
            countDotSign++;
            lastDotIndex = i;
        }
        else if (email[i] == ' ')
        {
            return false;
        }
    }
    return (countAtSign == 1 && lastAtIndex != 0 && countDotSign >= 1 &&
        lastDotIndex - lastAtIndex >= 2 &&
        length - lastDotIndex >= 2);
}

bool IsValidPhone(char *phone)
{
    for (int i = 0, n = strlen(phone); i < n; i++)
    {
        // Most ASCII characters are larger than the digits. Hence, check the > 9 condition first because it's more likely to fail than < 0.
        if (phone[i] > '9' || phone[i] < '0') return false;
    }
    return true;
}

bool StringContains(char *s, char c)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == c) return true;
    }
    return false;
}
