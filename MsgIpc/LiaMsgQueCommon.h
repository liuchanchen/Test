#ifndef LiaMsgQueCommon_h__
#define LiaMsgQueCommon_h__

typedef struct msgbuf
{
	long MsgType;
	char MsgBuf[128];
}msgbufStruct;

#define MSG_R 0400
#define MSG_W 0200

#define SVMSG_MODE MSG_R|MSG_W|MSG_R>>3| MSG_R>>6

#endif // LiaMsgQueCommon_h__

