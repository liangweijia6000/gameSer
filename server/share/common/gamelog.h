#ifndef _GAME_LOG_H_
#define _GAME_LOG_H_

#include <cstdarg>
#include <iostream> //TODO:

#include "servercommon.h"
#include "timemanager.h"

#define LOG_WARN GameLog::Warn
#define LOG_DEBUG GameLog::Debug
#define LOG_ERROR GameLog::Error
#define LOG_INFO GameLog::Info

enum LogLevel
{
    LogLevel_None = 0,
    LogLevel_Warn = 1,
    LogLevel_Debug = 2,
    LogLevel_Error = 3,
    LogLevel_Info = 4,
    LogLevel_Max = 5,
};

static const char* const LogLevelStr[LogLevel_Max]={
    "NULL",
    "WARN",
    "DEBUG",
    "ERROR",
    "Info",
    };

class GameLog
{
public:
    static void Warn(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        Log(LogLevel_Warn, format, args);
        va_end(args);
    }
    static void Debug(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        Log(LogLevel_Debug, format, args);
        va_end(args);
    }
    static void Error(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        Log(LogLevel_Error, format, args);
        va_end(args);
    }
    static void Info(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        Log(LogLevel_Info, format, args);
        va_end(args);
    }
private:
    static void Log(uint32 level, const char *format, va_list args)
    {
        char szMsg[1024];

        String timeStr = TimeManager::TimeStr();

        int32 Offset = snprintf(szMsg, 1000, "%s [%s]", timeStr.c_str(), LogLevelStr[level]);
        if (Offset < 0)
        {
            return;
        }       

        vsnprintf(szMsg + Offset, sizeof(szMsg) - Offset - 2, format, args);
		//strcat(szMsg, "\n");

        write(level, szMsg);

        return;
    }

    static void write(uint32 level, const char* msg)    //TODO:
    {
        if(level == LogLevel_Warn)
        {
            std::cout<<"\033[32m"<<msg<<"\033[0m"<<std::endl;
        }
        else if (level == LogLevel_Error)
        {
            std::cout<<"\033[31m"<<msg<<"\033[0m"<<std::endl;
        }
        else
        {
            std::cout<<msg<<std::endl;
        }
        
    }
};

#endif //_GAME_LOG_H_

