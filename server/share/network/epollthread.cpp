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
    printf("EpollThread Init\n");

    _pService = pService;

    return true;
}

bool EpollThread::Start()
{
    printf("EpollThread Start\n");

    if (0 != pthread_create(&_thread_id, NULL, (void *(*)(void *))(_thread_func_static), this))
	{
        printf("pthread_create error\n");
		return false;
	}
    
    return true;
}

void* EpollThread::_thread_func_static(void* arg)
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
    printf("EpollThread _main_loop\n");

    while (true)
    {
        static uint32 a = 0;
        if (a%500 == 0)
        {
            printf("EpollThread _main_loop %d\n", a/500);
        }

        if (!_pService->Process_epoll())
        {
            return false;
        }

        a += 1;
    }    

    return true;
}
