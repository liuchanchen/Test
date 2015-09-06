#ifndef LiaCommonMacro_h__
#define LiaCommonMacro_h__

#define JUDGE_POINTER_IS_NULL(x) \
if (NULL==x)\
do{\
	printf("pointer is null!error is in %d,%s,%s \n",__LINE__,__func__,__FILE__);\
	return -1;\
}while (0)

#define ACCESS(Path,mode) \
do{\
	if ((access(Path,mode) < 0)&&(ENOENT== errno))\
	{\
		printf("file %s doesn't exist! \n", Path);\
		return -1;\
	}\
}while (0)

#define Open(pi8Path,flag,mode) \
do{\
	if(open(pi8Path, flag, mode)<0)\
	{\
		printf("open error:%s\n", strerror(errno));\
		return -1;\
	}\
} while (0)

#define Write(i32Fd,pBuf,i32WriteLen) \
do{\
	if (write(i32Fd, pBuf, i32WriteLen)<0)\
	{\
		printf("write error:%s\n", strerror(errno));\
		return -1;\
	}\
} while (0)

#define Read(i32Fd,pBuf,i32ReadLen) \
do{\
if (read(i32Fd, pBuf, i32ReadLen) < 0)\
{\
printf("write error:%s\n", strerror(errno));\
return -1;\
}\
} while (0)

#endif // LiaCommonMacro_h__

