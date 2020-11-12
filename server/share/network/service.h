#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "common/servercommon.h"

struct IpAddr;

class Service
{
public:
    Service(IpAddr ipAddr);
    ~Service();
public:
    static void Process_static();
public:
    bool Start();

    bool Start_epoll();

    void Stop();
    void Reset(IpAddr ipAddr);

    bool Process_epoll();

    void SendMsg(char* msg);
    bool IsRun();
private:
private:
    String _ip;
    uint32 _port;
    int32 _listenSocketfd;
    Int32Vector _socketfdVec;
    bool _isRun;

private:
    int32 _epollfd = 0;
};

#endif  //_SERVICE_H_
