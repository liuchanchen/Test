#include"LiaDataCommonType.h"

int g_i32TestArray[2]={2,3};

Int32 Lia_TestArray();

Int32 Lia_TestArray()
{
	printf("%x %d in %s\n",g_i32TestArray,g_i32TestArray[1],__func__);
	
	return 0;	
}