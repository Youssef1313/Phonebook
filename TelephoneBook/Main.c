#include <stdio.h>
#include "PhonebookEntry.h"
#include "Loader.h"
int main(void)
{
    int n;
    PhonebookEntry **x = Load("C:\\phonebook.txt", &n);
    for (int i = 0; i < n; i++)
    {
        printf("First name:%s\n", x[i]->firstName);
        printf("Last name:%s\n", x[i]->lastName);
        printf("Address: %s\n", x[i]->address);
        printf("Email: %s\n", x[i]->email);
    }
    /*PhonebookEntry *entry = ConstructPhonebookEntry("Victor", "Youssef", date, "Sidi bishr", "MyEmail@gmail.com", "01287946618");
    printf("First name: %s\n", entry->firstName);
    printf("Last name: %s\n", entry->lastName);
    printf("Address: %s\n", entry->address);
    printf("Email: %s\n", entry->email);
    printf("Phone: %s\n", entry->phone);*/
    return 0;
}