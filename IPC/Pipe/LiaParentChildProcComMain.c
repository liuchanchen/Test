#include "../Pipe/Lia_PipeOperation.h"

int main(int argc,char **argv)
{
	int i32ChildPid=-1;
	int ParentToChildPipe[2];
	int ChildToParentPipe[2];

	if(0==(i32ChildPid=fork()))
	{
		while(1);
		exit(0);
	}

	waitpid(i32ChildPid,NULL,0);
	exit(0);

	return 0; 
}

static Int32 Lia_PipeSeverOp()
{
	return 0;
}


