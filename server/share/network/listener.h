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
private:
    int32 _listen_fd = -1;

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