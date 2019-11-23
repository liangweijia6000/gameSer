#include <stdio.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"

int main()
{
	printf("game server running!\n");

	//ServerVar& serverVar = ServerVar::getInstance();
	//
	ConfigManager& configManager = ConfigManager::getInstance();
	configManager.LoadConfig("config");
	ServerVar& serverVar = ServerVar::getInstance();
	InitMsg msg;
	msg.set_times(1);

	//main loop
	//bind port
	
	//

	
	return 0;
}

