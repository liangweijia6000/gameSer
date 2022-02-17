#ifndef _LISTENER_H_
#define _LISTENER_H_

#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif //__linux__

#include "common/servercommon.h"
#include "nw_define.h"
#include "requestor.h"

class Listener
{
public:
    Listener();
    ~Listener();
public:
    Requester* accept();
    void setListenSocket(int32 socket){this->_listen_socket = socket;}
    int32 getListensocket(){return this->_listen_socket;}
    SocketData* getSocketData(){return &(this->_socket_data);}
private:
    int32 _listen_socket = -1;

    SocketData _socket_data;
    
    struct sockaddr_in _remoteAddr;
};

class ListenerManager
{
    SINGLETON_DECLARATION(ListenerManager)
public:
    ListenerManager();
    ~ListenerManager();
public:
    Listener* create();
};

#endif //_LISTENER_H_