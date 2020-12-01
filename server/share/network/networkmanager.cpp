#ifdef __linux__
#include <sys/socket.h>
#endif //__linux__

#include "networkmanager.h"
#include "config/configmanager.h"
#include "epollthread.h"

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
    : _pService(NULL)
{
}

NetworkManager::~NetworkManager()
{
    //
}

bool NetworkManager::Init(IpAddr& in)
{
    _ipAddr.ip = in.ip;
    _ipAddr.port = in.port;

    LOG_DEBUG("NetworkManager::Init ip:%s port:%d", _ipAddr.ip.c_str(), _ipAddr.port);

    if (_pService == NULL)
    {
        _pService = new Service(_ipAddr);
    }else
    {
        _pService->Reset(_ipAddr);
    }

    if (!EpollThread::getInstance().Init(_pService))
    {
        return false;
    }

    return true;
}

bool NetworkManager::Start()
{
    if (!_pService->Start())
    {
        LOG_ERROR("NetworkManager::Start !_pService->Start()");
        return false;
    }
    
    if (!EpollThread::getInstance().Start())
    {
        LOG_ERROR("NetworkManager::Start !EpollThread::getInstance().Start()");
        return false;
    }    

    return true;
}

Service* NetworkManager::GetService()
{
    return _pService;
}



