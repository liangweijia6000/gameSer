#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include <common/servercommon.h>

class NetworkManager
{
    SINGLETON_DECLARATION(NetworkManager)
public:
	NetworkManager();
	~NetworkManager();
public:
	void Init();
};


#endif  //_NETWORK_H_
