/******************************************************************************

版权所有 (C), 刘剑个人文件

******************************************************************************
文 件 名 : LiaSignalApi.c
版 本 号 : 初稿
作 者 : liujian
生成日期 : 2015年9月10日
最近修改 :
功能描述 :
函数列表 :
修改历史 :
1.日 期 : 2015/09/10
作 者 : liujian
修改内容 : 创建文件

******************************************************************************/

/*----------------------------------------------*
* 包含头文件 *
*----------------------------------------------*/
#include "LiaSignalApi.h"
/*----------------------------------------------*
* 外部变量说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 外部函数原型说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 内部函数原型说明 *
*----------------------------------------------*/
static void LIA_SignalHandler(Int32 i32Singno);
static void LIA_SignalHandlerType(Int32 i32Singno, siginfo_t*, void *flag);

/*----------------------------------------------*
* 全局变量 *
*----------------------------------------------*/

/*----------------------------------------------*
* 模块级变量 *
*----------------------------------------------*/

/*----------------------------------------------*
* 常量定义 *
*----------------------------------------------*/

/*----------------------------------------------*
* 宏定义 *
*----------------------------------------------*/

Int32 Lia_SignalWholeProcess()
{
	sigset_t SigSet;
	Int32 i32SigNo = -1;

	sigemptyset(&SigSet);
	sigaddset(&SigSet, SIGALRM);
	sigaddset(&SigSet, SIGALRM);
	sigprocmask(SIG_BLOCK, &SigSet, NULL);
	alarm(3);
	while (1)
	{
		printf("entry while\n");
		sigwait(&SigSet, &i32SigNo);
		printf("112222\n");
	}

	return 0;
}

Int32 Lia_SignalProcessMain(int signo)
{
	sigset_t stOldSet, stNewSet, st_ZeroSet;

	sigemptyset(&st_ZeroSet);
	Lia_SignalIsBlock(signo);//判断信号是否阻塞
	Lia_SetSignalBlock(signo);
	//sigprocmask(SIG_BLOCK, &stNewSet, NULL);//阻塞该信号
	sigprocmask(SIG_BLOCK, NULL, &stOldSet);//获取当前信号阻塞情况
	Lia_RecieveSignalProcess(signo, LIA_SignalHandlerType);//处理信号
	Lia_SuspendProcUntilCatchSingnal(signo);//在捕获到信号之前，挂起线程
	Lia_SignalIsBlock(signo);//判断信号是否阻塞
	Lia_SignalIsPending(signo);//判断信号是否处于待定状态
	sigprocmask(SIG_SETMASK, &stOldSet, NULL);//解阻塞该信号
	Lia_SignalIsBlock(signo);//判断信号是否阻塞
	Lia_SignalIsPending(signo);//判断信号是否处于待定状态

	return 0;
}

/*****************************************************************************
函 数 名 : ITS_SignalHandler
功能描述 : 信号处理句柄
输入参数 : i32Singno 要处理的信号值
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :
b
修改历史 :
1.日 期 : 2015/09/10
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
static void LIA_SignalHandler(Int32 i32Singno)
{
	printf("Catch the signal!\n");

	return;
}

/*****************************************************************************
函 数 名 : ITS_SignalHandler
功能描述 : 信号处理句柄
输入参数 : i32Singno 要处理的信号值
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/10
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
static void LIA_SignalHandlerType(Int32 i32Singno, siginfo_t* stSigInfo, void *flag)
{
	//printf("Catch the signal:%d!\n", stSigInfo);

	return;
}

/*****************************************************************************
函 数 名 : Lia_SignalIsBlock
功能描述 : 判断信号是否阻塞
输入参数 : i32Signo
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/10
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SignalIsBlock(Int32 i32Signo)
{
	struct sigaction signal_act;

	sigprocmask(0, NULL, &signal_act.sa_mask);//获取当前的信号阻塞状态
	if (1 == sigismember(&signal_act.sa_mask, i32Signo))
	{
		printf("signal is blocked\n");
	}
	else if (0 == sigismember(&signal_act.sa_mask, i32Signo))
	{
		printf("signal is no blocked\n");
	}
	else if (sigismember(&signal_act.sa_mask, i32Signo)<0)
	{
		printf("sigismember error :%s\n", strerror(errno));
	}

	return 0;
}

/*****************************************************************************
函 数 名 : Lia_SignalIsPending
功能描述 : 判断信号是否处于待定状态
输入参数 : i32Signo 表示要判断的信号
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/11
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SignalIsPending(Int32 i32Signo)
{
	//struct sigaction signal_act;
	sigset_t SignalSet;

	if (sigpending(&SignalSet) < 0)//获取当前的信号阻塞状态
	{
		printf("pending error:%s\n", strerror(errno));
		return -1;
	}
	if (1 == sigismember(&SignalSet, i32Signo))
	{
		printf("The signal pending\n");
	}
	else if (0 == sigismember(&SignalSet, i32Signo))
	{
		printf("The signal no pending\n");
	}
	else if (sigismember(&SignalSet, i32Signo) < 0)
	{
		printf("The sigismember error :%s\n", strerror(errno));
	}

	return 0;
}

/*****************************************************************************
函 数 名 : Lia_RecieveSignalProcess
功能描述 :处理接收到的信号
输入参数 : i32Signo 表示所要处理的信号
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/11
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_RecieveSignalProcess(Int32 i32Signo, SigHandleFunc LIA_SignalHandlerType)
{
	struct sigaction signal_act;

	signal_act.sa_flags = SA_SIGINFO;
	sigemptyset(&signal_act.sa_mask);
	//sigaddset(&signal_act.sa_mask, i32Signo);
	signal_act.sa_sigaction = LIA_SignalHandlerType;
	if (sigaction(i32Signo, &signal_act, NULL) < 0)
	{
		printf("sigaction error!\n");
		return -1;
	}

	return 0;
}

/*****************************************************************************
函 数 名 : Lia_SetSignalBlock
功能描述 :
输入参数 : i32Signo 要阻塞的信号
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/11
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SetSignalBlock(Int32 i32Signo)
{
	sigset_t stSigSet;

	sigemptyset(&stSigSet);
	sigaddset(&stSigSet, i32Signo);
	sigprocmask(SIG_BLOCK, &stSigSet, NULL);

	return 0;
}


/*****************************************************************************
函 数 名 : Lia_SetSignalUnBlock
功能描述 : 解除某信号的阻塞或者将信号阻塞状态恢复到之前的状态
输入参数 : i32Signo 表示要屏蔽的信号
输入参数 : stOldSigSet 表示要恢复的之前的信号集
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/11
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SetSignalUnBlock(Int32 i32Signo, sigset_t *pstOldSigSet)
{
	sigset_t stSigSet;

	if (NULL == pstOldSigSet)
	{
		sigemptyset(&stSigSet);
		sigaddset(&stSigSet, i32Signo);
		sigprocmask(SIG_UNBLOCK, &stSigSet, NULL);
	}
	else
	{
		sigprocmask(SIG_SETMASK, pstOldSigSet, NULL);
	}

	return 0;
}

/*****************************************************************************
函 数 名 : Lia_SuspendProcUntilCatchSingnal
功能描述 : 解阻塞特定信号同时挂起线程
输入参数 : i32Signo 表示要解阻塞的信号
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/14
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SuspendProcUntilCatchSingnal(Int32 i32Signo)
{
	sigset_t CurSigSet;//当前信号集

	sigprocmask(0, NULL, &CurSigSet);//获取当前信号阻塞状态
	sigdelset(&CurSigSet, i32Signo);//从将信号从当前阻塞集中去除
	sigsuspend(&CurSigSet);

	return 0;
}

/*****************************************************************************
函 数 名 : Lia_SendSigWithPara
功能描述 : 发送带有参数的信号
输入参数 : pid 要发送信号的进程id
输入参数 : i32Signo 要发送的信号
输入参数 : SendData 要发送的数据
输出参数 : 无
返 回 值 : 0表示成功
负数表示失败
调用函数 :
被调函数 :

修改历史 :
1.日 期 : 2015/09/15
作 者 : liujian
修改内容 : 新生成函数

*****************************************************************************/
Int32 Lia_SendSigWithPara(pid_t pid, Int32 i32Signo, void *SendData)
{
	union sigval val;

	val.sival_ptr = SendData;
	sigqueue(pid, i32Signo, val);

	return 0;
}


