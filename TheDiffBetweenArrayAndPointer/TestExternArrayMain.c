#include"LiaDataCommonType.h"

extern Int32 Lia_TestArray();

extern int *g_i32TestArray;


//Int32 g_i32TestArray[2]={2,3};
static Int32 Lia_TestArrayMain();

int main(int argc,char **argv)
{
	Lia_TestArrayMain();
	Lia_TestArray();
	
	return 0;
}

static Int32 Lia_TestArrayMain()
{
	printf("%x in %s\n",g_i32TestArray,__func__);
	
	return 0;	
}
