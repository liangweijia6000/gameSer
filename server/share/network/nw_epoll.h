#ifndef _NW_EPOLL_H_
#define _NW_EPOLL_H_

#ifdef __linux__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "common/servercommon.h"
#include "common/gamelog.h"
#include "nw_api_sock.h"
#include "nw_define.h"


class EpollSock : public ISock
{
    SINGLETON_DECLARATION(EpollSock)
public:
    EpollSock();
    ~EpollSock();
public:
    virtual bool init(uint32 maxSize=256);
    virtual int32 wait();
    virtual bool del(int32 sockfd);
    virtual bool add(int32 sockfd, uint32 events, void* ptr);
    virtual bool getEvent(uint32 pos, uint32& events, void** ptr);
private:
    uint32 _max_event_size = 0;
    int32 _epollfd = 0;
    epoll_event* _pEvents = nullptr;
};

#endif //__linux__

#endif //_NW_EPOLL_H_
