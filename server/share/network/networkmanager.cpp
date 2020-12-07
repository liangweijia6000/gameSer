#ifdef __linux__
#include <sys/socket.h>
#endif //__linux__

#include "networkmanager.h"
#include "config/configmanager.h"
#include "epollthread.h"

SINGLETON_DEFINITION(NetworkManager)

#define NETWORK_MANAGER_PIPE_SIZE 1024*1024

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

    if (_pService != NULL)
    {
        LOG_ERROR("NetworkManager::Init _pService != NULL");
        return false;
    }

    if (!_pipe.init(NETWORK_MANAGER_PIPE_SIZE))
    {
        return false;
    }    

    _pService = new Service(_ipAddr);

    if (!_pService->Init())
    {
        LOG_ERROR("NetworkManager::Init !_pService->Start()");
        return false;
    }

    if (!EpollThread::getInstance().Init(_pService))
    {
        return false;
    }

    return true;
}

bool NetworkManager::Start()
{    
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



