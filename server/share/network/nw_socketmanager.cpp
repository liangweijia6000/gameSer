#include "nw_socketmanager.h"
#include "nw_epoll.h"

SINGLETON_DEFINITION(SocketManager)

bool SocketManager::init(uint32 maxSize){

#ifdef __linux__
     _pSocket = &EpollSock::getInstance();
    if(!_pSocket) {
        return false;
    }
    _pSocket->init(maxSize);
#endif //__linux__

    return true;
}