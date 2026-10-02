#include <stdio.h>
#include <string.h>
#include "assets.h"

int    assetCount = 0;
char   assetId[MAX_ASSETS][ID_LEN];
char   assetName[MAX_ASSETS][NAME_LEN];
char   assetType[MAX_ASSETS][TEXT_LEN];
double assetValue[MAX_ASSETS];
char   assetDept[MAX_ASSETS][TEXT_LEN];
char   assetCondition[MAX_ASSETS][TEXT_LEN];

static const char *TYPES[] = { "Vehicle", "Computer", "Building", "Equipment", "Furniture" };
static const char *CONDITIONS[] = { "Good", "Fair", "Poor" };

int findAssetById(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++)
        if (strcmp(assetId[i], id) == 0) return i;
    return -1;
}

void addAsset(void)
{
    if (assetCount >= MAX_ASSETS) { printf("  [!] Asset register full.\n"); return; }
    char id[ID_LEN];
    int i, n = assetCount;
    printf("\n--- Add Asset ---\n");
    for (;;) {
        readNonEmpty("Asset ID: ", id, sizeof id);
        if (findAssetById(id) != -1) printf("  [!] ID already exists.\n");
        else break;
    }
    strcpy(assetId[n], id);
    readNonEmpty("Asset name: ", assetName[n], NAME_LEN);

    printf("Asset type:\n");
    for (i = 0; i < 5; i++) printf("  %d. %s\n", i + 1, TYPES[i]);
    strcpy(assetType[n], TYPES[readInt("Choose type (1-5): ", 1, 5) - 1]);

    assetValue[n] = readMoney("Purchase value (N$): ");
    readNonEmpty("Department: ", assetDept[n], TEXT_LEN);

    printf("Condition:\n");
    for (i = 0; i < 3; i++) printf("  %d. %s\n", i + 1, CONDITIONS[i]);
    strcpy(assetCondition[n], CONDITIONS[readInt("Choose condition (1-3): ", 1, 3) - 1]);

    assetCount++;
    printf("  Asset '%s' registered.\n", assetName[n]);
}

void displayAssets(void)
{
    int i;
    printf("\n--- Asset Register (%d) ---\n", assetCount);
    if (assetCount == 0) { printf("  No assets registered.\n"); return; }
    printf("%-8s %-20s %-10s %12s %-14s %-6s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Cond.");
    printLine('-', 76);
    for (i = 0; i < assetCount; i++)
        printf("%-8s %-20s %-10s %12.2f %-14s %-6s\n",
               assetId[i], assetName[i], assetType[i], assetValue[i], assetDept[i], assetCondition[i]);
}

void searchAsset(void)
{
    char key[NAME_LEN];
    int i, found = 0;
    printf("\n--- Search Asset ---\n");
    readNonEmpty("Enter ID, name, type or department: ", key, sizeof key);
    for (i = 0; i < assetCount; i++) {
        if (strcmp(assetId[i], key) == 0 || containsIgnoreCase(assetName[i], key) ||
            containsIgnoreCase(assetType[i], key) || containsIgnoreCase(assetDept[i], key)) {
            printf("  %-8s %-20s %-10s N$%.2f  %-14s %s\n",
                   assetId[i], assetName[i], assetType[i], assetValue[i],
                   assetDept[i], assetCondition[i]);
            found++;
        }
    }
    if (!found) printf("  No asset matches '%s'.\n", key);
}

void assetMenu(void)
{
    int c;
    do {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Add asset\n2. Display assets\n3. Search asset\n4. Back to main menu\n");
        c = readInt("Enter your choice: ", 1, 4);
        switch (c) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            default: break;
        }
    } while (c != 4);
}
