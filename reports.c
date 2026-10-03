/*
 * reports.c - Reports module for the Municipal Financial Management System
 * Responsibility: Student 5 (Reports)
 */

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "reports.h"

/* ---------- helper functions (private to this file) ---------- */

/* Gross salary = basic salary + housing allowance + transport allowance */
static double grossSalary(const Employee *e)
{
    return e->basicSalary + e->housingAllowance + e->transportAllowance;
}

/* ---------- Employee Report ---------- */

void employeeReport(const Employee emp[], int count)
{
    int i;
    int highIdx = 0, lowIdx = 0;
    double total = 0.0, salary, high, low;
    char highName[50], lowName[50];

    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (count <= 0) {
        printf("No employees have been registered yet.\n");
        return;
    }

    high = low = grossSalary(&emp[0]);

    for (i = 0; i < count; i++) {
        salary = grossSalary(&emp[i]);
        total += salary;
        if (salary > high) { high = salary; highIdx = i; }
        if (salary < low)  { low  = salary; lowIdx  = i; }
    }

    strcpy(highName, emp[highIdx].name);
    strcpy(lowName,  emp[lowIdx].name);

    printf("Total Employees: %d\n", count);
    printf("Average Salary : N$%.2f\n", total / count);
    printf("Highest Salary : N$%.2f (%s)\n", high, highName);
    printf("Lowest Salary  : N$%.2f (%s)\n", low, lowName);

    printf("\n%-6s %-22s %-15s %12s\n", "ID", "Name", "Department", "Gross (N$)");
    printLine('-', 64);
    for (i = 0; i < count; i++) {
        printf("%-6d %-22s %-15s %12.2f\n", emp[i].id, emp[i].name,
               emp[i].department, grossSalary(&emp[i]));
    }
}

/* ---------- Budget Report ---------- */

void budgetReport(const Budget bud[], int count)
{
    int i, exceeded = 0;
    double totalAllocated = 0.0, totalSpent = 0.0, remaining;

    printf("\n========== BUDGET REPORT ==========\n");

    if (count <= 0) {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    printf("%-18s %14s %14s %14s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printLine('-', 64);

    for (i = 0; i < count; i++) {
        remaining = bud[i].allocated - bud[i].expenditure;
        totalAllocated += bud[i].allocated;
        totalSpent += bud[i].expenditure;

        printf("%-18s %14.2f %14.2f %14.2f  %s\n",
               bud[i].department, bud[i].allocated, bud[i].expenditure,
               remaining, (remaining < 0) ? "OVER BUDGET" : "WITHIN BUDGET");

        if (remaining < 0)
            exceeded++;
    }

    printLine('-', 64);
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Total Remaining Budget : N$%.2f\n", totalAllocated - totalSpent);

    if (exceeded == 0) {
        printf("Departments exceeding budget: None\n");
    } else {
        printf("Departments exceeding budget (%d):\n", exceeded);
        for (i = 0; i < count; i++) {
            if (bud[i].expenditure > bud[i].allocated)
                printf("  - %s (over by N$%.2f)\n", bud[i].department,
                       bud[i].expenditure - bud[i].allocated);
        }
    }
}

/* ---------- Supplier Report ---------- */

void supplierReport(const Supplier sup[], int count)
{
    int i;

    printf("\n========== SUPPLIER REPORT ==========\n");

    if (count <= 0) {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("%-6s %-20s %-24s %-14s %-12s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 64);
    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %-24s %-14s %-12s\n", sup[i].id, sup[i].name,
               sup[i].email, sup[i].phone, sup[i].town);
    }
    printf("\nTotal Suppliers: %d\n", count);
}

/* ---------- Asset Report ---------- */

void assetReport(const Asset ast[], int count)
{
    int i, poorCount = 0;
    double totalValue = 0.0;

    printf("\n========== ASSET REPORT ==========\n");

    if (count <= 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("%-6s %-18s %-12s %12s %-14s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', 64);
    for (i = 0; i < count; i++) {
        printf("%-6d %-18s %-12s %12.2f %-14s %-10s\n", ast[i].id, ast[i].name,
               ast[i].type, ast[i].purchaseValue, ast[i].department,
               ast[i].condition);

        totalValue += ast[i].purchaseValue;
        if (strcmp(ast[i].condition, "Poor") == 0)   /* needs attention */
            poorCount++;
    }

    printf("\nTotal Assets      : %d\n", count);
    printf("Total Asset Value : N$%.2f\n", totalValue);
    printf("Assets in Poor condition: %d\n", poorCount);
}

/* ---------- Reports menu ---------- */

void displayReports(const Employee emp[], int empCount,
                    const Budget bud[], int budCount,
                    const Supplier sup[], int supCount,
                    const Asset ast[], int astCount)
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
            case 1: employeeReport(emp, empCount); pauseScreen(); break;
            case 2: budgetReport(bud, budCount);   pauseScreen(); break;
            case 3: supplierReport(sup, supCount); pauseScreen(); break;
            case 4: assetReport(ast, astCount);    pauseScreen(); break;
            default: break;   /* 5 = back; readInt rejects anything else */
        }
    } while (choice != 5);
}
