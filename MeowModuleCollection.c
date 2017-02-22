#include "MeowModuleCollection.h"
#include <stdlib.h>
#include <stdio.h>

MeowModuleCollection* MeowModuleCollection_create(void) {
     int i;
     MeowModuleCollection *c = malloc(sizeof(*c));
     c->modules = DynamicArray_create();
     c->modules->items = malloc(sizeof(MeowModule*) * c->modules->size);
     for (i=0; i<c->modules->size; i++) {
	  ((MeowModule**)c->modules->items)[i] = NULL;
     }
     return c;
}

void MeowModuleCollection_startAll(MeowModuleCollection *c) {
     int i;
     for (i=0; i<c->modules->count; i++) {
	  MeowModule *m = ((MeowModule**)c->modules->items)[i];
	  m->ops->start(m);
     }
}

void MeowModuleCollection_free(MeowModuleCollection *c) {
     // free the modules
     while (MeowModuleCollection_count(c)) {
	  //	  printf("removing module\n");
	  MeowModuleCollection_removeAt(c, 0);
     }
     DynamicArray_free(c->modules);
}

MeowModule* MeowModuleCollection_get(MeowModuleCollection *c, int i) {
     if (i<0 || i >= c->modules->count) return NULL;
     return ((MeowModule**)c->modules->items)[i];
}

int MeowModuleCollection_count(MeowModuleCollection *c) {
     return c->modules->count;
}

void MeowModuleCollection_add(MeowModuleCollection *c, MeowModule *m) {
     int newCount = c->modules->count + 1;
     int i;
     if (c->modules->size < newCount) {
	  int newSize = c->modules->size * 2;
	  c->modules->items = realloc(c->modules->items, sizeof(*m) * newSize);
	  for (i=c->modules->size; i<newSize; i++) {
	       ((MeowModule**)c->modules->items)[i] = NULL;
	  }
	  c->modules->size = newSize;
     }
     ((MeowModule**)c->modules->items)[c->modules->count] = m;
     c->modules->count = newCount;
}

void MeowModuleCollection_remove(MeowModuleCollection *c, MeowModule *m) {
     int i;
     for (i=0; i<c->modules->count; i++) {
	  if (((MeowModule**)c->modules)[i] == m) {
	       MeowModule *m = ((MeowModule**)c->modules->items)[i];
	       m->ops->free(m);
	       ((MeowModule**)c->modules)[i] = NULL;
	       MeowModuleCollection_cleanup(c);
	       return;
	  }
     }
}

void MeowModuleCollection_removeAt(MeowModuleCollection *c, int i) {
     if (i >= c->modules->count || i < 0) return;
     MeowModule *m = ((MeowModule**)c->modules->items)[i];
     m->ops->free(m);
     ((MeowModule**)c->modules->items)[i] = NULL;
     MeowModuleCollection_cleanup(c);
}

void MeowModuleCollection_empty(MeowModuleCollection *c) {
     int i;
     for (i=0; i<c->modules->count; i++) {
	  MeowModule_free(((MeowModule**)c->modules->items)[i]);
	  ((MeowModule**)c->modules->items)[i] = NULL;
     }
     MeowModuleCollection_cleanup(c);
}

void MeowModuleCollection_cleanup(MeowModuleCollection *c) {
     int newCount = 0, i, j;
     for (i=0; i<c->modules->count; i++) {
	  if (((MeowModule**)c->modules->items)[i] != NULL)
	       newCount++;
     }
     if (newCount == c->modules->count) return;
     MeowModule **newItems = malloc(sizeof(MeowModule*) * newCount);
     for (i=0, j=0; i<c->modules->count; i++) {
	  if (((MeowModule**)c->modules->items)[i] != NULL)
	       newItems[j++] = ((MeowModule**)c->modules->items)[i];
     }
     c->modules->items = newItems;
     c->modules->count = newCount;
}
