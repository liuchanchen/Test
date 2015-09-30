#include "../LiaCommon.h"

int Lia_ExamSizeof();
int Test(char * p);
int BocomRecruit();
void SetBit(int data, int bit);
typedef Int32

int main(int argc, char ** argv)
{
	int data = 0;

	BocomRecruit();
	SetBit(data,3);
	//Lia_ExamSizeof();

	return 0;
}

int Lia_ExamSizeof()
{
	int *p;
	int str[10];
	char *pstr = "Bocom";
	struct
	{
		char a;
		int b[5];
	}stx[2];
	
	printf("sizeof p:%d\n", sizeof(p));
	printf("sizeof str:%d\n", sizeof(str));
	printf("sizeof str:%d\n", sizeof(pstr));
	printf("sizeof stx1:%d\n", sizeof(stx));

	return 0;
}

int BocomRecruit()
{
	char *p;

	Test(p);
	//strcpy(p, "Bocom\n");
	//printf("%s", p);

	return 0;
}

int Test(char * Addr)
{
	Addr = malloc(sizeof(char) * 10);
	strcpy(Addr, "Bocom\n");
	printf("%s", Addr);
	return 0;
}

void* mem_cpy(void *dst, const void *src, int len)   //参数定义为空指针类型，并且源地址内容不应该被改变，因此用const修饰  
{

    if(NULL==dst || NULL==src)
		return dst;
	
	while (len--)
	{
	        *(char*)dst = *(char*)src;    //强制转化为字符指针类型，并进行内容复制  
	        dst = (char*)dst + 1;
	        src = (char*)src + 1;
	}
	    return dst;
 }

void SetBit(int data ,int bit)
{
	if (bit > 31)
	{
		return ;
	}
	data = data|(0x1<< bit);

	return ;
}