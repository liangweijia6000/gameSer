#ifndef _NW_DEFINE_H_
#define _NW_DEFINE_H_

#include "common/servercommon.h"

enum CtrlEventType
{
	CtrlEventType_AddListen = 1,	//增加监听端口
};

struct AddListenEvent
{
	uint32 socketfd;
};

struct CtrlEvent
{
    CtrlEventType type;
	union EventInfo
	{
		AddListenEvent addListenEvent;
	}eventInfo;
};



//TODO:

struct EpollData
{
    EpollData()
    : type(0)
    , fd(0)
    {}

    void Release()
    {
        delete this;
    }

    uint32 type;
    uint32 fd;
};

enum EpollType
{
    EpollType_listen = 1,
    EpollType_sock = 2,
};

#endif //_NW_DEFINE_H_