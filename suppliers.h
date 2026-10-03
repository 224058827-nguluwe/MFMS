#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "common.h"

#define MAX_SUPPLIERS 100
#define EMAIL_LEN 80
#define PHONE_LEN 20

extern int supplierCount;
extern char supplierId[MAX_SUPPLIERS][ID_LEN];
extern char supplierName[MAX_SUPPLIERS][NAME_LEN];
extern char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
extern char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
extern char supplierTown[MAX_SUPPLIERS][TEXT_LEN];

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
int findSupplierById(const char *id);

#endif
