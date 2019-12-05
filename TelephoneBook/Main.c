#include <stdio.h>
#include "Add.h"
#include "Delete.h"
#include "Load.h"
#include "PhonebookEntry.h"
#include "Query.h"

// TODO: Use:
// if (field[strlen(field) - 1] == '\n') field[strlen(field) - 1] == '\0';
// Instead of strtok to remove the newline from fgets inputs.

// Longest commands are DELETE and MODIFY (6 chars + '\0' = 7 chars).
#define MAX_COMMAND_LENGTH 7
#define FILE_PATH "C:\\phonebook.txt"

PhonebookEntry *GetEntryFromUser(void);

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
        fgets(command, sizeof(command), stdin);
        fseek(stdin, 0, SEEK_END);
        if (!_stricmp(command, "LOAD\n") || !_stricmp(command, "1\n"))
        {
            entries = Load(FILE_PATH);
            printf("File is loaded successfully. It has %d record(s).\n\n", entries.actualNumber);
        }
        else if (!_stricmp(command, "QUERY\n") || !_stricmp(command, "2\n"))
        {
            char lastName[MAX_NAME_LENGTH];
            printf("Enter last name to search for: ");
            fgets(lastName, MAX_NAME_LENGTH, stdin);
            fseek(stdin, 0, SEEK_END);
            strtok(lastName, "\n");
            PhonebookEntries filtered = Search(lastName, &entries);
            PrintEntries(&filtered);
        }
        else if (!_stricmp(command, "ADD\n") || !_stricmp(command, "3\n"))
        {
            AddEntry(&entries, GetEntryFromUser());
        }
        else if (!_stricmp(command, "DELETE") || !_stricmp(command, "4\n"))
        {

        }
        else if (!_stricmp(command, "MODIFY") || !_stricmp(command, "5\n"))
        {

        }
        else if (!_stricmp(command, "PRINT\n") || !_stricmp(command, "6\n"))
        {

        }
        else if (!_stricmp(command, "SAVE\n") || !_stricmp(command, "7\n"))
        {

        }
        else if (!_stricmp(command, "QUIT\n") || !_stricmp(command, "8\n"))
        {

        }
        else
        {
            printf("You entered an unknown command.\n");
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


PhonebookEntry *GetEntryFromUser(void)
{
    char lastName[MAX_NAME_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char dateString[11]; // 07-03-1999 (10 chars + '\0')
    // TODO: add validation to all fields.
    printf("When prompted to any field, leaving it empty will result in add cancellation.\n");
    printf("\tEnter last name: ");
    fgets(lastName, sizeof(lastName), stdin);
    fseek(stdin, 0, SEEK_END);
    if (strlen(lastName) == 1) return NULL;
    strtok(lastName, "\n");

    printf("\tEnter first name: ");
    fgets(firstName, sizeof(firstName), stdin);
    fseek(stdin, 0, SEEK_END);
    if (strlen(firstName) == 1) return NULL;
    strtok(firstName, "\n");

    printf("\tEnter address: ");
    fgets(address, sizeof(address), stdin);
    fseek(stdin, 0, SEEK_END);
    if (strlen(address) == 1) return NULL;
    strtok(address, "\n");

    printf("\tEnter email: ");
    fgets(email, sizeof(email), stdin);
    fseek(stdin, 0, SEEK_END);
    if (strlen(email) == 1) return NULL;
    strtok(email, "\n");

    printf("\tEnter phone: ");
    fgets(phone, sizeof(phone), stdin);
    fseek(stdin, 0, SEEK_END);
    if (strlen(phone) == 1) return NULL;
    strtok(phone, "\n");

    short day, month, year;
    do
    {
        printf("\tEnter birthdate on the form dd-MM-yyyy or dd/MM/yyyy (Leave blank to cancel adding the phonebook entry): ");
        fgets(dateString, sizeof(dateString), stdin);
        fseek(stdin, 0, SEEK_END);
        if (strlen(dateString) == 1) return NULL;
        strtok(dateString, "\n");

        day = atoi(strtok(dateString, "-/"));
        month = atoi(strtok(NULL, "-/"));
        year = atoi(strtok(NULL, "-/"));
    } while (!day || !month || !year); // TODO: Consider adding `|| !IsValid(day, month, year)` to the condition.
   
    return ConstructPhonebookEntry(lastName, firstName, (Date){ day, month, year }, address, email, phone);
}