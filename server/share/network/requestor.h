#ifndef _REQUESTOR_H_
#define _REQUESTOR_H_

#include "common/servercommon.h"
#include "nw_define.h"

class Requester
{
public:
    Requester();
    ~Requester();
public:
    void setfd(int32 fd);
    int32 getfd(){return _sockfd;}
    SocketData* getSocketData(){return &_socket_data;}
public:
    void onSend();
    void onRecv();
private:
    SocketData _socket_data;
    int32 _sockfd;

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