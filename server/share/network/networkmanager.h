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
	void Init();
	Service* CreateService(IpAddr ipAddr);
	Service* GetService();
private:
	Service* pService;

};


#endif  //_NETWORK_H_
