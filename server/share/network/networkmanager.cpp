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

bool NetworkManager::Init(IpAddr& in)
{
    this->ipAddr.ip = in.ip;
    this->ipAddr.port = in.port;

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



