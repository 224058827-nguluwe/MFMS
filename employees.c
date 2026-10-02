#include <stdio.h>
#include <string.h>
#include "employees.h"

int    empCount = 0;
char   empId[MAX_EMPLOYEES][ID_LEN];
char   empName[MAX_EMPLOYEES][NAME_LEN];
char   empDept[MAX_EMPLOYEES][TEXT_LEN];
char   empTitle[MAX_EMPLOYEES][TEXT_LEN];
double empBasic[MAX_EMPLOYEES];
double empHousing[MAX_EMPLOYEES];
double empTransport[MAX_EMPLOYEES];
int    empYears[MAX_EMPLOYEES];

int findEmployeeById(const char *id)
{
    int i;
    for (i = 0; i < empCount; i++)
        if (strcmp(empId[i], id) == 0) return i;
    return -1;
}

double calculateGross(double basic, double housing, double transport)
{
    return basic + housing + transport;
}

/* Simplified monthly tax bands (teaching model, not official PAYE). */
double calculateTax(double gross)
{
    if (gross <= 5000.0)       return 0.0;
    else if (gross <= 10000.0) return (gross - 5000.0) * 0.10;
    else if (gross <= 20000.0) return 500.0 + (gross - 10000.0) * 0.20;
    else                       return 2500.0 + (gross - 20000.0) * 0.30;
}

/* Employee pension contribution: 7% of basic salary. */
double calculatePension(double basic)
{
    return basic * 0.07;
}

double calculateNet(double gross, double tax, double pension)
{
    return gross - tax - pension;
}

void addEmployee(void)
{
    if (empCount >= MAX_EMPLOYEES) {
        printf("  [!] Employee list is full (%d).\n", MAX_EMPLOYEES);
        return;
    }
    char id[ID_LEN];
    printf("\n--- Add Employee ---\n");
    for (;;) {
        readNonEmpty("Employee ID: ", id, sizeof id);
        if (findEmployeeById(id) != -1) printf("  [!] ID '%s' already exists.\n", id);
        else break;
    }
    int n = empCount;
    strcpy(empId[n], id);
    readNonEmpty("Full name: ", empName[n], NAME_LEN);
    readNonEmpty("Department: ", empDept[n], TEXT_LEN);
    readNonEmpty("Job title: ", empTitle[n], TEXT_LEN);
    empBasic[n]     = readMoney("Basic salary (N$/month): ");
    while (empBasic[n] <= 0) {
        printf("  [!] Basic salary must be greater than zero.\n");
        empBasic[n] = readMoney("Basic salary (N$/month): ");
    }
    empHousing[n]   = readMoney("Housing allowance (N$): ");
    empTransport[n] = readMoney("Transport allowance (N$): ");
    empYears[n]     = readInt("Years of service (0-50): ", 0, 50);
    empCount++;
    printf("  Employee '%s' added successfully.\n", empName[n]);
}

void displayEmployees(void)
{
    int i;
    printf("\n--- Employee List (%d) ---\n", empCount);
    if (empCount == 0) { printf("  No employees registered.\n"); return; }
    printf("%-10s %-22s %-16s %-16s %12s\n", "ID", "Name", "Department", "Title", "Basic (N$)");
    printLine('-', 80);
    for (i = 0; i < empCount; i++)
        printf("%-10s %-22s %-16s %-16s %12.2f\n",
               empId[i], empName[i], empDept[i], empTitle[i], empBasic[i]);
}

static void printEmployeeDetail(int i)
{
    double gross = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
    printf("\n  ID:         %s\n  Name:       %s\n  Department: %s\n  Title:      %s\n",
           empId[i], empName[i], empDept[i], empTitle[i]);
    printf("  Basic:      N$%.2f\n  Housing:    N$%.2f\n  Transport:  N$%.2f\n  Gross:      N$%.2f\n  Service:    %d year(s)\n",
           empBasic[i], empHousing[i], empTransport[i], gross, empYears[i]);
}

void searchEmployee(void)
{
    char key[NAME_LEN];
    int i, found = 0;
    printf("\n--- Search Employee ---\n");
    readNonEmpty("Enter ID, name or department: ", key, sizeof key);
    for (i = 0; i < empCount; i++) {
        if (strcmp(empId[i], key) == 0 || containsIgnoreCase(empName[i], key) ||
            containsIgnoreCase(empDept[i], key)) {
            printEmployeeDetail(i);
            found++;
        }
    }
    if (!found) printf("  No employee matches '%s'.\n", key);
    else        printf("\n  %d record(s) found.\n", found);
}

void salarySlip(void)
{
    char id[ID_LEN];
    printf("\n--- Salary Calculation ---\n");
    readNonEmpty("Employee ID: ", id, sizeof id);
    int i = findEmployeeById(id);
    if (i == -1) { printf("  [!] Employee not found.\n"); return; }

    double gross   = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
    double tax     = calculateTax(gross);
    double pension = calculatePension(empBasic[i]);
    double net     = calculateNet(gross, tax, pension);

    printf("\n  SALARY SLIP: %s (%s)\n", empName[i], empId[i]);
    printLine('-', 40);
    printf("  Basic salary      N$%10.2f\n", empBasic[i]);
    printf("  Housing allowance N$%10.2f\n", empHousing[i]);
    printf("  Transport allow.  N$%10.2f\n", empTransport[i]);
    printf("  Gross salary      N$%10.2f\n", gross);
    printf("  Tax (est.)       -N$%10.2f\n", tax);
    printf("  Pension (7%%)     -N$%10.2f\n", pension);
    printLine('-', 40);
    printf("  NET SALARY        N$%10.2f\n", net);
}

void employeeMenu(void)
{
    int c;
    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add employee\n2. Display employees\n3. Search employee\n");
        printf("4. Calculate salary\n5. Back to main menu\n");
        c = readInt("Enter your choice: ", 1, 5);
        switch (c) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: salarySlip(); break;
            default: break;
        }
    } while (c != 5);
}
