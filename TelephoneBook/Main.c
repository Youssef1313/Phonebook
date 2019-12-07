#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Add.h"
#include "ANSI_COLOR_CONSTANTS.h"
#include "ComparatorFunctions.h"
#include "Delete.h"
#include "Load.h"
#include "Modify.h"
#include "PhonebookEntry.h"
#include "Save.h"
#include "Query.h"
#include "Validation.h"

// Longest commands are DELETE and MODIFY (6 chars + '\0' = 7 chars).
// TODO: When implementing validation, implement separate functions to prompt for each field.
#define MAX_COMMAND_LENGTH 7
#define FILE_PATH "D:\\phonebook.txt"

PhonebookEntry *GetEntryFromUser(bool allowEmpty);
void GetString(char *buffer, int count);

int main(void)
{
    printf(ANSI_COLOR_CYAN"Welcome to phonebook program.\n\
The following is a list of the allowed commands to run the program:\n\n\
    1. LOAD   -> Loads the phonebook from hard disk.\n\
    2. QUERY  -> Search by a combination of fields.\n\
    3. ADD    -> Add new entry to phonebook.\n\
    4. DELETE -> Deletes an entry by providing first and last name.\n\
    5. MODIFY -> Modify a record.\n\
    6. PRINT  -> Print the phonebook in sorted order.\n\
    7. SAVE   -> Save the changes you made to the hard disk.\n\
    8. QUIT   -> Exit without saving.\n\n"ANSI_COLOR_RESET);
    PhonebookEntries entries = Load(NULL);
    int unsavedChanges = 0;
    while (1)
    {
        char command[MAX_COMMAND_LENGTH];
        printf(ANSI_COLOR_YELLOW"Enter a command: "ANSI_COLOR_RESET);
        GetString(command, sizeof(command));
        if (!_stricmp(command, "LOAD") || !_stricmp(command, "1"))
        {
            PhonebookEntries tempEntries = Load(FILE_PATH);
            if (tempEntries.actualNumber >= 0) // Load returns -1 if reading the file has failed.
            {
                entries = tempEntries;
                unsavedChanges = 0;
                printf(ANSI_COLOR_GREEN"File is loaded successfully. It has %d record(s).\n\n"ANSI_COLOR_RESET, entries.actualNumber);
            }
        }
        else if (!_stricmp(command, "QUERY") || !_stricmp(command, "2"))
        {
            printf("\tWhen prompted to any field, leaving it empty means it won't be used in searching.\n");
            PhonebookEntry *pSearchEntry = GetEntryFromUser(true);
            PhonebookEntries filtered = MultiSearch(pSearchEntry, &entries);
            PrintEntries(&filtered);
            free(pSearchEntry);
        }
        else if (!_stricmp(command, "ADD") || !_stricmp(command, "3"))
        {
            printf("\tWhen prompted to any field, leaving it empty will result in cancelling adding this record.\n");
            PhonebookEntry *pNewEntry = GetEntryFromUser(false);
            if (pNewEntry)
            {
                AddEntry(&entries, pNewEntry);
                unsavedChanges = 1;
                printf(ANSI_COLOR_GREEN"Record is added.\n\n"ANSI_COLOR_RESET);
            }
            else
                printf(ANSI_COLOR_RED"You've cancelled the add process.\n\n"ANSI_COLOR_RESET);
        }
        else if (!_stricmp(command, "DELETE") || !_stricmp(command, "4"))
        {
            char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for first and last name. If multiple records are found, you will be asked to select one.\n");
            do
            {
                printf(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET);
                GetString(lastName, sizeof(lastName));
            } while (!*lastName);

            do
            {
                printf(ANSI_COLOR_YELLOW"\t\tEnter first name: "ANSI_COLOR_RESET);
                GetString(firstName, sizeof(firstName));
            } while (!*firstName);
            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, firstName, (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = MultiSearch(pEntry, &entries);
            if (filtered.actualNumber == 0)
                printf(ANSI_COLOR_RED"No records are found.\n\n"ANSI_COLOR_RESET);
            else if (filtered.actualNumber == 1)
            {
                DeleteEntry(&entries, filtered.pEntries[0]);
                unsavedChanges = 1;
                printf(ANSI_COLOR_GREEN"Entry is deleted successfully. Current number of records is %d.\n\n"ANSI_COLOR_RESET, entries.actualNumber);
            }
            else
            {
                printf(ANSI_COLOR_BLUE"Found multiple results:\n"ANSI_COLOR_RESET);
                PrintNumberedEntries(&filtered);
                printf(ANSI_COLOR_YELLOW"Enter the number of the record (between 1 and %d) you want to delete: "ANSI_COLOR_RESET, filtered.actualNumber);
                int recordNumber = 0;
                do
                {
                    char numberString[5];
                    GetString(numberString, sizeof(numberString));
                    recordNumber = atoi(numberString);
                } while (recordNumber < 1 || recordNumber > filtered.actualNumber);
                DeleteEntry(&entries, filtered.pEntries[recordNumber - 1]);
                unsavedChanges = 1;
                printf(ANSI_COLOR_GREEN"Entry is deleted successfully. Current number of records is %d.\n\n"ANSI_COLOR_RESET, entries.actualNumber);
            }
        }
        else if (!_stricmp(command, "MODIFY") || !_stricmp(command, "5"))
        {
            char lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for last name. If multiple records are found, you will be asked to select one.\n");
            do
            {
                printf(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET);
                GetString(lastName, sizeof(lastName));
            } while (!*lastName);

            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, "", (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = MultiSearch(pEntry, &entries);
            free(pEntry);
            if (filtered.actualNumber == 0)
                printf(ANSI_COLOR_RED"No records are found.\n\n"ANSI_COLOR_RESET);
            else
            {
                int recordNumber = 1;
                if (filtered.actualNumber > 1)
                {
                    printf("Found multiple results:\n");
                    PrintNumberedEntries(&filtered);
                    printf(ANSI_COLOR_YELLOW"Enter the number of the record (between 1 and %d) you want to modify: "ANSI_COLOR_RESET, filtered.actualNumber);

                    do
                    {
                        char numberString[5];
                        GetString(numberString, sizeof(numberString));
                        recordNumber = atoi(numberString);
                    } while (recordNumber < 1 || recordNumber > filtered.actualNumber);
                }
                printf("\tYou will be prompted for new info, leave any field blank to keep it unchanged.\n");
                PhonebookEntry *pEntry = GetEntryFromUser(true);
                ModifyRecord(filtered.pEntries[recordNumber - 1], pEntry); // This function will call free on pEntry.
                unsavedChanges = 1;
                printf(ANSI_COLOR_GREEN"Field is modified!\n\n"ANSI_COLOR_RESET);
            }
        }
        else if (!_stricmp(command, "PRINT") || !_stricmp(command, "6"))
        {
            char sortBy[2];
            printf(ANSI_COLOR_YELLOW"Enter 'L' to sort by last name, 'B' to sort by 'Birthdate', or otherwise to cancel sorting: "ANSI_COLOR_RESET);
            GetString(sortBy, sizeof(sortBy));
            if (!_stricmp(sortBy, "L"))
            {
                qsort(entries.pEntries, entries.actualNumber, sizeof(entries.pEntries[0]), CompareEntriesByLastName);
                PrintEntries(&entries);
            }
            else if (!_stricmp(sortBy, "B"))
            {
                qsort(entries.pEntries, entries.actualNumber, sizeof(entries.pEntries[0]), CompareEntriesByDate);
                PrintEntries(&entries);
            }

        }
        else if (!_stricmp(command, "SAVE") || !_stricmp(command, "7"))
        {
            SaveEntries(entries, FILE_PATH);
            printf(ANSI_COLOR_GREEN"Changes are saved!\n\n"ANSI_COLOR_RESET);
            unsavedChanges = 0;
        }
        else if (!_stricmp(command, "QUIT") || !_stricmp(command, "8"))
        {
            if (unsavedChanges)
            {
                char confirmation[4];
                printf(ANSI_COLOR_RED"WARNING: There is unsaved changes. Enter 'yes' to confirm quitting: "ANSI_COLOR_RESET);
                GetString(confirmation, sizeof(confirmation));
                if (strcmp(confirmation, "yes")) continue;
                printf("\n");
            }
            break;
        }
        else
        {
            printf(ANSI_COLOR_MAGENTA"You entered an unknown command.\n\n"ANSI_COLOR_RESET);
        }
    }

    return 0;
}

void GetString(char *buffer, int count)
{
    fgets(buffer, count, stdin);
    fseek(stdin, 0, SEEK_END);
    int length = strlen(buffer);
    if (buffer[length - 1] == '\n') buffer[length - 1] = '\0';
}


PhonebookEntry *GetEntryFromUser(bool allowEmpty)
{
    char lastName[MAX_NAME_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char dateString[11]; // 07-03-1999 (10 chars + '\0')
    // TODO: add validation to all fields.
    printf(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET);
    GetString(lastName, sizeof(lastName));
    if (!allowEmpty && lastName[0] == '\0') return NULL;

    printf(ANSI_COLOR_YELLOW"\t\tEnter first name: "ANSI_COLOR_RESET);
    GetString(firstName, sizeof(firstName));
    if (!allowEmpty && firstName[0] == '\0') return NULL;

    printf(ANSI_COLOR_YELLOW"\t\tEnter address: "ANSI_COLOR_RESET);
    GetString(address, sizeof(address));
    if (!allowEmpty && address[0] == '\0') return NULL;

    printf(ANSI_COLOR_YELLOW"\t\tEnter email: "ANSI_COLOR_RESET);
    GetString(email, sizeof(email));
    if (!allowEmpty && email[0] == '\0') return NULL;

    printf(ANSI_COLOR_YELLOW"\t\tEnter phone: "ANSI_COLOR_RESET);
    GetString(phone, sizeof(phone));
    if (!allowEmpty && phone[0] == '\0') return NULL;

    Date birthdate = { 0, 0, 0 };
    while (1)
    {
        printf(ANSI_COLOR_YELLOW"\t\tEnter birthdate on the form dd-MM-yyyy or dd/MM/yyyy: "ANSI_COLOR_RESET);
        GetString(dateString, sizeof(dateString));
        if (!allowEmpty && dateString[0] == '\0') return NULL; // Meaning to cancel.
        if (dateString[0] == '\0') break;
        if (IsValidDate(dateString, &birthdate)) break;
    }
    return ConstructPhonebookEntry(lastName, firstName, birthdate, address, email, phone);
}