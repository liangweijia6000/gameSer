#include "requestor.h"


Requester::Requester():_socket_data(this, SocketType_sock)
{
}

Requester::~Requester()
{
}

void Requester::setSocket(int32 socket)
{
    _socket = socket;
}

void Requester::onRecv()
{
    //int32 recv = recv(s, buf, )
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
