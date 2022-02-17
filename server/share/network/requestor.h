#ifndef _REQUESTOR_H_
#define _REQUESTOR_H_

#include "common/servercommon.h"
#include "nw_define.h"


//每个socket都对应一个Requester？ 不是 requester对应一个event
class Requester
{
public:
    Requester();
    ~Requester();
public:
    void setSocket(int32 socket);
    int32 getSocket(){return _socket;}
    SocketData* getSocketData(){return &_socket_data;}
public:
    void onSend();
    void onRecv();
private:
    SocketData _socket_data;
    int32 _socket;

    char* _send_buff;
    char* _recv_buff;
};

class RequesterManager
{
    SINGLETON_DECLARATION(RequesterManager)
public:
    RequesterManager();
    ~RequesterManager();
public:
    Requester* create();
};

#endif //_REQUESTOR_H_
