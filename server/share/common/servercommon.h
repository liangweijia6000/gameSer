#ifndef _SERVER_COMMON_H_
#define _SERVER_COMMON_H_


#ifdef _WIN32
typedef char char8;  
typedef unsigned short char16;
typedef float float32;  
typedef double double64;  
typedef unsigned char byte8;  
typedef short int16;  
typedef unsigned short uint16;  
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;  
typedef unsigned long long uint64;
#endif //_WIN32

#ifdef __linux__
#ifdef __amd64 
typedef char char8;  
typedef unsigned short char16;
typedef float float32;  
typedef double double64; 
typedef unsigned char byte8; 
typedef short int16;  
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long int64;
typedef unsigned long uint64;
#else //__amd64
typedef char char8; 
typedef unsigned short char16;
typedef float float32; 
typedef double double64;
typedef unsigned char byte8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64; 
#endif //__amd64
#endif //__linux__


#endif //_SERVER_COMMON_H_
