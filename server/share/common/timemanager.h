#ifndef _TIME_MANAGER_H_
#define _TIME_MANAGER_H_

#include "servercommon.h"

#include <stdio.h>
#include <time.h>

class TimeManager
{
public:
    static uint32 TimeStamp()
    {
        return ::time(NULL);
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
