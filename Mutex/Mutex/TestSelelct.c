/******************************************************************************

版权所有 (C), 刘剑个人文件

******************************************************************************
文 件 名 : TestSelelct.c
版 本 号 : 初稿
作 者 : liujian
生成日期 : 2015/10/22
最近修改 :
功能描述 :
函数列表 :
修改历史 :
1.日 期 : 2015/10/22
作 者 : liujian
修改内容 : 创建文件

******************************************************************************/

/*----------------------------------------------*
* 包含头文件 *
*----------------------------------------------*/
#include "TestSelelct.h"
/*----------------------------------------------*
* 外部变量说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 外部函数原型说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 内部函数原型说明 *
*----------------------------------------------*/

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
	pthread_t PthreadRead;

	pthread_create(&PthreadRead, NULL, SelectRead, NULL);
	while (1);

	return 0;
}

void * SelectRead(void * arg)
{
	fd_set fds;
	struct timeval timeout;
	int Ret = -1;

	pthread_detach(pthread_self());
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		if ((Ret=select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout))<=0)
		{
			continue;
		}
		else if (FD_ISSET(STDIN_FILENO, &fds))
		{
			printf("select ok,Ret:%d\n", Ret);
		}
	}

	return (void *)0;
}

void * SelectWrite(void * arg)
{
	return (void *)0;
}

