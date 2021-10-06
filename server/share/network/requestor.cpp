#include "requestor.h"


Requester::Requester():_epoll_data(this, EpollType_sock)
{
}

Requester::~Requester()
{
}

void Requester::setfd(int32 fd)
{
    _sockfd = fd;
}


SINGLETON_DEFINITION(RequesterManager)

RequesterManager::RequesterManager()
{
}

RequesterManager::~RequesterManager()
{
}

Requester* RequesterManager::create()
{
    Requester* pRequester = new Requester();
    return pRequester;
}