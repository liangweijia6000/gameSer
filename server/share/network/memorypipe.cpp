#include "memorypipe.h"

MemoryPipe::MemoryPipe()
{
    //
}

MemoryPipe::~MemoryPipe()
{
    //
}

bool MemoryPipe::init(uint32 size)
{
    _size = size;
    _buff = new char[size];
    _head = _buff;
    _tail = _tail;

    return true;
}

bool MemoryPipe::write(const char* data, uint32 len)
{
    uint32 dist = _tail + _size - _head;
    if (dist > _size)
    {
        dist = dist - _size;
    }

    if (dist < len)
    {
        return false;
    }
    
    
    if (_tail + len > _buff + _size) //
    {
        uint32 len1 = _buff + _size - _tail;
        uint32 len2 = len - len1;
        memcpy(_tail, data, len1);
        memcpy(_buff, data + len1, len2);
        _tail = _buff + len2;
    }else
    {
        memcpy(_tail, data, len);
        _tail = _tail + len;
    }

    return true;   
}

bool MemoryPipe::read(char* buff, uint32 len)
{
    uint32 dist = _tail + _size - _head;
    if (dist > _size)
    {
        dist = dist - _size;
    }

    if (dist < len)
    {
        return false;
    }

    if (_head + len > _buff + _size)
    {
        uint32 len1 = _buff + _size - _head;
        uint32 len2 = len - len1;
        memcpy(buff, _head, len1);
        memcpy(buff+len1, _buff, len2);
        _head = _buff + len2;
    }else
    {
        memcpy(buff, _head, len);
        _head += len;
    }

    return true;
}

