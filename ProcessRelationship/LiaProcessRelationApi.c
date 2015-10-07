#include "LiaProcessRelationApi.h"


/*****************************************************************************
�� �� �� : cfgmng_get_taskname
�������� : ����pid���ҽ�����
������� : pidҪ���ҵĽ���id 
������� : len��ʾ�������ֽ���
������� : ac��ʾ�õ��Ľ��
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/10/01
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
int cfgmng_get_taskname(int pid,char *ac, int len)
{
	int count = 0;
	int nIndex = 0;
	char chPath[CFGMNG_TASK_NAME_LEN] = { 0 };
	char cParam[100] = { 0 };
	char *cTem = chPath;
	int tmp_len;
	pid_t pId = - 1;

	pId = pid;
	sprintf(cParam, "/proc/%d/exe", pId);
	/*    printf("cParam = %s.\n", cParam);*/
	count = readlink(cParam, chPath, CFGMNG_TASK_NAME_LEN);
	printf("chPath:%s\n", chPath);
	/*    printf("count = %d.\n", count);*/
	if (count < 0 || count >= CFGMNG_TASK_NAME_LEN)
	{
		printf("Current System Not Surport Proc.\n");

		return -1;
	}
	else
	{
		nIndex = count - 1;
		for (; nIndex >= 0; nIndex--)
		{
			if (chPath[nIndex] == '/')//ɸѡ��������
			{
				nIndex++;
				cTem += nIndex;
				break;
			}
		}
	}
	tmp_len = strlen(cTem);
	if (0 == tmp_len) 
	{
		printf("Get task fail.\n");

		return -1;
	}
	if (len <= tmp_len + 1) 
	{
		printf("len(%d) is less than taskname(%s)'s len.\n", len, cTem);

		return -1;
	}
	strcpy(ac, cTem);

	return 0;
}

/*****************************************************************************
�� �� �� : MonitorParentProcessDead
�������� : ��ظ������Ƿ�ҵ�
������� : 
�� �� ֵ : 0��ʾ�ɹ�
������ʾʧ��
���ú��� :
�������� :

�޸���ʷ :
1.�� �� : 2015/10/01
�� �� : liujian
�޸����� : �����ɺ���

*****************************************************************************/
int MonitorParentProcessDead()
{
	int pid = -1;//����pid
	int ppid = -1;//������pid
	char i8ProcName[CFGMNG_TASK_NAME_LEN];

	memset(i8ProcName, 0x0, sizeof(i8ProcName));
	pid = fork();
	if (pid<0)
	{
		perror("fork error");
	}
	else if (0==pid)
	{
		printf("I am child\n");
		while (1)
		{
			ppid = getppid();
			printf("parent id:%d\n",ppid);
			cfgmng_get_taskname(ppid, i8ProcName, CFGMNG_TASK_NAME_LEN);
			printf("Parent Process died!:%s\n", i8ProcName);
			if (1== ppid)//��������̱��init������������̹���
			{
				printf("Parent Process died!\n");
				sleep(10);
				exit(0);
			}
			sleep(1);
		}
	}
	printf("child id:%d\n",pid);
	//waitpid(pid, NULL, 0);
	//printf("Montior Process dead\n");

	return 0;
}
 