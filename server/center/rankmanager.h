#ifndef _RANK_MANAGER_H_
#define _RANK_MANAGER_H_

#include "common/servercommon.h"


enum RankSortType {
    RankSortType_Desc = 1,
    RankSortType_Asc,
};

//TODO: 要不要搞个UserManager,保存所有向排行榜更新过的用户的信息
struct UserRankInfo
{
    uint64 uid;
    uint64 value1;
    RankSortType valueSortType1;
    uint64 value2;
    RankSortType valueSortType2;
    uint64 value3;
    RankSortType valueSortType3;
};

class Rank
{
public:
    Rank();
    ~Rank();
public:
    void Update(UserRankInfo& userInfo);
private:
    std::vector<UserRankInfo> rankVec;
    std::map<uint64, uint64> rankIndexMap;
};

class RankManager
{
public:
    RankManager();
    ~RankManager();
private:
};


#endif //_RANK_MANAGER_H_