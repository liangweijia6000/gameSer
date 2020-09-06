#include <stdio.h>
#include <unistd.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"
#include "network/networkmanager.h"

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("main() argc error \n");
		return 0;
	}

	String serverNameStr = "game" + String(argv[1]);

	printf("Server %s running\n", serverNameStr.c_str());

	if (!ConfigManager::getInstance().Init())
	{
		printf("main ConfigManager Init error \n");
		return 0;
	}

	if(!NetworkManager::getInstance().Init(serverNameStr))
	{
		return 0;
	}

	Service* pService = NetworkManager::getInstance().CreateService();
	if (!pService)
	{
		printf("main NetworkManager createService eroor \n");
		return 0;
	}

	//ServerVar& serverVar = ServerVar::getInstance();	

	while (1)
	{
		//usleep(10000);
		pService->Process();
	}

	return 0;
}
