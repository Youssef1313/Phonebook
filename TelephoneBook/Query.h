#pragma once

#include "PhonebookEntry.h"

PhonebookEntry **Search(char *lastName, PhonebookEntry **entries, int numberOfTotalEntries, int *numberOfMatches);