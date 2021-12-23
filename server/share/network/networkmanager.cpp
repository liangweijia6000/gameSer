#ifdef __linux__
//#include <sys/socket.h>
#endif //__linux__

#include "networkmanager.h"
#include "config/configmanager.h"
#include "socketthread.h"

#define NETWORK_MANAGER_PIPE_SIZE 1024*1024
#define NETWORK_MANAGER_EVENT_PIPE_SIZE 1024*1024

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
    //: _pService(nullptr)
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

    // if (_pService != nullptr)
    // {
    //     LOG_ERROR("NetworkManager::Init _pService != NULL");
    //     return false;
    // }

    if (!_msgPipe.init(NETWORK_MANAGER_PIPE_SIZE))
    {
        return false;
    }

    if (!_eventPipe.init(NETWORK_MANAGER_EVENT_PIPE_SIZE))
    {
        return false;
    }
    

    // ListenService* pService = new ListenService(_ipAddr);
    // if (!pService->Init())
    // {
    //     LOG_ERROR("NetworkManager::Init !_pService->Start()");
    //     return false;
    // }

    if (!SocketThread::getInstance().Init())
    {
        return false;
    }

    return true;
}

bool NetworkManager::Start()
{    
    if (!SocketThread::getInstance().Start())
    {
        LOG_ERROR("NetworkManager::Start !SocketThread::getInstance().Start()");
        return false;
    }    

    return true;
}

// ListenService* NetworkManager::GetService()
// {
//     return _pService;
// }

bool NetworkManager::PushEvent(const CtrlEvent &event)
{
    while(!_eventPipe.write((char*)&event, sizeof(event)))
    {
        LOG_DEBUG("NetworkManager::PushEvent");
        //
    }

    return true;
}

bool NetworkManager::PopEvent(CtrlEvent &event)
{
    return _eventPipe.read((char*)&event, sizeof(event));
}

bool NetworkManager::PushMsgEvent(const MsgEvent &event)
{
    while (!_msgPipe.write((char*)&event, sizeof(event)))
    {
        LOG_DEBUG("NetWorkManager::PushMsgEvent");
    }

    return true;    
}

bool NetworkManager::PopMsgEvent(MsgEvent &event)
{
    return _eventPipe.read((char*)&event, sizeof(event));
}




