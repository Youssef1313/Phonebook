#pragma once

#include <stdbool.h>
#include "PhonebookEntry.h"

bool IsValidDate(char *dateString, Date *date);
bool StringContains(char *s, char c);
bool IsLeapYear(short year);
