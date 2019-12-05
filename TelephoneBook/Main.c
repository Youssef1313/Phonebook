#include <stdbool.h>
#include <stdio.h>
#include "Add.h"
#include "Delete.h"
#include "Load.h"
#include "PhonebookEntry.h"
#include "Query.h"

// TODO: Use:
// if (field[strlen(field) - 1] == '\n') field[strlen(field) - 1] = '\0';
// Instead of strtok to remove the newline from fgets inputs.

// Longest commands are DELETE and MODIFY (6 chars + '\0' = 7 chars).
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
    6. PRINT  -> Print the phonebook in sorted order\n\
    7. SAVE   -> Save the changes you made to the hard disk.\n\
    8. QUIT   -> Exit without saving.\n\n");
    PhonebookEntries entries = Load(NULL);

    while (1)
    {
        char command[MAX_COMMAND_LENGTH];
        printf("Enter a command: ");
        GetString(command, sizeof(command));
        if (!_stricmp(command, "LOAD") || !_stricmp(command, "1"))
        {
            entries = Load(FILE_PATH);
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
                printf("\033[32;1m Record is added.\n\n \033[0m\n");
            }
            else
                printf("\033[31;1m You've cancelled the add process.\n\n \033[0m\n");

        }
        else if (!_stricmp(command, "DELETE") || !_stricmp(command, "4"))
        {
            char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];
            printf("\tYou will be prompted for first name and last name. If multiple records are found, you will be asked to select one.\n");
            printf("\t\tEnter last name: ");
            GetString(lastName, sizeof(lastName));
            printf("\t\tEnter first name: ");
            GetString(firstName, sizeof(firstName));
            PhonebookEntry *pEntry = ConstructPhonebookEntry(lastName, firstName, (Date) { 0, 0, 0 }, "", "", "");
        }
        else if (!_stricmp(command, "MODIFY") || !_stricmp(command, "5"))
        {

        }
        else if (!_stricmp(command, "PRINT") || !_stricmp(command, "6"))
        {

        }
        else if (!_stricmp(command, "SAVE") || !_stricmp(command, "7"))
        {

        }
        else if (!_stricmp(command, "QUIT") || !_stricmp(command, "8"))
        {

        }
        else
        {
            printf("You entered an unknown command.\n\n");
        }
    }


    /*PhonebookEntry *entry = ConstructPhonebookEntry("Victor", "Youssef", date, "Sidi bishr", "MyEmail@gmail.com", "01287946618");
    printf("First name: %s\n", entry->firstName);
    printf("Last name: %s\n", entry->lastName);
    printf("Address: %s\n", entry->address);
    printf("Email: %s\n", entry->email);
    printf("Phone: %s\n", entry->phone);*/
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

    short day = 0, month = 0, year = 0;
    do
    {
        printf("\tEnter birthdate on the form dd-MM-yyyy or dd/MM/yyyy: ");
        GetString(dateString, sizeof(dateString));
        if (!allowEmpty && dateString[0] == '\0') return NULL;
        if (dateString[0] == '\0') break;
        char *dayToken = strtok(dateString, "-/");
        if (!dayToken) continue;
        day = atoi(dayToken);

        char *monthToken = strtok(NULL, "-/");
        if (!monthToken) continue;
        month = atoi(monthToken);

        char *yearToken = strtok(NULL, "-/");
        if (!yearToken) continue;
        year = atoi(yearToken);
    } while (!day || !month || !year); // TODO: Consider adding `|| !IsValid(day, month, year)` to the condition.

    return ConstructPhonebookEntry(lastName, firstName, (Date) { day, month, year }, address, email, phone);
}