#define _CRT_SECURE_NO_WARNINGS // Disable strcpy errors. TODO: Check a more secured way.

#include <stdio.h>
#include "PhonebookEntry.h"

int main(void)
{
	Date date = { 7, 3, 1999 };
	PhonebookEntry *entry = ConstructPhonebookEntry("Victor", "Youssef", date, "Sidi bishr", "MyEmail@gmail.com", "01287946618");
	printf("First name: %s\n", entry->firstName);
	printf("Last name: %s\n", entry->lastName);
	printf("Address: %s\n", entry->address);
	printf("Email: %s\n", entry->email);
	printf("Phone: %s\n", entry->phone);

	return 0;
}