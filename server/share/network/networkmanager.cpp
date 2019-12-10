#include <sys/socket.h>
#include "networkmanager.h"

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
{
    //
}

NetworkManager::~NetworkManager()
{
    //
}

void NetworkManager::Init()
{
    printf("NetworkManager::Init\n");
}

Service* NetworkManager::CreateService(IpAddr ipAddr)
{
    printf("NetworkManager::CreateService\n");
    if (this->pService != NULL)
    {
        this->pService = new Service(ipAddr);
    }else
    {
        this->pService->Reset(ipAddr);
    }   
    
    return this->pService;
}

Service* NetworkManager::GetService()
{
    return this->pService;
}



