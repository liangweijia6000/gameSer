#ifndef _NW_API_SOCK_
#define _NW_API_SOCK_

#include "common/servercommon.h"
#include "nw_define.h"

#ifdef EPOLLOUT
#define SOCKET_WRITE EPOLLOUT
#else 
#define SOCKET_WRITE 0x004
#endif

#ifdef EPOLLIN
#define SOCKET_READ EPOLLIN
#else 
#define SOCKET_READ 0x001
#endif

#ifdef EPOLLERR
#define SOCKET_ERROR EPOLLERR
#else 
#define SOCKET_ERROR 0x008
#endif


class ISock
{
public:
    //ISock();
    virtual ~ISock(){};
public:
    virtual bool init(uint32 maxSize) = 0;
    virtual int32 wait() = 0;
    virtual bool del(int32 sockfd) = 0;
    virtual bool add(int32 sockfd, uint32 events, void* ptr) = 0;
    virtual bool getEvent(uint32 pos, uint32& events, void** ptr)=0;
private:
};


#endif  //_NW_API_SOCK_