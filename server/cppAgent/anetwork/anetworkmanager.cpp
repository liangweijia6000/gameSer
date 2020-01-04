#include "anetworkmanager.h"
#include "config/configmanager.h"

SINGLETON_DEFINITION(ANetworkManager)

ANetworkManager::ANetworkManager()
{
    //
}

ANetworkManager::~ANetworkManager()
{
    //
}

bool ANetworkManager::start(String serverNameStr)
{
    IpAddr ipAddr;
    if (!ConfigManager::getInstance().GetConfigIpAddr(serverNameStr, ipAddr))
	{
		printf("NetworkManager::Init GetConfigIpAddr error \n");
		return false;
	}

    printf("ANetworkManager::start ipAddr.ip:%s\n", ipAddr.ip.c_str());
    printf("ANetworkManager::start ipAddr.port:%d\n", ipAddr.port);


    

    return true;
}
