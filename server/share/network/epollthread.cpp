#include "epollthread.h" 

SINGLETON_DEFINITION(EpollThread)

EpollThread::EpollThread()
{
}

EpollThread::~EpollThread()
{
}

bool EpollThread::Init()
{
    printf("EpollThread Init");
    return true;
}

bool EpollThread::Start()
{
    printf("EpollThread Start\n");
    return true;
}

bool EpollThread::Attach(Service* pService)
{
    printf("EpollThread Attack\n");
    return true;
}

bool EpollThread::_main_loop()
{
    printf("EpollThread _main_loop\n");
    return true;
}
