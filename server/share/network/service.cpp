
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
    this->ip = ipAddr.ip;
    this->port = ipAddr.port;
    this->listenSocketfd = -1;
    this->isRun = false;
}

Service::~Service()
{
}

void Service::Reset(IpAddr ipAddr)
{
    this->ip = ipAddr.ip;
    this->port = ipAddr.port;
    this->listenSocketfd = -1;
}

bool Service::Start()
{
    printf("Service::Start at ip:%s port:%d\n", this->ip.c_str(), this->port);

    this->listenSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listenSocketfd < 0)
    {
        return false;
    }

    int flags = fcntl(this->listenSocketfd, F_GETFL, 0);
    fcntl(this->listenSocketfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(this->ip.c_str());
    sockaddr.sin_port = htons(this->port);

    int32 res = bind(this->listenSocketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (res < 0)
    {
        printf("Service::Start bind error\n");
        return false;
    }

    res = listen(this->listenSocketfd, 512);
    if (res < 0)
    {
        printf("Service::Start listen error\n");
        return false;
    }

    this->isRun = true;
    
    return true;
}

bool Service::Start_epoll()
{

    printf("Service::Start at ip:%s port:%d\n", this->ip.c_str(), this->port);

    this->listenSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listenSocketfd < 0)
    {
        return false;
    }

    int flags = fcntl(this->listenSocketfd, F_GETFL, 0);
    fcntl(this->listenSocketfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(this->ip.c_str());
    sockaddr.sin_port = htons(this->port);

    int32 res = bind(this->listenSocketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (res < 0)
    {
        printf("Service::Start bind error\n");
        return false;
    }

    res = listen(this->listenSocketfd, 512);
    if (res < 0)
    {
        printf("Service::Start listen error\n");
        return false;
    }

    this->epollfd = epoll_create(4096);
    printf("Service::Start_epoll epollfd:%d\n", epollfd);

    struct epoll_event ev;

    ev.data.fd = this->listenSocketfd;
    ev.events = EPOLLIN|EPOLLET;

    epoll_ctl(this->epollfd, EPOLL_CTL_ADD, listenSocketfd, &ev);


    this->isRun = true;

    return true;
}

void Service::Stop()
{
    close(this->listenSocketfd);
    for(auto it:this->socketfdVec)
    {
        close(it);
    }

    this->isRun =false;
}

void Service::Process()
{
    //printf("Service::Process\n");
    struct sockaddr_in remoteAddr;

    uint32 structLen = sizeof(struct sockaddr);

    int32 acceptfd = accept(this->listenSocketfd, (struct sockaddr *)&remoteAddr, &structLen);
    if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
    {
        //        
    }else
    {
        this->socketfdVec.push_back(acceptfd);
    }

    for (auto it = this->socketfdVec.begin(); it != this->socketfdVec.end(); ++it)
    {
        char buf[BUFSIZ];
        memset(buf, 0, BUFSIZ);

        int32 len = recv(*it, &buf, BUFSIZ, 0);
        if ((len < 0 && errno != EWOULDBLOCK) || len == 0)
        {
            this->socketfdVec.erase(it);
            it--;
            continue;
        }

        InitMsgA2C tempmsg;
        tempmsg.ParseFromString(buf);

        printf("Service::Process recv len:%d\n", len);

        printf("Service::Process recv:%d \n", tempmsg.times());
        printf("Service::Process recv:%s \n", tempmsg.name().c_str());

        //printf("Service::Process recv:%s \n", buf);
    }
}

void Service::Process_epoll()
{
    if (!this->isRun)
    {
        return;
    }

    struct epoll_event events[256];

    int32 nfds = epoll_wait(this->epollfd, events, 256, 500);

    printf("Process_epoll nfds:%d\n", nfds);

    for (int32 i = 0; i < nfds; i++)
    {
        int32 eventfd = events[i].data.fd;
        if (eventfd < 0)
        {
            printf("eventfd < 0 \n");
            continue;
        }        

        if (eventfd == this->listenSocketfd)
        {
            struct sockaddr_in remoteAddr;
            uint32 structLen = sizeof(struct sockaddr);
            int32 acceptfd = accept(this->listenSocketfd, (struct sockaddr *)&remoteAddr, &structLen);
            if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            {
                //        
            }else
            {
                struct epoll_event ev;
                ev.data.fd = acceptfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(this->epollfd, EPOLL_CTL_ADD, acceptfd, &ev);
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
    
    
}


void Service::SendMsg(char* msg)
{
    if (!IsRun())
    {
        return;
    }
    
    //send(this->socketfd, msg, sizeof(*msg), 0);
}

bool Service::IsRun()
{
    return this->isRun;
}

