#pragma once

#include "PhonebookEntry.h"

PhonebookEntry *Load(char *fileName, int *pNumberOfRecords);
PhonebookEntry *ParseLine(char *line);