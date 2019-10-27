#include <stdio.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "tools/cpp/init.pb.h"

int main()
{
	printf("game server running!\n");

	//ServerVar& serverVar = ServerVar::getInstance();
	//
	ConfigManager& configManager = ConfigManager::getInstance();
	ServerVar& serverVar = ServerVar::getInstance();
	InitMsg msg;
	msg.set_times(1);
	
	return 0;
}

