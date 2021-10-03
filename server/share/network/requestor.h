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
    void onSend();
    void onRecv();
private:

    EpollData _epoll_data;

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