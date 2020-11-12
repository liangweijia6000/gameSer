#ifndef _EPOLL_THREAD_H_
#define _EPOLL_THREAD_H_

#include "common/servercommon.h"
#include "service.h"

class EpollThread
{
	SINGLETON_DECLARATION(EpollThread)
public:
	EpollThread();
	~EpollThread();
public:
	bool Init(Service* pService);
	bool Start();
private:
	bool _main_loop();
private:
	static void* _thread_func_static(void* arge);
private:
	pthread_t _thread_id = 0;
	Service* _pService = NULL;
};

#endif //_EPOLL_THREAD_H_
