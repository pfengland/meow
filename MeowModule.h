#ifndef H_MEOWMODULE
#define H_MEOWMODULE

typedef struct MeowModule_s MeowModule;
typedef struct MeowModule_ops_s MeowModule_ops;
struct MeowModule_s {
     const MeowModule_ops *ops;
     void *impl;
};

struct MeowModule_ops_s {
     void (*free)(MeowModule *m);
     void (*start)(MeowModule *m);
};

MeowModule* MeowModule_create(void);
void MeowModule_free(MeowModule *m);

#endif
