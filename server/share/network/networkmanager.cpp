#include <sys/socket.h>
#include "networkmanager.h"
#include "config/configmanager.h"

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
{
    //
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
    return true;
}

Service* NetworkManager::CreateService()
{
    printf("NetworkManager::CreateService\n");
    if (this->pService != NULL)
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



