#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#ifdef __linux__
#include <sys/epoll.h>
#endif //__linux__

#include "common/servercommon.h"
#include "service.h"
#include "memorypipe.h"

struct IpAddr
{
	String ip;
	uint32 port;
};

struct MsgEvent
{
	uint32 type;
	uint32 id;
	uint32 msglen;
};

struct CtrlEvent
{
	enum CtrlEventType
	{
		CtrlEventType_AddListen = 1,
	};
	uint32 type;
	uint32 socketfd;
};


class NetworkManager
{
    SINGLETON_DECLARATION(NetworkManager)
public:
	NetworkManager();
	~NetworkManager();
public:
	bool Init(IpAddr& in);
	bool Start();
	ListenService* GetService();
	bool PushEvent(const CtrlEvent &event);
	bool PopEvent(CtrlEvent &event);

	//void Push
private:
	IpAddr _ipAddr;
	ListenService* _pService;	//TODO:

	//
	MemoryPipe _msgPipe;	//

	MemoryPipe _eventPipe;
};


#endif  //_NETWORK_H_
