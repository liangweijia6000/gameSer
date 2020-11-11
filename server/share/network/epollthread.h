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
	bool Init();
	bool Start();
	bool Attach(Service* pService);
private:
	bool _main_loop();
};

#endif //_EPOLL_THREAD_H_
