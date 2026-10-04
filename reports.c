/*
 * reports.c - Reports module for the Municipal Financial Management System
 * Responsibility: Student 5 (Reports)
 *
 * Reads the data stored by the other modules (employees.c, budget.c,
 * suppliers.c, assets.c) and prints summary reports.
 */

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* ------------------------------------------------------------------
 * BUDGET and SUPPLIER data names.
 * If the budget/supplier modules use different variable names, change
 * ONLY the right-hand side of these lines to match budget.h/suppliers.h.
 * ------------------------------------------------------------------ */
#define BUD_COUNT      budgetCount
#define BUD_DEPT(i)    budgetDept[i]
#define BUD_ALLOC(i)   budgetAllocated[i]
#define BUD_SPENT(i)   budgetSpent[i]

#define SUP_COUNT      supplierCount
#define SUP_ID(i)      supplierId[i]
#define SUP_NAME(i)    supplierName[i]
#define SUP_EMAIL(i)   supplierEmail[i]
#define SUP_PHONE(i)   supplierPhone[i]
#define SUP_TOWN(i)    supplierTown[i]

/* ---------- Employee Report ---------- */

void employeeReport(void)
{
    int i, highIdx = 0, lowIdx = 0;
    double gross, total = 0.0, high, low;
    char highName[NAME_LEN], lowName[NAME_LEN];

    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (empCount <= 0) {
        printf("No employees have been registered yet.\n");
        return;
    }

    high = low = calculateGross(empBasic[0], empHousing[0], empTransport[0]);

    for (i = 0; i < empCount; i++) {
        gross = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
        total += gross;
        if (gross > high) { high = gross; highIdx = i; }
        if (gross < low)  { low  = gross; lowIdx  = i; }
    }

    strcpy(highName, empName[highIdx]);
    strcpy(lowName,  empName[lowIdx]);

    printf("Total Employees: %d\n", empCount);
    printf("Average Salary : N$%.2f\n", total / empCount);
    printf("Highest Salary : N$%.2f (%s)\n", high, highName);
    printf("Lowest Salary  : N$%.2f (%s)\n", low, lowName);

    printf("\n%-12s %-22s %-18s %12s\n", "ID", "Name", "Department", "Gross (N$)");
    printLine('-', 68);
    for (i = 0; i < empCount; i++) {
        printf("%-12s %-22s %-18s %12.2f\n", empId[i], empName[i], empDept[i],
               calculateGross(empBasic[i], empHousing[i], empTransport[i]));
    }
}

/* ---------- Budget Report ---------- */

void budgetReport(void)
{
    int i, exceeded = 0;
    double totalAllocated = 0.0, totalSpent = 0.0, remaining;

    printf("\n========== BUDGET REPORT ==========\n");

    if (BUD_COUNT <= 0) {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    printf("%-18s %14s %14s %14s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printLine('-', 76);

    for (i = 0; i < BUD_COUNT; i++) {
        remaining = BUD_ALLOC(i) - BUD_SPENT(i);
        totalAllocated += BUD_ALLOC(i);
        totalSpent += BUD_SPENT(i);

        printf("%-18s %14.2f %14.2f %14.2f  %s\n", BUD_DEPT(i), BUD_ALLOC(i),
               BUD_SPENT(i), remaining,
               (remaining < 0) ? "OVER BUDGET" : "WITHIN BUDGET");

        if (remaining < 0)
            exceeded++;
    }

    printLine('-', 76);
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Total Remaining Budget : N$%.2f\n", totalAllocated - totalSpent);

    if (exceeded == 0) {
        printf("Departments exceeding budget: None\n");
    } else {
        printf("Departments exceeding budget (%d):\n", exceeded);
        for (i = 0; i < BUD_COUNT; i++) {
            if (BUD_SPENT(i) > BUD_ALLOC(i))
                printf("  - %s (over by N$%.2f)\n", BUD_DEPT(i),
                       BUD_SPENT(i) - BUD_ALLOC(i));
        }
    }
}

/* ---------- Supplier Report ---------- */

void supplierReport(void)
{
    int i;

    printf("\n========== SUPPLIER REPORT ==========\n");

    if (SUP_COUNT <= 0) {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("%-12s %-20s %-24s %-14s %-12s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 84);
    for (i = 0; i < SUP_COUNT; i++) {
        printf("%-12s %-20s %-24s %-14s %-12s\n", SUP_ID(i), SUP_NAME(i),
               SUP_EMAIL(i), SUP_PHONE(i), SUP_TOWN(i));
    }
    printf("\nTotal Suppliers: %d\n", SUP_COUNT);
}

/* ---------- Asset Report ---------- */

void assetReport(void)
{
    int i, poorCount = 0;
    double totalValue = 0.0;

    printf("\n========== ASSET REPORT ==========\n");

    if (assetCount <= 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("%-12s %-18s %-12s %12s %-14s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', 82);
    for (i = 0; i < assetCount; i++) {
        printf("%-12s %-18s %-12s %12.2f %-14s %-10s\n", assetId[i],
               assetName[i], assetType[i], assetValue[i], assetDept[i],
               assetCondition[i]);

        totalValue += assetValue[i];
        if (equalsIgnoreCase(assetCondition[i], "Poor"))   /* needs attention */
            poorCount++;
    }

    printf("\nTotal Assets      : %d\n", assetCount);
    printf("Total Asset Value : N$%.2f\n", totalValue);
    printf("Assets in Poor condition: %d\n", poorCount);
}

/* ---------- Reports menu ---------- */

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("               REPORTS MENU\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: employeeReport(); pauseScreen(); break;
            case 2: budgetReport();   pauseScreen(); break;
            case 3: supplierReport(); pauseScreen(); break;
            case 4: assetReport();    pauseScreen(); break;
            default: break;   /* 5 = back; readInt rejects anything else */
        }
    } while (choice != 5);
}
