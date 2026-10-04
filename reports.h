#ifndef REPORTS_H
#define REPORTS_H

/*
 * reports.h - Reports module for the Municipal Financial Management System
 *
 * main.c calls reportsMenu(). The four report functions read the other
 * modules' data directly (empCount/empName/..., assetCount/assetName/...,
 * and the budget and supplier arrays), so they take no parameters.
 */

void reportsMenu(void);       /* menu: choose which report to view */
void employeeReport(void);
void budgetReport(void);
void supplierReport(void);
void assetReport(void);

#endif
