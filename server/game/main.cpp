#include <stdio.h>
#include <unistd.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"
#include "network/networkmanager.h"
#include "network/epollthread.h"

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		LOG_ERROR("main() argc error");
		return 0;
	}

	String serverNameStr = "game" + String(argv[1]);

	LOG_DEBUG("Server %s running", serverNameStr.c_str());

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
		usleep(10000);
		//Process();
		LOG_DEBUG("main loop 1");
		break;
	}

	return 0;
}

