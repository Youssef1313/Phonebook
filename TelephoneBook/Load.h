#pragma once

#include "PhonebookEntry.h"

PhonebookEntries Load(char *fileName);
PhonebookEntry *ParseLine(char *line);
