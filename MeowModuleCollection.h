#ifndef H_MEOWMODULECOLLECTION
#define H_MEOWMODULECOLLECTION

#include "DynamicArray.h"
#include "MeowModule.h"

typedef struct MeowModuleCollection_s MeowModuleCollection;
struct MeowModuleCollection_s {
     DynamicArray *modules;
};

MeowModuleCollection* MeowModuleCollection_create(void);
void MeowModuleCollection_free(MeowModuleCollection *c);
MeowModule* MeowModuleCollection_get(MeowModuleCollection *c, int i);
int MeowModuleCollection_count(MeowModuleCollection *c);
void MeowModuleCollection_add(MeowModuleCollection *c, MeowModule *m);
void MeowModuleCollection_remove(MeowModuleCollection *c, MeowModule *m);
void MeowModuleCollection_removeAt(MeowModuleCollection *c, int i);
void MeowModuleCollection_empty(MeowModuleCollection *c);
void MeowModuleCollection_cleanup(MeowModuleCollection *c);
void MeowModuleCollection_startAll(MeowModuleCollection *c);
     
#endif
