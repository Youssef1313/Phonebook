#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "PhonebookEntry.h"

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

    return !strtok(NULL, "-/");

}