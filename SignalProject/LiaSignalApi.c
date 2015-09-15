/******************************************************************************

��Ȩ���� (C), ���������ļ�

******************************************************************************
�� �� �� : LiaSignalApi.c
�� �� �� : ����
�� �� : liujian
�������� : 2015��9��10��
����޸� :
�������� :
�����б� :
�޸���ʷ :
1.�� �� : 2015/09/10
�� �� : liujian
�޸����� : �����ļ�

******************************************************************************/

/*----------------------------------------------*
* ����ͷ�ļ� *
*----------------------------------------------*/
#include "LiaSignalApi.h"
/*----------------------------------------------*
* �ⲿ����˵�� *
*----------------------------------------------*/

/*----------------------------------------------*
* �ⲿ����ԭ��˵�� *
*----------------------------------------------*/

/*----------------------------------------------*
* �ڲ�����ԭ��˵�� *
*----------------------------------------------*/
static void LIA_SignalHandler(Int32 i32Singno);
static void LIA_SignalHandlerType(Int32 i32Singno, siginfo_t*, void *flag);

/*----------------------------------------------*
* ȫ�ֱ��� *
*----------------------------------------------*/

/*----------------------------------------------*
* ģ�鼶���� *
*----------------------------------------------*/

/*----------------------------------------------*
* �������� *
*----------------------------------------------*/

/*----------------------------------------------*
* �궨�� *
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
	Lia_SignalIsBlock(signo);//�ж��ź��Ƿ�����
	Lia_SetSignalBlock(signo);
	//sigprocmask(SIG_BLOCK, &stNewSet, NULL);//�������ź�
	sigprocmask(SIG_BLOCK, NULL, &stOldSet);//��ȡ��ǰ�ź��������
	Lia_RecieveSignalProcess(signo, LIA_SignalHandlerType);//�����ź�
	Lia_SuspendProcUntilCatchSingnal(signo);//�ڲ����ź�֮ǰ�������߳�
	Lia_SignalIsBlock(signo);//�ж��ź��Ƿ�����
	Lia_SignalIsPending(signo);//�ж��ź��Ƿ��ڴ���״̬
	sigprocmask(SIG_SETMASK, &stOldSet, NULL);//���������ź�
	Lia_SignalIsBlock(signo);//�ж��ź��Ƿ�����
	Lia_SignalIsPending(signo);//�ж��ź��Ƿ��ڴ���״̬

	return 0;
}

/*****************************************************************************
�� �� �� : ITS_SignalHandler
�������� : �źŴ�����
������� : i32Singno Ҫ������ź�ֵ
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :
b
�޸���ʷ :
1.�� �� : 2015/09/10
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
static void LIA_SignalHandler(Int32 i32Singno)
{
	printf("Catch the signal!\n");

	return;
}

/*****************************************************************************
�� �� �� : ITS_SignalHandler
�������� : �źŴ�����
������� : i32Singno Ҫ������ź�ֵ
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/10
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
static void LIA_SignalHandlerType(Int32 i32Singno, siginfo_t* stSigInfo, void *flag)
{
	//printf("Catch the signal:%d!\n", stSigInfo);

	return;
}

/*****************************************************************************
�� �� �� : Lia_SignalIsBlock
�������� : �ж��ź��Ƿ�����
������� : i32Signo
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/10
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
Int32 Lia_SignalIsBlock(Int32 i32Signo)
{
	struct sigaction signal_act;

	sigprocmask(0, NULL, &signal_act.sa_mask);//��ȡ��ǰ���ź�����״̬
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
�� �� �� : Lia_SignalIsPending
�������� : �ж��ź��Ƿ��ڴ���״̬
������� : i32Signo ��ʾҪ�жϵ��ź�
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/11
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
Int32 Lia_SignalIsPending(Int32 i32Signo)
{
	//struct sigaction signal_act;
	sigset_t SignalSet;

	if (sigpending(&SignalSet) < 0)//��ȡ��ǰ���ź�����״̬
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
�� �� �� : Lia_RecieveSignalProcess
�������� :������յ����ź�
������� : i32Signo ��ʾ��Ҫ������ź�
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/11
�� �� : liujian
�޸����� : �����ɺ���

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
�� �� �� : Lia_SetSignalBlock
�������� :
������� : i32Signo Ҫ�������ź�
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/11
�� �� : liujian
�޸����� : �����ɺ���

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
�� �� �� : Lia_SetSignalUnBlock
�������� : ���ĳ�źŵ��������߽��ź�����״̬�ָ���֮ǰ��״̬
������� : i32Signo ��ʾҪ���ε��ź�
������� : stOldSigSet ��ʾҪ�ָ���֮ǰ���źż�
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/11
�� �� : liujian
�޸����� : �����ɺ���

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
�� �� �� : Lia_SuspendProcUntilCatchSingnal
�������� : �������ض��ź�ͬʱ�����߳�
������� : i32Signo ��ʾҪ���������ź�
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/14
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
Int32 Lia_SuspendProcUntilCatchSingnal(Int32 i32Signo)
{
	sigset_t CurSigSet;//��ǰ�źż�

	sigprocmask(0, NULL, &CurSigSet);//��ȡ��ǰ�ź�����״̬
	sigdelset(&CurSigSet, i32Signo);//�ӽ��źŴӵ�ǰ��������ȥ��
	sigsuspend(&CurSigSet);

	return 0;
}

/*****************************************************************************
�� �� �� : Lia_SendSigWithPara
�������� : ���ʹ��в������ź�
������� : pid Ҫ�����źŵĽ���id
������� : i32Signo Ҫ���͵��ź�
������� : SendData Ҫ���͵�����
������� : ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/09/15
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
Int32 Lia_SendSigWithPara(pid_t pid, Int32 i32Signo, void *SendData)
{
	union sigval val;

	val.sival_ptr = SendData;
	sigqueue(pid, i32Signo, val);

	return 0;
}


