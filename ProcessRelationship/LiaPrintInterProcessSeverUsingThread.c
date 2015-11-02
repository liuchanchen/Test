/******************************************************************************

��Ȩ���� (C), ���������ļ�

******************************************************************************
�� �� �� : LiaPrintInterProcessSeverUsingThread.c
�� �� �� : ����
�� �� : liujian
�������� : 2015/10/13
����޸� :
�������� :
�����б� :
�޸���ʷ :
1.�� �� : 2015/10/13
�� �� : liujian
�޸����� : �����ļ�

******************************************************************************/

/*----------------------------------------------*
* ����ͷ�ļ� *
*----------------------------------------------*/
#include "LiaPrintInterProcessSeverUsingThread.h"
/*----------------------------------------------*
* �ⲿ����˵�� *
*----------------------------------------------*/

/*----------------------------------------------*
* �ⲿ����ԭ��˵�� *
*----------------------------------------------*/

/*----------------------------------------------*
* �ڲ�����ԭ��˵�� *
*----------------------------------------------*/
static void * LiaPrintThread(void * argv);
static void * LiaPrintThread2(void * argv);

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

int main(int argc, char ** argv)
{
	pthread_t PthreadPrint, PthreadPrint2;

	if (pthread_create(&PthreadPrint,NULL, LiaPrintThread,NULL)<0)
	{
		perror("pthread_create error :");
	}
	pthread_detach(PthreadPrint);
	if (pthread_create(&PthreadPrint2, NULL, LiaPrintThread2, NULL) < 0)
	{
		perror("pthread_create error :");
	}
	pthread_detach(PthreadPrint2);
	while (1);

	return 0;
}

static void * LiaPrintThread(void * argv)
{
	char i8ReadBuf[128];
	int fd = -1;

	memset(i8ReadBuf, 0x0, sizeof(i8ReadBuf));
	printf("entry LiaPrintThread\n");
	while (1)
	{
		Lia_Fifo_Init(FIFO_FROM_CLIENT_TO_SEVER, FIFO_MODE);//��fifo
		Lia_Fifo_Read(FIFO_FROM_CLIENT_TO_SEVER, i8ReadBuf, 32);//���տͻ��˵��ն�
		Lia_Fifo_UnInit(FIFO_FROM_CLIENT_TO_SEVER);//�ر�fifo
		printf("client tty name : %s\n", i8ReadBuf);
		if ((fd =open(i8ReadBuf,O_WRONLY,0))<0)//�򿪿ͻ����ն�
		{
			perror("open tty error!\n");
		}
		dup2(fd,STDOUT_FILENO);//�������̵��ն�����������ض��򵽿ͻ����ն�
		printf("LiaPrintThread\n");
		sleep(2);
	}

	return (void *)0;
}

static void * LiaPrintThread2(void * argv)
{
	while (1)
	{
		printf("LiaPrintThread2\n");
		sleep(2);
	}

	return (void *)0;
}
