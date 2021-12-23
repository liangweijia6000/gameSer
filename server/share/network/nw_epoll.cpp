#include "nw_epoll.h"

#ifdef __linux__

SINGLETON_DEFINITION(EpollSock)

EpollSock::EpollSock()
{
}

EpollSock::~EpollSock()
{
}

bool EpollSock::init(uint32 maxSize)
{
    _max_event_size = maxSize;
    _pEvents = new epoll_event[_max_event_size];
    _epollfd = epoll_create(_max_event_size);
    return true;
}

int32 EpollSock::wait()
{
    int32 count = epoll_wait(_epollfd, _pEvents, 256, 1);
    if (count < 0)
    {
        if(errno == EINTR) {
            return 0;
        }else{
            LOG_ERROR("epoll_wait error errno:%d, %s", errno, strerror(errno));
        }
    }

    return count;    
}

bool EpollSock::getEvent(uint32 pos, uint32& events, void** ptr)
{
    if(!_pEvents || pos >= _max_event_size || !ptr) {
        return false;
    }

    *ptr = _pEvents[pos].data.ptr;
    events = _pEvents[pos].events;
    
    return true;
}

bool EpollSock::del(int32 sockfd)
{
    //TODO:
    return true;
}

bool EpollSock::add(int32 sockfd, uint32 events, void* ptr)
{
    struct epoll_event ev;
    ev.data.ptr = ptr;
    ev.events = events;

    epoll_ctl(_epollfd, EPOLL_CTL_ADD, sockfd, &ev);

    return true;
}

#endif //__linux__
