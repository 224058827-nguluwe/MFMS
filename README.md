# MFMS – Municipal Financial Management System

**Course:** PAP521S – Programming in Practice (Project A: Foundation System)
**Group number:** [FILL IN]

## Group members
| # | Name | Student number | Responsibility |
|---|------|----------------|----------------|
| 1 | Wapingena E. Muukua | 223080071 | Employee Management (`employees.c/.h`) |
| 2 | Matheus SL | 224017578 | Budget Management (`budget.c/.h`) |
| 3 | John Mitchell | 223116173 | Supplier Management (`suppliers.c/.h`) |
| 4 | Alfons Beukes | 225068125 | Asset Management (`assets.c/.h`) |
| 5 | Hileni Uukanga | 225012219 | Reports (`reports.c/.h`) |
| 6 | Kondjashili Shatimwene | 225080370 | Functions, integration, validation (`common.c/.h`, `main.c`) |
| 7 | Linda Nguluwe | 224058827 | Testing, documentation, Git coordination (`Makefile`, `README.md`) |

## Description
A menu-driven console application written in ANSI C (C99) that helps a municipality manage
employees, departmental budgets, suppliers and assets, and produce summary reports.
Data is held in arrays in memory (it is not saved to disk in Project A).

## Features
- **Employees:** add, list, search (ID/name/department), salary calculation (gross, estimated tax, 7% pension, net)
- **Budgets:** enter department budgets, record expenditure, remaining balance, WITHIN/OVER BUDGET status, list over-budget departments
- **Suppliers:** add (email and phone validated), list, search (ID/name/town), compare two suppliers
- **Assets:** add (type and condition chosen from menus), list, search (ID/name/type/department)
- **Reports:** employee statistics, budget totals, supplier list, asset list with total value
- **Validation:** invalid menu choices, negative/non-numeric amounts, empty fields, duplicate IDs, bad email/phone

## Compilation
```
make
```
or manually:
```
gcc -std=c99 -Wall -Wextra -pedantic main.c common.c employees.c budget.c suppliers.c assets.c reports.c -o mfms -lm
```

## How to run
```
./mfms        (Linux/macOS/Git Bash)
mfms.exe      (Windows)
```

## Individual responsibilities
See the table above and each member's Individual Contribution Record.
