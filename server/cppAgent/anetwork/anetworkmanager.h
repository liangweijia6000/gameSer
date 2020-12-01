#ifndef _A_NETWORK_MANAGER_H_
#define _A_NETWORK_MANAGER_H_

#include "network/networkmanager.h"
#include "commoninclude.h"

class  ANetworkManager
{
    SINGLETON_DECLARATION(ANetworkManager);
public:
     ANetworkManager();
    ~ ANetworkManager();
public:
    bool start(String serverNameStr);
};





#endif //_A_NETWORK_MANAGER_H_