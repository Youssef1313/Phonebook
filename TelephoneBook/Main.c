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
void GetString(char *prompt, char *buffer, int count);
PhonebookEntry *SelectEntry(PhonebookEntries *pEntries);

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
    bool unsavedChanges = false;
    while (1)
    {
        char command[MAX_COMMAND_LENGTH];
        GetString(ANSI_COLOR_YELLOW"Enter a command: "ANSI_COLOR_RESET, command, sizeof(command));
        if (!_stricmp(command, "LOAD") || !_stricmp(command, "1"))
        {
            PhonebookEntries tempEntries = Load(FILE_PATH);
            if (tempEntries.actualNumber >= 0) // Load returns -1 if reading the file has failed.
            {
                entries = tempEntries;
                unsavedChanges = false;
                printf(ANSI_COLOR_GREEN"File is loaded successfully. It has %d record(s).\n\n"ANSI_COLOR_RESET, entries.actualNumber);
            }
            else
                printf(ANSI_COLOR_RED"Unable to read the file. Make sure the file exists, then run the LOAD command again.\n\n"ANSI_COLOR_RESET);
        }
        else if (!_stricmp(command, "QUERY") || !_stricmp(command, "2"))
        {
            printf("\tWhen prompted to any field, leaving it empty means it won't be used in searching.\n");
            PhonebookEntry *pSearchEntry = GetEntryFromUser(true);
            PhonebookEntries filtered = Search(pSearchEntry, &entries);
            PrintEntries(&filtered, false);
            free(pSearchEntry);
        }
        else if (!_stricmp(command, "ADD") || !_stricmp(command, "3"))
        {
            printf("\tWhen prompted to any field, leaving it empty will result in cancelling adding this record.\n");
            PhonebookEntry *pNewEntry = GetEntryFromUser(false);
            if (pNewEntry)
            {
                AddEntry(&entries, pNewEntry);
                unsavedChanges = true;
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
                GetString(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET, lastName, sizeof(lastName));
            } while (!*lastName);

            do
            {
                GetString(ANSI_COLOR_YELLOW"\t\tEnter first name: "ANSI_COLOR_RESET, firstName, sizeof(firstName));
            } while (!*firstName);
            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, firstName, (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = Search(pEntry, &entries);
            free(pEntry);

            if (filtered.actualNumber == 0)
                printf(ANSI_COLOR_RED"No records are found.\n\n"ANSI_COLOR_RESET);
            else
            {
                DeleteEntry(&entries, SelectEntry(&filtered));
                unsavedChanges = true;
                printf(ANSI_COLOR_GREEN"Entry is deleted successfully. Current number of records is %d.\n\n"ANSI_COLOR_RESET, entries.actualNumber);
            }
            free(filtered.pEntries); // Ignore the compile-warning, the memory is initialized in Search.
        }
        else if (!_stricmp(command, "MODIFY") || !_stricmp(command, "5"))
        {
            char lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for last name. If multiple records are found, you will be asked to select one.\n");
            do
            {
                GetString(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET, lastName, sizeof(lastName));
            } while (!*lastName);

            PhonebookEntry *pEntryForSearch = ConstructPhonebookEntry(lastName, "", (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = Search(pEntryForSearch, &entries);
            free(pEntryForSearch);
            if (filtered.actualNumber == 0)
                printf(ANSI_COLOR_RED"No records are found.\n\n"ANSI_COLOR_RESET);
            else
            {
                PhonebookEntry *pEntryToModify = SelectEntry(&filtered);
                printf("\tYou will be prompted for new info, leave any field blank to keep it unchanged.\n");
                PhonebookEntry *pNewEntry = GetEntryFromUser(true);
                ModifyRecord(pEntryToModify, pNewEntry); // This function will call free on pNewEntry.
                unsavedChanges = true;
                printf(ANSI_COLOR_GREEN"Field is modified!\n\n"ANSI_COLOR_RESET);
            }
            free(filtered.pEntries); // Ignore the compile-warning, the memory is initialized in Search.
        }
        else if (!_stricmp(command, "PRINT") || !_stricmp(command, "6"))
        {
            char sortBy[2];
            GetString(ANSI_COLOR_YELLOW"Enter 'L' to sort by last name, 'B' to sort by 'Birthdate', or otherwise to cancel sorting: "ANSI_COLOR_RESET, sortBy, sizeof(sortBy));
            if (!_stricmp(sortBy, "L"))
            {
                qsort(entries.pEntries, entries.actualNumber, sizeof(entries.pEntries[0]), CompareEntriesByLastName);
                PrintEntries(&entries, false);
            }
            else if (!_stricmp(sortBy, "B"))
            {
                qsort(entries.pEntries, entries.actualNumber, sizeof(entries.pEntries[0]), CompareEntriesByDate);
                PrintEntries(&entries, false);
            }

        }
        else if (!_stricmp(command, "SAVE") || !_stricmp(command, "7"))
        {
            SaveEntries(entries, FILE_PATH);
            printf(ANSI_COLOR_GREEN"Changes are saved!\n\n"ANSI_COLOR_RESET);
            unsavedChanges = false;
        }
        else if (!_stricmp(command, "QUIT") || !_stricmp(command, "8"))
        {
            if (unsavedChanges)
            {
                char confirmation[4];
                GetString(ANSI_COLOR_RED"WARNING: There is unsaved changes. Enter 'yes' to confirm quitting: "ANSI_COLOR_RESET, confirmation, sizeof(confirmation));
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

void GetString(char *prompt, char *buffer, int count)
{
    bool firstTime = true;
    printf(prompt);
    do
    {
        if (!firstTime) printf(ANSI_COLOR_RED"Commas not allowed. Re-enter: "ANSI_COLOR_RESET);
        fgets(buffer, count, stdin);
        fseek(stdin, 0, SEEK_END);
        int length = strlen(buffer);
        if (buffer[length - 1] == '\n') buffer[length - 1] = '\0';
        firstTime = false;
    } while (StringContains(buffer, ','));
}

PhonebookEntry *SelectEntry(PhonebookEntries *pEntries)
{
    int recordNumber = 1;
    if (pEntries->actualNumber > 1)
    {
        printf(ANSI_COLOR_BLUE"Found multiple results:\n"ANSI_COLOR_RESET);
        PrintEntries(pEntries, true);
        do
        {
            printf(ANSI_COLOR_YELLOW"Enter the number of the record (between 1 and %d) you want to delete: "ANSI_COLOR_RESET, pEntries->actualNumber);
            char numberString[5];
            GetString("", numberString, sizeof(numberString));
            recordNumber = atoi(numberString);
        } while (recordNumber < 1 || recordNumber > pEntries->actualNumber);
    }
    return pEntries->pEntries[recordNumber - 1];
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

    GetString(ANSI_COLOR_YELLOW"\t\tEnter last name: "ANSI_COLOR_RESET, lastName, sizeof(lastName));
    if (!allowEmpty && lastName[0] == '\0') return NULL;

    GetString(ANSI_COLOR_YELLOW"\t\tEnter first name: "ANSI_COLOR_RESET, firstName, sizeof(firstName));
    if (!allowEmpty && firstName[0] == '\0') return NULL;

    while (true)
    {
        GetString(ANSI_COLOR_YELLOW"\t\tEnter address: "ANSI_COLOR_RESET, address, sizeof(address));
        if (!allowEmpty && address[0] == '\0') return NULL;
        if (address[0] == '\0') break;
        if (IsValidPhone(email)) break;
    }


    while (true)
    {
        GetString(ANSI_COLOR_YELLOW"\t\tEnter email: "ANSI_COLOR_RESET, email, sizeof(email));
        if (!allowEmpty && email[0] == '\0') return NULL;
        if (email[0] == '\0') break;
        if (IsValidEmail(email)) break;
    }


    GetString(ANSI_COLOR_YELLOW"\t\tEnter phone: "ANSI_COLOR_RESET, phone, sizeof(phone));
    if (!allowEmpty && phone[0] == '\0') return NULL;

    Date birthdate = { 0, 0, 0 };
    while (true)
    {
        GetString(ANSI_COLOR_YELLOW"\t\tEnter birthdate on the form dd-MM-yyyy or dd/MM/yyyy: "ANSI_COLOR_RESET, dateString, sizeof(dateString));
        if (!allowEmpty && dateString[0] == '\0') return NULL; // Meaning to cancel.
        if (dateString[0] == '\0') break;
        if (IsValidDate(dateString, &birthdate)) break;
    }
    return ConstructPhonebookEntry(lastName, firstName, birthdate, address, email, phone);
}