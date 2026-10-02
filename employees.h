#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include "common.h"

#define MAX_EMPLOYEES 100

extern int    empCount;
extern char   empId[MAX_EMPLOYEES][ID_LEN];
extern char   empName[MAX_EMPLOYEES][NAME_LEN];
extern char   empDept[MAX_EMPLOYEES][TEXT_LEN];
extern char   empTitle[MAX_EMPLOYEES][TEXT_LEN];
extern double empBasic[MAX_EMPLOYEES];
extern double empHousing[MAX_EMPLOYEES];
extern double empTransport[MAX_EMPLOYEES];
extern int    empYears[MAX_EMPLOYEES];

void   employeeMenu(void);
void   addEmployee(void);
void   displayEmployees(void);
void   searchEmployee(void);
void   salarySlip(void);
int    findEmployeeById(const char *id);
double calculateGross(double basic, double housing, double transport);
double calculateTax(double gross);
double calculatePension(double basic);
double calculateNet(double gross, double tax, double pension);
#endif
