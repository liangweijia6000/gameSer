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
#include "listener.h"

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

    return nullptr;
}

bool EpollThread::_main_loop()
{
    LOG_DEBUG("EpollThread _main_loop");

    while (true)
    {
        if (!_process_epoll())
        {
            return false;
        }

        //增加计数?
        /* if count < 1000

            static uint32 a = 0;
            if (a%500 == 0)
            {
                LOG_DEBUG("EpollThread _main_loop %d", a/500);
            }

            a += 1;
        */

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
    
#ifdef __linux__    //TODO:为win下调试写个select(先把win下cmake搞定...)
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

        if (pEpollData == nullptr)
        {
            continue;
        }        

        if (pEpollData->type == EpollType_listen)
        {
            Listener* pListener = (Listener*)pEpollData->ptr;
            if(!pListener) {
                LOG_ERROR("_process_epoll !pListener");
                exit(-1);
            }

            Requester* pRequester = pListener->accept();
            if(!pRequester) {
                LOG_ERROR("pListener->accept !pRequester");
                exit(-1);
            }

            //TODO:

            //struct sockaddr_in remoteAddr;
            //uint32 structLen = sizeof(struct sockaddr);
            //int32 acceptfd = accept(pEpollData->fd, (struct sockaddr *)&remoteAddr, &structLen);
            //if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            //{
                //
            //}else
            // {
            //     EpollData* pEpolldata = new EpollData();
            //     pEpolldata->type = EpollType_sock;
            //     pEpollData->fd = acceptfd;

            //     struct epoll_event ev;
            //     ev.data.ptr = pEpolldata;
            //     ev.events = EPOLLIN | EPOLLOUT; //默认水平触发

            //     epoll_ctl(_epollfd, EPOLL_CTL_ADD, acceptfd, &ev);
            // }
            continue;
        }
        
        if (events[i].events & EPOLLIN) //可读  //TODO:读写均通过对应的requestor
        {
            char buf[BUFSIZ];
            memset(buf, 0, BUFSIZ);
            int32 readSize = 0;//read(pEpollData->fd, buf, BUFSIZ);
            if (readSize < 0)
            {
                if (errno == ECONNRESET)
                {
                    //close(pEpollData->fd);
                    events[i].data.ptr = nullptr;
                    pEpollData->Release();
                    continue;
                }    
            }else if (readSize == 0)
            {
                //close(pEpollData->fd);
                events[i].data.ptr = nullptr;
                pEpollData->Release();
                continue;
            }

            LOG_DEBUG("read buf:%s", buf);
            
        }else if (events[i].events & EPOLLOUT)
        {
            //TODO:可写，数据怎么拿过来？怎么区分不同连接对象(server或client)
        }    
    }
#endif //__linux__

    return true;
}


//TODO: 加停止监听,断开连接 等等
bool EpollThread::_process_event()
{
    CtrlEvent event;
    while(NetworkManager::getInstance().PopEvent(event))
    {
        LOG_DEBUG("EpollThread::_process_event type:%d", event.type);

        switch(event.type)
        {
            case CtrlEventType_AddListen:
            {
                Listener* pListener = ListenerManager::getInstance().create();
                if(!pListener) {
                    LOG_ERROR("_process_event create Listener error");
                    exit(-1);
                }
                AddListenEvent* pEvent = &event.eventInfo.addListenEvent;
                struct epoll_event ev;
                ev.data.ptr = pListener;
                ev.events = EPOLLIN;

                epoll_ctl(_epollfd, EPOLL_CTL_ADD, pEvent->socketfd, &ev);                
            }
            break;
            default:
            break;
        }
    }

    return true;
}

bool EpollThread::IsRun()
{
    return _isRun;
}
