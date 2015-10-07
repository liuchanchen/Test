#ifndef LiaProcessRelationApi_h__
#define LiaProcessRelationApi_h__

#include "../LiaCommon.h"

#define CFGMNG_TASK_NAME_LEN 256

int cfgmng_get_taskname(int pid, char *ac, int len);
int MonitorParentProcessDead();

#endif // LiaProcessRelationApi_h__

