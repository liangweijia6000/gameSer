#ifndef _MSG_HANDLE_H_
#define _MSG_HANDLE_H_

#include "protocol/protocol.pb.h"
//#include <google/protobuf/message.h>

class MsgHandle
{
public:
    MsgHandle();
    ~MsgHandle();
public:
    //virtual OnMessage(Message* msg) = 0;
    static void InitMsgHandle(InitMsgA2C* msg);
};

#endif //_MSG_HANDLE_H_