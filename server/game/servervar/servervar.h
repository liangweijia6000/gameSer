#ifndef _SERVERVAR_H_
#define _SERVERVAR_H_

#include <common/servercommon.h>

class ServerVar
{
	SINGLETON_DECLARATION(ServerVar);
public:
	ServerVar(){}
	~ServerVar(){}
public:
	void printAllVar();
};




















#endif //_SERVERVAR_H_

