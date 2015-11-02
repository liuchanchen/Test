#include "TestPthreadCond.h"

pthread_cond_t PthreadCond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t PthreadMutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char ** argv)
{
	pthread_t PthreadId1, PthreadId2;
	pthread_create(&PthreadId1, NULL, TestPthreadSever, NULL);
	pthread_create(&PthreadId2, NULL, TestPthreadClient, NULL);
	while (1);

	return 0;
}

void *TestPthreadSever(void * argv)
{
	printf("entry TestPthreadSever!\n");
	sleep(10);
	pthread_cond_signal(&PthreadCond);
	while (1);

	return (void *)0;
}

void *TestPthreadClient(void * argv)
{
	printf("entry TestPthreadClient!\n");
	while (1)
	{
		pthread_cond_wait(&PthreadCond, &PthreadMutex);
		printf("wait up!\n");
	}
	return (void *)0;
}