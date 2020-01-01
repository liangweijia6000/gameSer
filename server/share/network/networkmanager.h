#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

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
	bool Init(String serverName);
	Service* CreateService();
	Service* GetService();
private:
	IpAddr ipAddr;
	Service* pService;

};


#endif  //_NETWORK_H_
