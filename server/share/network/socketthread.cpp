#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "socketthread.h"
#include "networkmanager.h"
#include "protocol/protocol.pb.h"
#include "listener.h"

#include "nw_socketmanager.h"


SINGLETON_DEFINITION(SocketThread)

SocketThread::SocketThread()
{
}

SocketThread::~SocketThread()
{
}

bool SocketThread::Init()
{
       return true;
}

bool SocketThread::Start()
{
    LOG_DEBUG("SocketThread Start");

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

void* SocketThread::_thread_func_static(void* arg)   //static
{
    SocketThread* pSocketThread = (SocketThread*)arg;

    if (pSocketThread)
    {
        pSocketThread->_main_loop();
    }

    return nullptr;
}

bool SocketThread::_main_loop()
{
    LOG_DEBUG("SocketThread _main_loop");

    while (true)
    {
        if (!_process_socket())
        {
            return false;
        }

        _process_event();
    }    

    return true;
}

bool SocketThread::_process_socket()
{
    if (!IsRun())
    {
        return false;
    }

    int32 count = SocketManager::getInstance().wait();
    if(count < 0) {
        return false;
    }

    for (int32 i = 0; i < count; i++)
    {
        uint32 events = 0;
        SocketData* pSocketData = nullptr;
        if(!SocketManager::getInstance().getEvent(i, events, (void**)&pSocketData)) {
            LOG_ERROR("getEvent error");
            return false;
        }

        if (!pSocketData) {
            LOG_ERROR("pSocketData");
            return false;
        }

        if (pSocketData->type == SocketType_listen) {
            Listener* pListener = (Listener*)pSocketData->ptr;
            if(!pListener) {
                LOG_ERROR("_process_epoll !pListener");
                return false;
            }
            Requester* pRequester = pListener->accept();
            if(!pRequester) {
                LOG_ERROR("pListener->accept !pRequester");
                exit(-1);
            }
            continue;
        }
        
        Requester* pRequester = (Requester*)pSocketData->ptr;

        if (events & SOCKET_READ)   //可读
        {
            // char buf[BUFSIZ];
            // memset(buf, 0, BUFSIZ);
            // int32 readSize = 0;//read(pEpollData->fd, buf, BUFSIZ);
            // if (readSize < 0)
            // {
            //     if (errno == ECONNRESET)
            //     {
            //         //close(pEpollData->fd);
            //         events[i].data.ptr = nullptr;
            //         pEpollData->Release();
            //         continue;
            //     }    
            // }else if (readSize == 0)
            // {
            //     //close(pEpollData->fd);
            //     events[i].data.ptr = nullptr;
            //     pEpollData->Release();
            //     continue;
            // }

            // LOG_DEBUG("read buf:%s", buf);

            pRequester->onRecv();
            
        }else if (events & SOCKET_WRITE)    //可写
        {
        }    
    }

    return true;
}


//TODO: 加停止监听,断开连接 等等
bool SocketThread::_process_event()
{
    CtrlEvent event;
    while(NetworkManager::getInstance().PopEvent(event))
    {
        LOG_DEBUG("SocketThread::_process_event type:%d", event.type);

        switch(event.type)
        {
            case CtrlEventType_AddListen:
            {
            //     Listener* pListener = ListenerManager::getInstance().create();
            //     if(!pListener) {
            //         LOG_ERROR("_process_event create Listener error");
            //         exit(-1);
            //     }
            //     AddListenEvent* pEvent = &event.eventInfo.addListenEvent;
            //     struct epoll_event ev;
            //     ev.data.ptr = pListener;
            //     ev.events = EPOLLIN;

            //     //epoll_ctl(_epollfd, EPOLL_CTL_ADD, pEvent->socketfd, &ev);
            }
            break;
            default:
            break;
        }
    }

    return true;
}

bool SocketThread::IsRun()
{
    return _isRun;
}
