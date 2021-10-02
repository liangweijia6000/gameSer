#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "nw_define.h"
#include "requestor.h"

class listener
{
public:
    listener();
    ~listener();
public:
    Requester* accept();
private:
    
};


#endif //_LISTENER_H_