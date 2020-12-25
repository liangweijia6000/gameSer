#ifndef _EPOLL_THREAD_H_
#define _EPOLL_THREAD_H_

//#include "common/servercommon.h"
#include "commoninclude.h"
//#include "service.h"

struct EpollData
{
    EpollData()
    : type(0)
    , fd(0)
    {}

    void Release()
    {
        delete this;
    }

    uint32 type;
    uint32 fd;
};

enum EpollType
{
    EpollType_listen = 1,
    EpollType_sock = 2,
};

class EpollThread
{
	SINGLETON_DECLARATION(EpollThread)
public:
	EpollThread();
	~EpollThread();
public:
	bool Init();
	bool Start();
	bool IsRun();
	bool OnEvent(int32 listenfd);
private:
	bool _main_loop();
	bool _process_epoll();	//
	bool _process_event();	//add epoll ctl
private:
	static void* _thread_func_static(void* arge);
private:
#ifdef __linux__
	pthread_t _thread_id = 0;
#endif //__linux__
	//ListenService* _pService = NULL;
	int32 _epollfd = 0;
	bool _isRun = false;
};

#endif //_EPOLL_THREAD_H_
