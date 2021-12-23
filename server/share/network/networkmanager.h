#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include "common/servercommon.h"
#include "service.h"
#include "memorypipe.h"
#include "nw_define.h"

#include "nw_api_sock.h"

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

class NetworkManager
{
    SINGLETON_DECLARATION(NetworkManager)
public:
	NetworkManager();
	~NetworkManager();
public:
	bool Init(IpAddr& in);
	bool Start();
	// ListenService* GetService();

	bool PushEvent(const CtrlEvent &event);
	bool PopEvent(CtrlEvent &event);

	bool PushMsgEvent(const MsgEvent &event);
	bool PopMsgEvent(MsgEvent &event);
private:
	IpAddr _ipAddr;
	
	MemoryPipe _msgPipe;	//TODO:是不是需要两个，一出一进？

	MemoryPipe _eventPipe;
};


#endif  //_NETWORK_H_
