#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif //__linux__

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "epollthread.h"
#include "networkmanager.h"
#include "protocol/protocol.pb.h"

SINGLETON_DEFINITION(EpollThread)

EpollThread::EpollThread()
{
}

EpollThread::~EpollThread()
{
}

bool EpollThread::Init()
{
    LOG_DEBUG("EpollThread Init");

    _epollfd = epoll_create(4096);
    LOG_DEBUG("ListenService::Start_epoll epollfd:%d", _epollfd);

    return true;
}

bool EpollThread::Start()
{
    LOG_DEBUG("EpollThread Start");

#ifdef __linux__
    if (0 != pthread_create(&_thread_id, NULL, (void *(*)(void *))(_thread_func_static), this))
	{
        LOG_DEBUG("pthread_create error");
		return false;
	}
#endif //__linux__

    _isRun = true;
    
    return _isRun;
}

void* EpollThread::_thread_func_static(void* arg)   //static
{
    EpollThread* pEpollThread = (EpollThread*)arg;

    if (pEpollThread)
    {
        pEpollThread->_main_loop();
    }

    return NULL;
}

bool EpollThread::_main_loop()
{
    LOG_ERROR("EpollThread _main_loop");

    while (true)
    {
        static uint32 a = 0;
        if (a%500 == 0)
        {
            LOG_DEBUG("EpollThread _main_loop %d", a/500);
        }

        if (!_process_epoll())
        {
            return false;
        }

        a += 1;

        _process_event();
    }    

    return true;
}

bool EpollThread::_process_epoll()
{
    if (!IsRun())
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
            int32 acceptfd = accept(pEpollData->fd, (struct sockaddr *)&remoteAddr, &structLen);
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

bool EpollThread::_process_event()
{
    CtrlEvent event;
    if(!NetworkManager::getInstance().PopEvent(event))
    {
        return false;
    }

    LOG_DEBUG("EpollThread::_process_event type:%d", event.type);
    LOG_DEBUG("EpollThread::_process_event sockfd:%d", event.socketfd);
    
    switch(event.type)
    {
        case CtrlEvent::CtrlEventType_AddListen:
        {
            EpollData* pEpolldata = new EpollData();
            pEpolldata->type = EpollType_listen;

            struct epoll_event ev;
            ev.data.ptr = pEpolldata;
            ev.events = EPOLLIN;

            epoll_ctl(_epollfd, EPOLL_CTL_ADD, event.socketfd, &ev);
        }
        break;
        default:
        break;
    }

    return true;
}

/*
bool EpollThread::OnEvent(int32 listenfd)
{
    
}
*/

bool EpollThread::IsRun()
{
    return _isRun;
}
