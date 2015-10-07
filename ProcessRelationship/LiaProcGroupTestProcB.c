/******************************************************************************

版权所有 (C), 刘剑个人文件

******************************************************************************
文 件 名 : LiaProcGroupTestProcB.c
版 本 号 : 初稿
作 者 : liujian
生成日期 : 2015/10/06
最近修改 :
功能描述 :
函数列表 :
修改历史 :
1.日 期 : 2015/10/06
作 者 : liujian
修改内容 : 创建文件

******************************************************************************/

/*----------------------------------------------*
* 包含头文件 *
*----------------------------------------------*/
#include "LiaProcGroupTestProcB.h"
/*----------------------------------------------*
* 外部变量说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 外部函数原型说明 *
*----------------------------------------------*/

/*----------------------------------------------*
* 内部函数原型说明 *
*----------------------------------------------*/
static void LiaSigHandleFunc(int i32SigNo, siginfo_t *SigInfo, void *Flag);

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


int main(int arc, char ** argv)
{
	printf("Exec B pgid:%d,pid:%d\n", getpgid(getpid()),getpid());//当前pgid
	Lia_RecieveSignalProcess(SIGUSR1, LiaSigHandleFunc);
	while (1);

	return 0;
}

static void LiaSigHandleFunc(int i32SigNo, siginfo_t *SigInfo, void *Flag)
{
	printf("Catch the signal:%d\n", SigInfo->si_pid);

	return;
}