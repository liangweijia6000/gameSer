#include "listener.h"
//#include "requestor.h"

listener::listener()
{
}

listener::~listener()
{
}

Requester* listener::accept()
{
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

    //_epoll_data.






    return nullptr;
}