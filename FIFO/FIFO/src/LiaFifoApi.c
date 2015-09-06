#include "LiaFifoApi.h"



/************************************
Function:    Lia_Fifo_Init
description:  Creat Fifo.If the fifo has
			existed,return -1
Author: liujian
Date: 2015/09/04
Input: const Int8 * pi8PathSeverToClient £ºFIFO path name
		 Int32 mode £ºfifo mode
Returns:   0 indicates success
			negative numbers indicate failure
************************************/
Int32 Lia_Fifo_Init(const Int8 * pi8Path,Int32 mode)
{
	JUDGE_POINTER_IS_NULL(pi8Path);

	if ((mkfifo(pi8Path, mode) < 0) && (EEXIST != errno))
	{
		printf("fifo creats error:%s!\n",strerror(errno));
		return -1;
	}

	return 0;
}

/************************************
Functon:    Lia_Fifo_UnInit
Description:  unlink fifo.If the fifo has
			been unlinked, return -1
Author: liujian
Date: 2015/09/04
Input: const Int8 * pi8Path £ºFIFO path name
Returns: 0 indicates success
			negative number indicates failure
************************************/
Int32 Lia_Fifo_UnInit(const Int8 * pi8Path)
{
	JUDGE_POINTER_IS_NULL(pi8Path);
	ACCESS(pi8Path,F_OK);//determines fifo if path exists
	unlink(pi8Path);

	return 0;
}

/*********************************************
Functon:    Lia_Fifo_Read
Description:  read context from fifo
Author: liujian
Date: 2015/09/04
Input: void * pBuf:the context being readed from fifo
		pi8Path:fifo path
		i32MaxReadLen:maxium length of read
Returns: 0 indicates success
		negative numbers indicate failure
*********************************************/
Int32 Lia_Fifo_Read(Int8 *pi8Path,void * pBuf,Int32 i32MaxReadLen)
{
	Int32 i32Fd=-1;
	Int32 i32ReadCnt = -1;
	JUDGE_POINTER_IS_NULL(pBuf);
	JUDGE_POINTER_IS_NULL(pi8Path);
	ACCESS(pi8Path,F_OK);
	i32Fd=open(pi8Path, O_RDONLY,0);
	if (i32Fd < 0)
	{
		printf("open error:%s\n", strerror(errno));
		return -1;
	}
	i32ReadCnt = read(i32Fd, pBuf, i32MaxReadLen);
	if (i32ReadCnt<0)
	{
		printf("read error\n");
		return -1;
	}
	else if(0== i32ReadCnt)//write fifo has closed,unlink the read fifo
	{
		unlink(pi8Path);
	}
	close(i32Fd);

	return 0;
}

/*********************************************
Functon:    Lia_Fifo_Write
Description: write to fifo 
Author: liujian
Date: 2015/09/04
Input: const void * pBuf:the context should be 
		writen to the fifo
		pi8Path:fifo path
		i32WriteLen:maxium length of write
Returns: 0 indicates success
		negative numbers indicate failure
*********************************************/
Int32 Lia_Fifo_Write(Int8 *pi8Path,const void * pBuf, Int32 i32WriteLen)
{
	Int32 i32Fd = -1;
	JUDGE_POINTER_IS_NULL(pBuf);
	JUDGE_POINTER_IS_NULL(pi8Path);
	ACCESS(pi8Path, F_OK);
	printf("pi8Path:%s\n", pi8Path);
	i32Fd = open(pi8Path, O_WRONLY,0);
	if (i32Fd < 0)
	{
		printf("open error:%s\n",strerror(errno));
		return -1;
	}
	if (write(i32Fd, pBuf, i32WriteLen) < 0)
	{
		printf("write error\n");
		return -1;
	}
	close(i32Fd);

	return 0;
}