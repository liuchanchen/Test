#include"LiaDataCommonType.h"

#define TEST_FILE_PATH "/mnt/hgfs/linux_share/Test/test.txt"

static Int32 Lia_WritePipe(Int32 i32Fd,Int32 i32Len,Uint8 *pui8Buf);
static Lia_OpenWronlyFile(const Int8 *pi8Path,Uint32 *pi32fd);


Int32 main(int argc ,char **argv)
{
    Int8 i8Buf[8];
    Int32 i32fd=-1;

    memset(i8Buf,36,sizeof(i8Buf));
    Lia_OpenWronlyFile(TEST_FILE_PATH,&i32fd);
    Lia_WritePipe(i32fd,sizeof(i8Buf),i8Buf);
    
    return 0;
}

static Int32 Lia_WritePipe(Int32 i32Fd,Int32 i32Len,Uint8 *pui8Buf)
{
    if(write(i32Fd,pui8Buf,i32Len)<0)
    {   
        perror("write error:");
    }
    
    return 0;
}

static Lia_OpenWronlyFile(const Int8 *pi8Path,Uint32 *pi32fd)
{
    if(NULL==pi8Path)
    {
        printf("pui8Path is null!\n");
        return -1;
    }
    if(NULL==pi32fd)
    {
        printf("pi32fd is null!\n");
        return -1;
    }
    *pi32fd=open(pi8Path,O_RDONLY);
    if((*pi32fd)<0)
    {
        perror("file open error:");
        return -1;
    }

    return 0;
}


