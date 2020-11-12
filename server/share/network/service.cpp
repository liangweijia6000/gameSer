
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "service.h"
#include "networkmanager.h"

#include "protocol/protocol.pb.h"

Service::Service(IpAddr ipAddr)
{
    //
}

Service::~Service()
{
    //
}

void Service::Reset(IpAddr ipAddr)
{
    _ip = ipAddr.ip;
    _port = ipAddr.port;
    _listenSocketfd = -1;
}

bool Service::Start()
{
    printf("Service::Start at ip:%s port:%d\n", _ip.c_str(), _port);

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
        printf("Service::Start bind error\n");
        return false;
    }

    res = listen(_listenSocketfd, 512);
    if (res < 0)
    {
        printf("Service::Start listen error\n");
        return false;
    }

    _isRun = true;
    
    return true;
}

bool Service::Start_epoll()
{

    printf("Service::Start at ip:%s port:%d\n", _ip.c_str(), _port);

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
        printf("Service::Start bind error\n");
        return false;
    }

    res = listen(_listenSocketfd, 512);
    if (res < 0)
    {
        printf("Service::Start listen error\n");
        return false;
    }

    _epollfd = epoll_create(4096);
    printf("Service::Start_epoll epollfd:%d\n", _epollfd);

    struct epoll_event ev;

    ev.data.fd = _listenSocketfd;
    ev.events = EPOLLIN|EPOLLET;

    epoll_ctl(_epollfd, EPOLL_CTL_ADD, _listenSocketfd, &ev);


    _isRun = true;

    return true;
}

void Service::Stop()
{
    close(_listenSocketfd);
    for(auto it:_socketfdVec)
    {
        close(it);
    }

    _isRun =false;
}

bool Service::Process_epoll()
{
    if (!_isRun)
    {
        return false;
    }

    struct epoll_event events[256];

    int32 nfds = epoll_wait(_epollfd, events, 256, 500);
    if (nfds < 0)
    {
        return false;
    }    

    printf("Process_epoll nfds:%d\n", nfds);

    for (int32 i = 0; i < nfds; i++)
    {
        int32 eventfd = events[i].data.fd;
        if (eventfd < 0)
        {
            printf("eventfd < 0 \n");
            continue;
        }        

        if (eventfd == _listenSocketfd)
        {
            struct sockaddr_in remoteAddr;
            uint32 structLen = sizeof(struct sockaddr);
            int32 acceptfd = accept(_listenSocketfd, (struct sockaddr *)&remoteAddr, &structLen);
            if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            {
                //        
            }else
            {
                struct epoll_event ev;
                ev.data.fd = acceptfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(_epollfd, EPOLL_CTL_ADD, acceptfd, &ev);
            }

            continue;
        }
        
        if (events[i].events & EPOLLIN)
        {
            char buf[BUFSIZ];
            memset(buf, 0, BUFSIZ);
            int32 readSize = read(eventfd, buf, BUFSIZ);
            if (readSize < 0)
            {
                if (errno == ECONNRESET)
                {
                    close(eventfd);
                    events[i].data.fd = -1;
                    continue;
                }    
            }else if (readSize == 0)
            {
                close(eventfd);
                events[i].data.fd = -1;
                continue;
            }

            printf("read buf:%s", buf);
            
        }else if (events[i].events & EPOLLOUT)
        {
            //
        }        
    }

    return true;
}


void Service::SendMsg(char* msg)
{
    if (!IsRun())
    {
        return;
    }
    
    //send(_socketfd, msg, sizeof(*msg), 0);
}

bool Service::IsRun()
{
    return _isRun;
}

