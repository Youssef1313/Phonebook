#pragma once

#include <stdbool.h>
#include "PhonebookEntry.h"

bool IsLeapYear(short year);
bool IsValidDate(char *dateString, Date *date);
bool IsValidEmail(char *email);
bool IsValidPhone(char *phone);
bool StringContains(char *s, char c);
