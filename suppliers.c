#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

int supplierCount = 0;
char supplierId[MAX_SUPPLIERS][ID_LEN];
char supplierName[MAX_SUPPLIERS][NAME_LEN];
char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
char supplierTown[MAX_SUPPLIERS][TEXT_LEN];

int findSupplierById(const char *id)
{
    int i;

    for (i = 0; i < supplierCount; i++)
        if (strcmp(supplierId[i], id) == 0) return i;

    return -1;
}

static int validEmail(const char *email)
{
    int i, at = -1, dot = -1;

    if (strlen(email) < 5) return 0;

    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            if (at != -1) return 0;
            at = i;
        }

        if (email[i] == '.' && at != -1 && i > at + 1)
            dot = i;
    }

    if (at <= 0 || dot <= at + 1 || email[dot + 1] == '\0') return 0;
    return 1;
}

static int validPhone(const char *phone)
{
    int i, digits = 0;

    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char)phone[i]))
            digits++;
        else if (phone[i] == ' ' || phone[i] == '-')
            continue;
        else if (phone[i] == '+' && i == 0)
            continue;
        else
            return 0;
    }

    return digits >= 7 && digits <= 15;
}

static void printSupplierDetail(int i)
{
    printf("\n ID: %s\n", supplierId[i]);
    printf(" Name: %s\n", supplierName[i]);
    printf(" Email: %s\n", supplierEmail[i]);
    printf(" Telephone: %s\n", supplierPhone[i]);
    printf(" Town: %s\n", supplierTown[i]);
}

void addSupplier(void)
{
    char id[ID_LEN];
    int n;

    if (supplierCount >= MAX_SUPPLIERS) {
        printf(" [!] Supplier list is full.\n");
        return;
    }

    printf("\n--- Add Supplier ---\n");

    for (;;) {
        readNonEmpty("Supplier ID: ", id, sizeof id);
        if (findSupplierById(id) != -1)
            printf(" [!] ID '%s' already exists.\n", id);
        else
            break;
    }

    n = supplierCount;
    strcpy(supplierId[n], id);
    readNonEmpty("Supplier name: ", supplierName[n], NAME_LEN);

    for (;;) {
        readNonEmpty("Email: ", supplierEmail[n], EMAIL_LEN);
        if (validEmail(supplierEmail[n])) break;
        printf(" [!] Please enter a valid email address.\n");
    }

    for (;;) {
        readNonEmpty("Telephone number: ", supplierPhone[n], PHONE_LEN);
        if (validPhone(supplierPhone[n])) break;
        printf(" [!] Please enter a valid telephone number.\n");
    }

    readNonEmpty("Town/Location: ", supplierTown[n], TEXT_LEN);

    supplierCount++;
    printf(" Supplier '%s' added successfully.\n", supplierName[n]);
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- Supplier List (%d) ---\n", supplierCount);

    if (supplierCount == 0) {
        printf(" No suppliers registered.\n");
        return;
    }

    printf("%-10s %-22s %-28s %-18s %-16s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 98);

    for (i = 0; i < supplierCount; i++)
        printf("%-10s %-22s %-28s %-18s %-16s\n",
               supplierId[i], supplierName[i], supplierEmail[i],
               supplierPhone[i], supplierTown[i]);
}

void searchSupplier(void)
{
    char key[NAME_LEN];
    int i, found = 0;

    printf("\n--- Search Supplier ---\n");
    readNonEmpty("Enter ID, name or town: ", key, sizeof key);

    for (i = 0; i < supplierCount; i++) {
        if (strcmp(supplierId[i], key) == 0 ||
            containsIgnoreCase(supplierName[i], key) ||
            containsIgnoreCase(supplierTown[i], key)) {
            printSupplierDetail(i);
            found++;
        }
    }

    if (!found)
        printf(" No supplier matches '%s'.\n", key);
    else
        printf("\n %d record(s) found.\n", found);
}

void compareSuppliers(void)
{
    char firstId[ID_LEN], secondId[ID_LEN];
    int first, second, result;

    if (supplierCount < 2) {
        printf(" At least two suppliers are needed for comparison.\n");
        return;
    }

    printf("\n--- Compare Suppliers ---\n");
    readNonEmpty("First supplier ID: ", firstId, sizeof firstId);
    readNonEmpty("Second supplier ID: ", secondId, sizeof secondId);

    first = findSupplierById(firstId);
    second = findSupplierById(secondId);

    if (first == -1 || second == -1) {
        printf(" [!] One or both supplier IDs were not found.\n");
        return;
    }

    printf("\nFirst supplier:\n");
    printSupplierDetail(first);
    printf("\nSecond supplier:\n");
    printSupplierDetail(second);

    if (equalsIgnoreCase(supplierTown[first], supplierTown[second]))
        printf("\nBoth suppliers are in %s.\n", supplierTown[first]);
    else
        printf("\nThe suppliers are in different towns.\n");

    result = strcmp(supplierName[first], supplierName[second]);

    if (result == 0)
        printf("The supplier names are the same.\n");
    else if (result < 0)
        printf("%s comes before %s alphabetically.\n",
               supplierName[first], supplierName[second]);
    else
        printf("%s comes before %s alphabetically.\n",
               supplierName[second], supplierName[first]);
}

void supplierMenu(void)
{
    int c;

    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add supplier\n2. Display suppliers\n3. Search supplier\n");
        printf("4. Compare suppliers\n5. Back to main menu\n");

        c = readInt("Enter your choice: ", 1, 5);

        switch (c) {
        case 1: addSupplier(); break;
        case 2: displaySuppliers(); break;
        case 3: searchSupplier(); break;
        case 4: compareSuppliers(); break;
        default: break;
        }
    } while (c != 5);
}
