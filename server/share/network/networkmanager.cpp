#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif //__linux__

#include "networkmanager.h"
#include "config/configmanager.h"
#include "socketthread.h"

#define NETWORK_MANAGER_PIPE_SIZE 1024 * 1024
#define NETWORK_MANAGER_EVENT_PIPE_SIZE 1024 * 1024

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
//: _pService(nullptr)
{
}

NetworkManager::~NetworkManager()
{
    //
}

bool NetworkManager::Init(IpAddr &in) //TODO: 从这里开始监听么?
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

    //TODO: 调试用临时代码

    //bind + listen

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        LOG_ERROR("socket error");
        exit(1);
    }

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(_ip.c_str());
    sockaddr.sin_port = htons(_ipAddr.port);

    int32 res = bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (res < 0)
    {
        LOG_ERROR("ListenService::Start bind error");
        return false;
    }

    res = listen(socket_fd, 512);
    if (res < 0)
    {
        LOG_ERROR("ListenService::Start listen error");
        return false;
    }

    CtrlEvent event;
    event.type = CtrlEventType_AddListen;
    event.eventInfo.addListenEvent.id = 1;
    event.eventInfo.addListenEvent.socketfd = socket_fd;
    PushEvent(event);

    return true;
}

// ListenService* NetworkManager::GetService()
// {
//     return _pService;
// }

bool NetworkManager::PushEvent(const CtrlEvent &event)
{

    LOG_INFO("NetworkManager::PushEvent eventType: %d", event.type);

    while (!_eventPipe.write((char *)&event, sizeof(event)))
    {
        LOG_DEBUG("NetworkManager::PushEvent wait");
        //
    }

    return true;
}

bool NetworkManager::PopEvent(CtrlEvent &event)
{
    return _eventPipe.read((char *)&event, sizeof(event));
}

bool NetworkManager::PushMsgEvent(const MsgEvent &event)
{
    while (!_msgPipe.write((char *)&event, sizeof(event)))
    {
        LOG_DEBUG("NetWorkManager::PushMsgEvent");
    }

    return true;
}

bool NetworkManager::PopMsgEvent(MsgEvent &event)
{
    return _eventPipe.read((char *)&event, sizeof(event));
}
