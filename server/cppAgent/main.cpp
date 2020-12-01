#include <stdio.h>
#include <unistd.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"
//#include "network/networkmanager.h"
#include "anetwork/anetworkmanager.h"

int main(int argc,char *argv[])
{
    if(argc != 2)
	{
		LOG_ERROR("main() argc error");
		return 0;
	}

    String serverNameStr = "agent" + String(argv[1]);

    if (!ConfigManager::getInstance().Init())
	{
		LOG_ERROR("main ConfigManager Init error");
		return 0;
	}
    
	if(!ANetworkManager::getInstance().start(serverNameStr))
    {
		LOG_ERROR("main ANetworkManager start error");
        return 0;
    }  

    return 0;
}
