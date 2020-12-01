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
		LOG_ERROR("NetworkManager::Init GetConfigIpAddr error");
		return false;
	}

    LOG_DEBUG("ANetworkManager::start ipAddr.ip:%s", ipAddr.ip.c_str());
    LOG_DEBUG("ANetworkManager::start ipAddr.port:%d", ipAddr.port);    

    return true;
}
