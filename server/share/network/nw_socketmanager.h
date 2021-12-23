#ifndef _NW_SOCKET_MANAGER_H_
#define _NW_SOCKET_MANAGER_H_

#include "common/servercommon.h"
#include "nw_api_sock.h"

class SocketManager : public ISock
{
    SINGLETON_DECLARATION(SocketManager)
public:
    SocketManager(){};
    ~SocketManager(){};
public:
    bool init(uint32 maxSize);
    int32 wait(){return _pSocket?_pSocket->wait():0;}
    bool del(int32 sockfd){return _pSocket?_pSocket->del(sockfd):false;}
    bool add(int32 sockfd, uint32 events, void* ptr){return _pSocket?_pSocket->add(sockfd, events, ptr):false;};
    bool getEvent(uint32 pos, uint32& events, void** ptr){return _pSocket?_pSocket->getEvent(pos, events, ptr):false;};
private:
	ISock* _pSocket;
};

#endif //_NW_SOCKET_MANAGER_H_
