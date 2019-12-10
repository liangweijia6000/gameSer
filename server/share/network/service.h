#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "common/servercommon.h"

struct IpAddr;

class Service
{
private:
    /* data */
public:
    Service(IpAddr ipAddr);
    ~Service();
public:
    bool Start();
    void Stop();
    void Reset(IpAddr ipAddr);
    void Process();
    void SendMsg(char* msg);
    bool IsRun();
private:
private:
    String ip;
    uint32 port;
    int32 socketfd;
    Int32Vector socketfdVec;
    bool isRun;
};

#endif  //_SERVICE_H_
