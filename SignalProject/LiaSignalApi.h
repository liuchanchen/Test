#ifndef LiaSignalApi_h__
#define LiaSignalApi_h__

#include "../LiaCommon.h"

typedef void(*SigHandleFunc)(int, siginfo_t *,void *);

Int32 Lia_SignalWholeProcess();
Int32 Lia_SignalProcessMain(int signo);
Int32 Lia_SignalIsBlock(Int32 i32Signo);
Int32 Lia_SignalIsPending(Int32 i32Signo);
Int32 Lia_RecieveSignalProcess(Int32 i32Signo, SigHandleFunc LIA_SignalHandlerType);
Int32 Lia_SetSignalBlock(Int32 i32Signo);
Int32 Lia_SetSignalUnBlock(Int32 i32Signo, sigset_t *pstOldSigSet);
Int32 Lia_SuspendProcUntilCatchSingnal(Int32 i32Signo);
Int32 Lia_SendSigWithPara(pid_t pid, Int32 i32Signo, void *SendData);
#endif // LiaSignalApi_h__

