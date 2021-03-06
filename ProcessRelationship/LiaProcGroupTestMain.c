/******************************************************************************

版权所有 (C), 刘剑个人文件

******************************************************************************
文 件 名 : LiaProcGroupTestMain.c
版 本 号 : 初稿
作 者 : liujian
生成日期 : 2015/10/06
最近修改 :
功能描述 :主要是用于对于进程组的概念和使用方法的研究
函数列表 :
修改历史 :
1.日 期 : 2015/10/06
作 者 : liujian
修改内容 : 创建文件

******************************************************************************/

/*----------------------------------------------*
* 包含头文件 *
*----------------------------------------------*/
#include "LiaProcGroupTestMain.h"
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


int main(int argc, char **argv)
{
	int pid_B = -1;
	int pid_A = -1;

	pid_A = fork();
	printf("Proc main pgid:%d\n", getpgid(getpid()));//当前pgid
	if (pid_A<0)
	{
		perror("fork A error!\n");
		return -1;
	}
	else if (0==pid_A)//fork A进程
	{
		printf("Proc A pgid:%d\n", getpgid(getpid()));//当前pgid
		if (execl("./LiaProcGroupTestProcA.out", "./LiaProcGroupTestProcA.out", (char *)0)<0)
		{
			perror("execl A error!");
		}
		exit(0);
	}
	pid_B = fork();
	if (pid_B < 0)
	{
		perror("fork A error!\n");
		return -1;
	}
	else if (0 == pid_B)//fork B进程
	{
		printf("Proc B pgid:%d,pid:%d\n", getpgid(getpid()), getpid());//当前pgid
		if (execl("./LiaProcGroupTestProcB.out", "./LiaProcGroupTestProcB.out", (char *)0) < 0)
		{
			perror("execl B error!");
		}
		exit(0);
	}
	sleep(1);
	kill(0, SIGUSR1);//给A进程发信号
	//kill(pid_B, SIGUSR1);//给B进程发信号
	sleep(2);
	while (1);

	return 0;
}

