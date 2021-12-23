#ifndef _RANK_MANAGER_H_
#define _RANK_MANAGER_H_

#include "common/servercommon.h"

struct RankInfo
{
    int64 uid;
    int64 value1;
    int64 value2;
    int64 value3;
};

//TODO: 要不要搞个UserManager
struct UserInfo
{
    //name
    //avatar
    //pro
    //
};

class Rank
{
public:
    Rank(/* args */);
    ~Rank();
private:
};

class RankManager
{
public:
    RankManager(/* args */);
    ~RankManager();
private:
};


#endif //_RANK_MANAGER_H_