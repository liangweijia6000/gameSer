#ifndef _SOCKET_THREAD_H_
#define _SOCKET_THREAD_H_

#include "common/servercommon.h"

class SocketThread
{
	SINGLETON_DECLARATION(SocketThread)
public:
	SocketThread();
	~SocketThread();
public:
	bool Init();
	bool Start();
	bool IsRun();
	//bool OnEvent(int32 listenfd);
private:
	bool _main_loop();
	bool _process_socket();	//
	bool _process_event();	//add epoll ctl
private:
	static void* _thread_func_static(void* arge);
private:

#ifdef __linux__
	pthread_t _thread_id = 0;
#endif //__linux__
	//ListenService* _pService = nullptr;
	//int32 _epollfd = 0;
	bool _isRun = false;
};

#endif //_SOCKET_THREAD_H_
