#include <stdio.h>
#include <string.h>
#include "budget.h"

int    deptCount = 0;
char   deptName[MAX_DEPTS][TEXT_LEN];
double deptAllocated[MAX_DEPTS];
double deptSpent[MAX_DEPTS];

int findDepartment(const char *name)
{
    int i;
    for (i = 0; i < deptCount; i++)
        if (equalsIgnoreCase(deptName[i], name)) return i;
    return -1;
}

double calculateRemaining(double allocated, double spent)
{
    return allocated - spent;
}

int isWithinBudget(double allocated, double spent)
{
    return spent <= allocated;
}

void addDepartmentBudget(void)
{
    if (deptCount >= MAX_DEPTS) { printf("  [!] Department list full.\n"); return; }
    char name[TEXT_LEN];
    printf("\n--- Enter Departmental Budget ---\n");
    for (;;) {
        readNonEmpty("Department name: ", name, sizeof name);
        if (findDepartment(name) != -1) printf("  [!] Department already has a budget.\n");
        else break;
    }
    strcpy(deptName[deptCount], name);
    deptAllocated[deptCount] = readMoney("Allocated budget (N$): ");
    deptSpent[deptCount] = 0.0;
    deptCount++;
    printf("  Budget saved for '%s'.\n", name);
}

void recordExpenditure(void)
{
    char name[TEXT_LEN];
    printf("\n--- Enter Expenditure ---\n");
    if (deptCount == 0) { printf("  [!] Add a departmental budget first.\n"); return; }
    readNonEmpty("Department name: ", name, sizeof name);
    int i = findDepartment(name);
    if (i == -1) { printf("  [!] Department not found.\n"); return; }
    double amt = readMoney("Expenditure amount (N$): ");
    deptSpent[i] += amt;
    printf("  Recorded. Total spent: N$%.2f\n", deptSpent[i]);
    if (!isWithinBudget(deptAllocated[i], deptSpent[i]))
        printf("  [WARNING] %s has now EXCEEDED its budget!\n", deptName[i]);
}

void displayBudgets(void)
{
    int i;
    printf("\n--- Budget Information ---\n");
    if (deptCount == 0) { printf("  No budgets entered.\n"); return; }
    for (i = 0; i < deptCount; i++) {
        double rem = calculateRemaining(deptAllocated[i], deptSpent[i]);
        printf("\nDepartment:       %s\n", deptName[i]);
        printf("Allocated Budget: N$%.2f\n", deptAllocated[i]);
        printf("Expenditure:      N$%.2f\n", deptSpent[i]);
        printf("Remaining Budget: N$%.2f\n", rem);
        printf("Status:           %s\n",
               isWithinBudget(deptAllocated[i], deptSpent[i]) ? "WITHIN BUDGET" : "OVER BUDGET");
    }
}

void displayOverBudget(void)
{
    int i, found = 0;
    printf("\n--- Departments Over Budget ---\n");
    for (i = 0; i < deptCount; i++) {
        if (!isWithinBudget(deptAllocated[i], deptSpent[i])) {
            printf("  %-20s over by N$%.2f\n", deptName[i],
                   -calculateRemaining(deptAllocated[i], deptSpent[i]));
            found++;
        }
    }
    if (!found) printf("  No department has exceeded its budget.\n");
}

void budgetMenu(void)
{
    int c;
    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter departmental budget\n2. Enter expenditure\n3. Display budgets\n");
        printf("4. Show departments over budget\n5. Back to main menu\n");
        c = readInt("Enter your choice: ", 1, 5);
        switch (c) {
            case 1: addDepartmentBudget(); break;
            case 2: recordExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: displayOverBudget(); break;
            default: break;
        }
    } while (c != 5);
}
