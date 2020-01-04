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
		printf("main() argc error \n");
		return 0;
	}

    String serverNameStr = "agent" + String(argv[1]);

    if (!ConfigManager::getInstance().Init())
	{
		printf("main ConfigManager Init error \n");
		return 0;
	}
    
	if(ANetworkManager::getInstance().start(serverNameStr))
    {
        return 0;
    }  

    return 0;
}
