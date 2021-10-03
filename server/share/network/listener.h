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

class listener
{
public:
    listener();
    ~listener();
public:
    Requester* accept();
private:
    int32 _listen_fd = -1;
    
    struct sockaddr_in _remoteAddr;
};


#endif //_LISTENER_H_