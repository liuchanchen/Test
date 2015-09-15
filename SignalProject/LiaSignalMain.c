#include "LiaSignalApi.h"

Int32 main(Int32 argc, Int8 **argv)
{
	pid_t ChildPid,ParentPid;
	struct sigaction stact;
	union sigval Val;
		//Lia_SignalWholeProcess();
	ChildPid = fork();
	ParentPid = getpid();
	if (0==ChildPid)
	{
		Val.sival_int= 2;
		sigqueue(ParentPid,SIGRTMAX-1, Val);
		exit(0);
	}
	stact.sa_flags = 0;
	stact.__sigaction_handler = Lia_Handler;
	sigaction(SIGRTMAX - 1,&stact,NULL);
	waitpid(ChildPid, NULL, 0);

	return 0;
}

void Lia_Handler(int singo)
{


	return;
}