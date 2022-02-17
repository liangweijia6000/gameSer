#include "listener.h"
#include "nw_socketmanager.h"
#include "common/gamelog.h"

Listener::Listener():_socket_data(this, SocketType_listen)
{
}

Listener::~Listener()
{
}

void Listener::setListenSocket(int32 socket)
{
    this->_listen_socket = socket;
}

SocketData* Listener::getSocketData() {
    return &_socket_data;
}

//
Requester* Listener::accept()
{
    //struct sockaddr_in remoteAddr;
    uint32 structLen = sizeof(struct sockaddr);
    int32 acceptfd = ::accept(this->_listen_socket, (struct sockaddr *)&_remoteAddr, &structLen);
    if(acceptfd == -1) {
        LOG_ERROR("Listener::accept ::accept fd == -1");
        return nullptr;
    }

    Requester* pRequester = RequesterManager::getInstance().create();
    if(!pRequester) {
        return nullptr;
    }

    //TODO: accept 远端连接信息保存在Requester中
    pRequester->setfd(acceptfd);
    return pRequester;
}

//======================================================

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
