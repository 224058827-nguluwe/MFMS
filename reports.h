#ifndef REPORTS_H
#define REPORTS_H

/*
 * reports.h - Reports module for the Municipal Financial Management System
 *
 * The report functions do not own any data. Each one receives the arrays
 * (and how many items they hold) from main(), so the module stays separate
 * from the other members' code.
 *
 * ASSUMED STRUCTS - agree on these names/fields with your teammates, or
 * change the field names in reports.c to match theirs.
 */

#include "employees.h"   /* Employee: id, name, department,
                            basicSalary, housingAllowance, transportAllowance */
#include "budget.h"      /* Budget:   department, allocated, expenditure     */
#include "suppliers.h"   /* Supplier: id, name, email, phone, town           */
#include "assets.h"      /* Asset:    id, name, type, purchaseValue,
                            department, condition                            */

/* Menu that lets the user pick which report to view */
void displayReports(const Employee emp[], int empCount,
                    const Budget bud[], int budCount,
                    const Supplier sup[], int supCount,
                    const Asset ast[], int astCount);

void employeeReport(const Employee emp[], int count);
void budgetReport(const Budget bud[], int count);
void supplierReport(const Supplier sup[], int count);
void assetReport(const Asset ast[], int count);

#endif
