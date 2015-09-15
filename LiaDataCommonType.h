#ifndef LIA_DATA_COMMON_TYPE_H
#define LIA_DATA_COMMON_TYPE_H

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <unistd.h>
#include <mqueue.h>
#include <sys/msg.h>
#include <signal.h>



typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;

typedef  char Int8;
typedef  short Int16;
typedef  int Int32;
typedef  long long Int64;


#endif