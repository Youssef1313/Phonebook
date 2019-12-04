#include <stdio.h>
#include "PhonebookEntry.h"
#include "Loader.h"
#include "Query.h"

int main(void)
{
    int n;
    int n2;
    PhonebookEntry **x = Load("C:\\phonebook.txt", &n);
    PhonebookEntry **y = Search("aiman", x, n, &n2);
    for (int i = 0; i < n2; i++)
    {
        printf("First name:%s\n", y[i]->firstName);
        printf("Last name:%s\n", y[i]->lastName);
        printf("Address: %s\n", y[i]->address);
        printf("Email: %s\n", y[i]->email);
    }

    /*PhonebookEntry *entry = ConstructPhonebookEntry("Victor", "Youssef", date, "Sidi bishr", "MyEmail@gmail.com", "01287946618");
    printf("First name: %s\n", entry->firstName);
    printf("Last name: %s\n", entry->lastName);
    printf("Address: %s\n", entry->address);
    printf("Email: %s\n", entry->email);
    printf("Phone: %s\n", entry->phone);*/
    return 0;
}