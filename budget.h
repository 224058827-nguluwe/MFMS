#ifndef BUDGET_H
#define BUDGET_H
#include "common.h"

#define MAX_DEPTS 20

extern int    deptCount;
extern char   deptName[MAX_DEPTS][TEXT_LEN];
extern double deptAllocated[MAX_DEPTS];
extern double deptSpent[MAX_DEPTS];

void   budgetMenu(void);
void   addDepartmentBudget(void);
void   recordExpenditure(void);
void   displayBudgets(void);
void   displayOverBudget(void);
int    findDepartment(const char *name);
double calculateRemaining(double allocated, double spent);
int    isWithinBudget(double allocated, double spent);
#endif
