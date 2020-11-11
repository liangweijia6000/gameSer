#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include <sys/epoll.h>

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
	Service* CreateService();
	Service* GetService();
private:
	IpAddr ipAddr;
	Service* pService;	//TODO:

};


#endif  //_NETWORK_H_
