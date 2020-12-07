#ifndef _MEMORY_PIPE_H_
#define _MEMORY_PIPE_H_

#include "common/servercommon.h"

class MemoryPipe
{
public:
    MemoryPipe();
    ~MemoryPipe();
public:
    bool init(uint32 size);
    bool write(const char* data, uint32 len);
    bool read(char* buff, uint32 len);
private:
    uint32 _size;
    char* _buff;
    char* _head;
    char* _tail;    
};

#endif //_MEMORY_PIPE_H_
