#include <sys/socket.h>
#include "networkmanager.h"
#include "config/configmanager.h"

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
    : pService(NULL)
{
}

NetworkManager::~NetworkManager()
{
    //
}

bool NetworkManager::Init(String serverNameStr)
{
    printf("NetworkManager::Init\n");
    if (!ConfigManager::getInstance().GetConfigIpAddr(serverNameStr, this->ipAddr))
	{
		printf("NetworkManager::Init GetConfigIpAddr error \n");
		return false;
	}

    printf("NetworkManager::Init ip:%s port:%d \n", this->ipAddr.ip.c_str(), this->ipAddr.port);
    return true;
}

Service* NetworkManager::CreateService()
{
    printf("NetworkManager::CreateService\n");
    if (this->pService == NULL)
    {
        this->pService = new Service(this->ipAddr);
    }else
    {
        this->pService->Reset(this->ipAddr);
    }   
    
    return this->pService;
}

Service* NetworkManager::GetService()
{
    return this->pService;
}



