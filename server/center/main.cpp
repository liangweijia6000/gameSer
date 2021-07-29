#include <stdio.h>
#include "commoninclude.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"
#include "network/networkmanager.h"

int main()
{
	String serverNameStr = "center";

	LOG_INFO("Server %s running", serverNameStr.c_str());

	if (!ConfigManager::getInstance().Init())
	{
		LOG_ERROR("main ConfigManager Init error");
		return 0;
	}

	IpAddr addrInfo;
	if (!ConfigManager::getInstance().GetConfigIpAddr(serverNameStr, addrInfo))
	{
		LOG_ERROR("main GetConfigIpAddr error");
		return 0;
	}

	if(!NetworkManager::getInstance().Init(addrInfo))
	{
		LOG_ERROR("main NetworkManager Init error");
		return 0;
	}
    
	if (!NetworkManager::getInstance().Start())
	{
		LOG_ERROR("main NetworkManager Start error");
		return 0;
	}

	while (1)
	{
		TimerManager::getInstance().Exec();
	}
	
	return 0;
}
