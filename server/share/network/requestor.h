#ifndef _REQUESTOR_H_
#define _REQUESTOR_H_

class Requester
{
public:
    Requester();
    ~Requester();
public:
    void onSend();
    void onRecv();
private:
    char* _send_buff;
    char* _recv_buff;
};

class RequesterManager
{
public:
    RequesterManager();
    ~RequesterManager();
};

#endif //_REQUESTOR_H_