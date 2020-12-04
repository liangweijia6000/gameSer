#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif //__linux__

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "service.h"
#include "networkmanager.h"
#include "protocol/protocol.pb.h"

Service::Service(IpAddr ipAddr)
    : _ip(ipAddr.ip)
    , _port(ipAddr.port)
    , _listenSocketfd(-1)
{
}

Service::~Service()
{
    //
}

bool Service::Init()
{

    LOG_DEBUG("Service::Start at ip:%s port:%d", _ip.c_str(), _port);

#ifdef __linux__
    _listenSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenSocketfd < 0)
    {
        return false;
    }

    int flags = fcntl(_listenSocketfd, F_GETFL, 0);
    fcntl(_listenSocketfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(_ip.c_str());
    sockaddr.sin_port = htons(_port);

    int32 res = bind(_listenSocketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (res < 0)
    {
        LOG_ERROR("Service::Start bind error");
        return false;
    }

    res = listen(_listenSocketfd, 512);
    if (res < 0)
    {
        LOG_ERROR("Service::Start listen error");
        return false;
    }

    _epollfd = epoll_create(4096);
    LOG_DEBUG("Service::Start_epoll epollfd:%d", _epollfd);

    EpollData* pEpolldata = new EpollData();
    pEpolldata->type = EpollType_listen;

    struct epoll_event ev;
    ev.data.ptr = pEpolldata;
    ev.events = EPOLLIN;

    epoll_ctl(_epollfd, EPOLL_CTL_ADD, _listenSocketfd, &ev);


    _isRun = true;
#endif //__linux__

    return true;
}

/*
void Service::Stop()
{
#ifdef __linux__
    close(_listenSocketfd);
    for(auto it:_socketfdVec)
    {
        close(it);
    }

    _isRun =false;
#endif //__linux__
}
*/

bool Service::Process_epoll()
{
    if (!_isRun)
    {
        return false;
    }

#ifdef __linux__
    struct epoll_event events[256];

    int32 nfds = epoll_wait(_epollfd, events, 256, 1);
    if (nfds < 0)
    {
        return false;
    }    

    if(nfds != 0)
    {
        LOG_DEBUG("Process_epoll nfds:%d", nfds);
    }

    for (int32 i = 0; i < nfds; i++)
    {
        EpollData* pEpollData = (EpollData*)events[i].data.ptr;

        if (pEpollData == NULL)
        {
            continue;
        }        

        if (pEpollData->type == EpollType_listen)
        {
            struct sockaddr_in remoteAddr;
            uint32 structLen = sizeof(struct sockaddr);
            int32 acceptfd = accept(_listenSocketfd, (struct sockaddr *)&remoteAddr, &structLen);
            if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            {
                //        
            }else
            {
                EpollData* pEpolldata = new EpollData();
                pEpolldata->type = EpollType_sock;
                pEpollData->fd = acceptfd;

                struct epoll_event ev;
                ev.data.ptr = pEpolldata;
                ev.events = EPOLLIN;

                epoll_ctl(_epollfd, EPOLL_CTL_ADD, acceptfd, &ev);
            }

            continue;
        }
        
        if (events[i].events & EPOLLIN)
        {
            char buf[BUFSIZ];
            memset(buf, 0, BUFSIZ);
            int32 readSize = read(pEpollData->fd, buf, BUFSIZ);
            if (readSize < 0)
            {
                if (errno == ECONNRESET)
                {
                    close(pEpollData->fd);
                    events[i].data.ptr = NULL;
                    pEpollData->Release();
                    continue;
                }    
            }else if (readSize == 0)
            {
                close(pEpollData->fd);
                events[i].data.ptr = NULL;
                pEpollData->Release();
                continue;
            }

            LOG_DEBUG("read buf:%s", buf);
            
        }else if (events[i].events & EPOLLOUT)
        {
            //
        }    
    }
#endif //__linux__

    return true;
}

/*
void Service::SendMsg(char* msg)
{
    if (!IsRun())
    {
        return;
    }
    
    //send(_socketfd, msg, sizeof(*msg), 0);
}
*/

bool Service::IsRun()
{
    return _isRun;
}

