#include "../../../LiaCommon.h"
#include "LiaFifoApi.h"

Int32 main(Int32 argc, char ** argv)
{
	Int8 *pWriteBuf = "This is a greeting from sever !";
	Int8 i8ReadBuf[128];

	memset(i8ReadBuf,0x0,sizeof(i8ReadBuf));
	Lia_Fifo_Init(FIFO_FROM_SEVER_TO_CLIENT, FIFO_MODE);
	Lia_Fifo_Write(FIFO_FROM_SEVER_TO_CLIENT, pWriteBuf,128);
	Lia_Fifo_Read(FIFO_FROM_CLIENT_TO_SEVER,i8ReadBuf,128);
	printf("read buf:%s\n", i8ReadBuf);
	Lia_Fifo_UnInit(FIFO_FROM_CLIENT_TO_SEVER);

	return 0;
}