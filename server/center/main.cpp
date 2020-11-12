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

	if (!ConfigManager::getInstance().Init())
	{
		printf("main ConfigManager Init error \n");
		return 0;
	}

	IpAddr addrInfo;
	if (!ConfigManager::getInstance().GetConfigIpAddr(serverNameStr, addrInfo))
	{
		printf("main GetConfigIpAddr error \n");
		return 0;
	}

	if(!NetworkManager::getInstance().Init(addrInfo))
	{
		printf("main NetworkManager Init error\n");
		return 0;
	}
    
	if (!NetworkManager::getInstance().Start())
	{
		printf("main NetworkManager Start error \n");
		return 0;
	}

	while (1)
	{
		usleep(10000);
		//pService->Process();
		printf("center main thread loop 1\n");
		break;
	}
	
	return 0;
}
