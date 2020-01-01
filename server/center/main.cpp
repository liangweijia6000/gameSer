#include <stdio.h>
#include <unistd.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"
#include "network/networkmanager.h"

int main()
{
	String serverNameStr = "center";

	printf("Server %s running\n", serverNameStr.c_str());

	if (ConfigManager::getInstance().Init())
	{
		printf("main ConfigManager Init error \n");
		return 0;
	}

	if(NetworkManager::getInstance().Init(serverNameStr))
    {
        return 0;
    }
    
	Service* pService = NetworkManager::getInstance().CreateService();
	if (!pService)
	{
		printf("main NetworkManager createService eroor \n");
		return 0;
	}

	if(!pService->Start())
	{
		printf("main service start error\n");
		return 0;
	}

	while (1)
	{
		usleep(10000);
		pService->Process();
	}
	
	return 0;
}
