#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#ifdef __linux__
#include <sys/epoll.h>
#endif //__linux__

#include "common/servercommon.h"
#include "service.h"

struct IpAddr
{
	String ip;
	uint32 port;
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
	Service* GetService();
private:
	IpAddr _ipAddr;
	Service* _pService;	//TODO:

};


#endif  //_NETWORK_H_
