#ifndef _SERVER_COMMON_H_
#define _SERVER_COMMON_H_

#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>

#include <cstring>

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

typedef std::string String;
typedef std::vector<String> StringVector;  
typedef std::list<String> StringList; 
typedef std::map<String,String> StringMap; 
typedef std::map<String,int32> StringIntMap; 
typedef std::map<String,int64> StringInt64Map; 
typedef std::map<String,int64> StringIdMap; 
typedef std::map<String, float32>StringFloatMap;

typedef std::vector<int32> Int32Vector;  
typedef std::vector<float32> Float32Vector;
typedef std::vector<int32> IntVector;  
typedef std::list<int32> Int32List;   
typedef std::list<int32> IntList;  
typedef std::list<int64> Int64List;
typedef std::list<int64> IdList;
typedef std::vector<int64> Int64Vector;
typedef std::vector<int64> IdVector;
typedef std::vector<Int32Vector> Int32VectorVector;
typedef std::vector<Int32Vector> IntVectorVector;

typedef std::map<int32,int32> Int32Int32Map;
typedef std::map<int32,int32> IntIntMap;
typedef std::map<int64,int32> Int64Int32Map;
typedef std::map<int64,int32> IdIntMap;
typedef std::map<int32,int64> Int32Int64Map;
typedef std::map<int32,int64> IntIdMap;
typedef std::map<int64,int64> Int64Int64Map;
typedef std::map<int64,int64> IdIdMap;

typedef std::map<int64,String> Int64StringMap;
typedef std::map<int64,String> IdStringMap;
typedef std::map<int32,String> IntStringMap;

typedef std::set<int32> Int32Set;
typedef std::set<int32> IntSet;
typedef std::set<int64> Int64Set;
typedef std::set<int64> IdSet;
typedef std::set<String> StringSet;

typedef std::map<int64,Int32Int32Map> Int64Int32Int32Map;
typedef std::map<int32,Int32Int32Map> Int32Int32Int32Map;
typedef std::map<int32,Int64Int32Map> Int32Int64Int32Map;

typedef std::map<int64,Int32Vector> Int64_Int32VectorMap;
typedef std::map<int32, Int32Vector> Int32VectorMap;
typedef std::vector<byte8> Byte8Vector;
typedef std::vector<int16> Int16Vector;
typedef std::vector<bool> BoolVector;



#define FOR_I_INT(size) for (int_32 i = 0; i < size; i++)
#define FOR_I_UINT(size) for (uint_32 i = 0; i < size; i++)
#define FOR_K_INT(size) for (int_32 k = 0; k < size; k++)
#define FOR_K_UINT(size) for (uint_32 k = 0; k < size; k++)



#define SINGLETON_DECLARATION(class_name) \
	public:		static class_name& getInstance();	\
	private:	static class_name* _instance;

#define SINGLETON_DEFINITION(class_name)				\
	class_name* class_name::_instance = NULL;			\
	class_name& class_name::getInstance()				\
	{													\
	if (class_name::_instance == NULL)				\
		{												\
		class_name::_instance = new class_name();	\
		}												\
		return *class_name::_instance;					\
	}




#endif //_SERVER_COMMON_H_

