#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Add.h"
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
#define FILE_PATH "C:\\phonebook.txt"

PhonebookEntry *GetEntryFromUser(bool allowEmpty);
void GetString(char *buffer, int count);

int main(void)
{
    printf("Welcome to phonebook program.\n\
The following is a list of the allowed commands to run the program:\n\n\
    1. LOAD   -> Loads the phonebook from hard disk.\n\
    2. QUERY  -> Search by last name.\n\
    3. ADD    -> Add new entry to phonebook.\n\
    4. DELETE -> Deletes an entry by providing first and last name.\n\
    5. MODIFY -> Modify a record.\n\
    6. PRINT  -> Print the phonebook in sorted order.\n\
    7. SAVE   -> Save the changes you made to the hard disk.\n\
    8. QUIT   -> Exit without saving.\n\n");
    PhonebookEntries entries = Load(NULL);
    int unsavedChanges = 0;
    while (1)
    {
        char command[MAX_COMMAND_LENGTH];
        printf("Enter a command: ");
        GetString(command, sizeof(command));
        if (!_stricmp(command, "LOAD") || !_stricmp(command, "1"))
        {
            entries = Load(FILE_PATH);
            unsavedChanges = 0;
            printf("File is loaded successfully. It has %d record(s).\n\n", entries.actualNumber);
        }
        else if (!_stricmp(command, "QUERY") || !_stricmp(command, "2"))
        {
            printf("When prompted to any field, leaving it empty means it won't be used in searching.\n");
            PhonebookEntry *pSearchEntry = GetEntryFromUser(true);
            PhonebookEntries filtered = MultiSearch(pSearchEntry, &entries);
            PrintEntries(&filtered);
            free(pSearchEntry);
        }
        else if (!_stricmp(command, "ADD") || !_stricmp(command, "3"))
        {
            printf("When prompted to any field, leaving it empty will result in cancelling adding this record.\n");
            PhonebookEntry *pNewEntry = GetEntryFromUser(false);
            if (pNewEntry)
            {
                AddEntry(&entries, pNewEntry);
                unsavedChanges = 1;
                printf("\033[32;1m Record is added.\n\n \033[0m\n");
            }
            else
                printf("\033[31;1m You've cancelled the add process.\n\n \033[0m\n");

        }
        else if (!_stricmp(command, "DELETE") || !_stricmp(command, "4"))
        {
            char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for first and last name. If multiple records are found, you will be asked to select one.\n");
            do
            {
                printf("\t\tEnter last name: ");
                GetString(lastName, sizeof(lastName));
            } while (!*lastName);

            do
            {
                printf("\t\tEnter first name: ");
                GetString(firstName, sizeof(firstName));
            } while (!*firstName);
            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, firstName, (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = MultiSearch(pEntry, &entries);
            if (filtered.actualNumber == 0)
                printf("No records are found.\n\n");
            else if (filtered.actualNumber == 1)
            {
                DeleteEntry(&entries, filtered.pEntries[0]);
                unsavedChanges = 1;
                printf("Entry is deleted successfully. Current number of records is %d.\n\n", entries.actualNumber);
            }
            else
            {
                printf("Found multiple results:\n");
                PrintNumberedEntries(&filtered);
                printf("Enter the number of the record (between 1 and %d) you want to delete: ", filtered.actualNumber);
                int recordNumber = 0;
                do
                {
                    char numberString[5];
                    GetString(numberString, sizeof(numberString));
                    recordNumber = atoi(numberString);
                } while (recordNumber < 1 || recordNumber > filtered.actualNumber);
                DeleteEntry(&entries, filtered.pEntries[recordNumber - 1]);
                unsavedChanges = 1;
                printf("Entry is deleted successfully. Current number of records is %d.\n\n", entries.actualNumber);
            }
        }
        else if (!_stricmp(command, "MODIFY") || !_stricmp(command, "5"))
        {
            char lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for last name. If multiple records are found, you will be asked to select one.\n");
            do
            {
                printf("\t\tEnter last name: ");
                GetString(lastName, sizeof(lastName));
            } while (!*lastName);

            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, "", (Date) { 0, 0, 0 }, "", "", "");
            PhonebookEntries filtered = MultiSearch(pEntry, &entries);
            free(pEntry);
            if (filtered.actualNumber == 0)
                printf("No records are found.\n\n");
            else if (filtered.actualNumber == 1)
            {
                printf("You will be prompted for new info, leave any field blank to keep it unchanged.\n");
                PhonebookEntry *pEntry = GetEntryFromUser(true);
                ModifyRecord(filtered.pEntries[0], pEntry); // This function will call free on pEntry.
                unsavedChanges = 1;
                printf("Field is modified!\n\n");
            }
            else
            {
                printf("Found multiple results:\n");
                PrintNumberedEntries(&filtered);
                printf("Enter the number of the record (between 1 and %d) you want to modify: ", filtered.actualNumber);
                int recordNumber = 0;
                do
                {
                    char numberString[5];
                    GetString(numberString, sizeof(numberString));
                    recordNumber = atoi(numberString);
                } while (recordNumber < 1 || recordNumber > filtered.actualNumber);

                printf("You will be prompted for new info, leave any field blank to keep it unchanged.\n");
                PhonebookEntry *pEntry = GetEntryFromUser(true);
                ModifyRecord(filtered.pEntries[recordNumber - 1], pEntry); // This function will call free on pEntry.
                unsavedChanges = 1;
                printf("Field is modified!\n\n");
            }
        }
        else if (!_stricmp(command, "PRINT") || !_stricmp(command, "6"))
        {
            printf("SORT!\n");
        }
        else if (!_stricmp(command, "SAVE") || !_stricmp(command, "7"))
        {
            SaveEntries(entries, FILE_PATH);
            printf("Changes are saved!\n\n");
            unsavedChanges = 0;
        }
        else if (!_stricmp(command, "QUIT") || !_stricmp(command, "8"))
        {
            if (unsavedChanges)
            {
                char confirmation[4];
                printf("WARNING: There is unsaved changes. Enter 'yes' to confirm quitting: ");
                GetString(confirmation, sizeof(confirmation));
                if (strcmp(confirmation, "yes")) continue;
            }
            break;
        }
        else
        {
            printf("You entered an unknown command.\n\n");
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
    printf("\tEnter last name: ");
    GetString(lastName, sizeof(lastName));
    if (!allowEmpty && lastName[0] == '\0') return NULL;

    printf("\tEnter first name: ");
    GetString(firstName, sizeof(firstName));
    if (!allowEmpty && firstName[0] == '\0') return NULL;

    printf("\tEnter address: ");
    GetString(address, sizeof(address));
    if (!allowEmpty && address[0] == '\0') return NULL;

    printf("\tEnter email: ");
    GetString(email, sizeof(email));
    if (!allowEmpty && email[0] == '\0') return NULL;

    printf("\tEnter phone: ");
    GetString(phone, sizeof(phone));
    if (!allowEmpty && phone[0] == '\0') return NULL;

    Date birthdate;
    while (1)
    {
        printf("\tEnter birthdate on the form dd-MM-yyyy or dd/MM/yyyy: ");
        GetString(dateString, sizeof(dateString));
        if (!allowEmpty && dateString[0] == '\0') return NULL; // Meaning to cancel.
        if (dateString[0] == '\0') break;
        if (IsValidDate(dateString, &birthdate)) break;
    }
    return ConstructPhonebookEntry(lastName, firstName, birthdate, address, email, phone);
}