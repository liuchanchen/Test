#ifndef LiaFifoApi_h__
#define LiaFifoApi_h__

#include "../../../LiaCommon.h"

#define FIFO_FROM_SEVER_TO_CLIENT "/home/liujian/Desktop/Test/FIFO/FIFO/src/FifoSeverToClient"
#define FIFO_FROM_CLIENT_TO_SEVER "/home/liujian/Desktop/Test/FIFO/FIFO/src/FifoClientToSever"
#define FIFO_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

Int32 Lia_Fifo_Init(const Int8 * pi8PathSeverToClient, Int8 * pi8PathClientToSever, Int32 mode);
Int32 Lia_Fifo_UnInit(const Int8 * pi8Path);
Int32 Lia_Fifo_Read(Int8 *pi8Path, void * pBuf, Int32 i32MaxReadLen);
Int32 Lia_Fifo_Write(Int8 * pi8Path, const void * pBuf, Int32 i32WriteLen);

#endif // LiaFifoApi_h__


