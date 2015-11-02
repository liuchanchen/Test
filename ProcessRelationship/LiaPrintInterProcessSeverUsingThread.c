/******************************************************************************

版权所有 (C), 刘剑个人文件

******************************************************************************
文 件 名 : LiaPrintInterProcessSeverUsingThread.c
版 本 号 : 初稿
作 者 : liujian
生成日期 : 2015/10/13
最近修改 :
功能描述 :
函数列表 :
修改历史 :
1.日 期 : 2015/10/13
作 者 : liujian
修改内容 : 创建文件

******************************************************************************/

/*----------------------------------------------*
* 包含头文件 *
*----------------------------------------------*/
#include "LiaPrintInterProcessSeverUsingThread.h"
/*----------------------------------------------*
* 外部变量说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 外部函数原型说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 内部函数原型说明 *
*----------------------------------------------*/
static void * LiaPrintThread(void * argv);
static void * LiaPrintThread2(void * argv);

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
		Lia_Fifo_Init(FIFO_FROM_CLIENT_TO_SEVER, FIFO_MODE);//打开fifo
		Lia_Fifo_Read(FIFO_FROM_CLIENT_TO_SEVER, i8ReadBuf, 32);//接收客户端的终端
		Lia_Fifo_UnInit(FIFO_FROM_CLIENT_TO_SEVER);//关闭fifo
		printf("client tty name : %s\n", i8ReadBuf);
		if ((fd =open(i8ReadBuf,O_WRONLY,0))<0)//打开客户端终端
		{
			perror("open tty error!\n");
		}
		dup2(fd,STDOUT_FILENO);//将本进程的终端输出描述符重定向到客户端终端
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
