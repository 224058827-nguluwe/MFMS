#include <stdio.h>
#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void displayMenu(void)
{
    printf("\n");
    printLine('=', 40);
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printLine('=', 40);
    printf("1. Employee Management\n2. Budget Management\n3. Supplier Management\n");
    printf("4. Asset Management\n5. Reports\n6. Exit\n");
}

int main(void)
{
    int choice;
    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);
        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu();   break;
            case 3: supplierMenu(); break;
            case 4: assetMenu();    break;
            case 5: reportsMenu();  break;
            case 6: printf("\nThank you for using MFMS. Goodbye!\n"); break;
        }
    } while (choice != 6);
    return 0;
}
