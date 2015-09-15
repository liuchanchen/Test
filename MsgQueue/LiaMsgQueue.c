#include "LiaMsgQueue.h"
#include "../LiaDataCommonType.h"

Int32 main(Int32 argc, Int8 **argv)
{
	mqd_t mqd;

	mq_open("sda", O_WRONLY | O_CREAT, FIFO_MODE, NULL);
	printf("mqd:%d:%s\n",mqd,strerror(errno));

	return 0;
}