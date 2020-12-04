#include "epollthread.h"

SINGLETON_DEFINITION(EpollThread)

EpollThread::EpollThread()
{
}

EpollThread::~EpollThread()
{
}

bool EpollThread::Init(Service* pService)
{
    LOG_DEBUG("EpollThread Init");

    _pService = pService;

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
    
    return true;
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

        if (!_pService->Process_epoll())
        {
            return false;
        }

        a += 1;
    }    

    return true;
}
