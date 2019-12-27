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

	IpAddr ipaddr;
	if (!ConfigManager::getInstance().GetConfigIpAddr(serverNameStr, ipaddr))
	{
		printf("main ConfigManager GetConfigIpAddr error \n");
		return 0;
	}	

	NetworkManager& rNWMgr = NetworkManager::getInstance();
	rNWMgr.Init();
	Service* pService = rNWMgr.CreateService(ipaddr);
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
		
	//ServerVar& serverVar = ServerVar::getInstance();	

	while (1)
	{
		usleep(10000);
		pService->Process();
	}
	
	return 0;
}

