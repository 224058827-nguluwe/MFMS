#ifndef ASSETS_H
#define ASSETS_H
#include "common.h"

#define MAX_ASSETS 200

extern int    assetCount;
extern char   assetId[MAX_ASSETS][ID_LEN];
extern char   assetName[MAX_ASSETS][NAME_LEN];
extern char   assetType[MAX_ASSETS][TEXT_LEN];
extern double assetValue[MAX_ASSETS];
extern char   assetDept[MAX_ASSETS][TEXT_LEN];
extern char   assetCondition[MAX_ASSETS][TEXT_LEN];

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int  findAssetById(const char *id);
#endif
