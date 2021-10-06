#include "listener.h"
//#include "requestor.h"

Listener::Listener():_epoll_data(this, EpollType_listen)
{
}

Listener::~Listener()
{
}

Requester* Listener::accept()
{
    //struct sockaddr_in remoteAddr;
    uint32 structLen = sizeof(struct sockaddr);
    int32 acceptfd = ::accept(_listen_fd, (struct sockaddr *)&_remoteAddr, &structLen);
    if(acceptfd == -1) {
        //log
        return nullptr;
    }

    Requester* pRequester = RequesterManager::getInstance().create();
    if(!pRequester) {
        return nullptr;
    }

    pRequester->setfd(acceptfd);

    //TODO: accept 远端连接信息保存在Requester中

    return pRequester;
}

SINGLETON_DEFINITION(ListenerManager)

ListenerManager::ListenerManager()
{
    //
}

ListenerManager::~ListenerManager()
{
    //
}

Listener* ListenerManager::create()
{
    Listener* pListener = new Listener();
    return pListener;
}