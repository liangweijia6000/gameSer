#ifndef _TIME_MANAGER_H_
#define _TIME_MANAGER_H_

//#include <stdio.h>
//#include <time.h>
#include <iostream>

#include <chrono>
#include <ctime>

#include "servercommon.h"

class TimeManager
{
public:
    static uint32 TimeStamp()
    {
        return ::time(NULL);
    }

    static uint32 Now()
    {
        return TimeStamp();
    }

    static uint64 NowMilliSecond()
    {
	    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> microClock_type;
        microClock_type tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        return tp.time_since_epoch().count();
    }

    static String TimeStr()
    {
        time_t time = TimeStamp();
        tm* localtm = localtime(&time);
        if (!localtm)
        {
            return String("");
        }else
        {
            char timestr[100];
            snprintf(timestr, 100, "%04d-%02d-%02d %02d:%02d:%02d",
                            localtm->tm_year + 1900,
                            localtm->tm_mon + 1,
                            localtm->tm_mday,
                            localtm->tm_hour,
                            localtm->tm_min,
                            localtm->tm_sec);
            return String(timestr);
        }
    }
};

#endif //_TIME_MANAGER_H_
