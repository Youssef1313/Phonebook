#include <stdio.h>
#include "PhonebookEntry.h"
#include "Loader.h"
#include "Query.h"

int main(void)
{
    PhonebookEntries x = Load("C:\\phonebook.txt");
    PhonebookEntries y = Search("aiman", x);
    for (int i = 0; i < y.actualNumber; i++)
    {
        printf("First name:%s\n", y.pEntries[i]->firstName);
        printf("Last name:%s\n", y.pEntries[i]->lastName);
        printf("Address: %s\n", y.pEntries[i]->address);
        printf("Email: %s\n\n", y.pEntries[i]->email);
    }

    /*PhonebookEntry *entry = ConstructPhonebookEntry("Victor", "Youssef", date, "Sidi bishr", "MyEmail@gmail.com", "01287946618");
    printf("First name: %s\n", entry->firstName);
    printf("Last name: %s\n", entry->lastName);
    printf("Address: %s\n", entry->address);
    printf("Email: %s\n", entry->email);
    printf("Phone: %s\n", entry->phone);*/
    return 0;
}