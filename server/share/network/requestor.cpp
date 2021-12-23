#include "requestor.h"


Requester::Requester():_socket_data(this, SocketType_sock)
{
}

Requester::~Requester()
{
}

void Requester::setfd(int32 fd)
{
    _sockfd = fd;
}

void Requester::onRecv()
{
    //
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