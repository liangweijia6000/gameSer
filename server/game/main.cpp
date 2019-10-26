#include <stdio.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"

int main()
{
	printf("game server running!\n");

	//ServerVar& serverVar = ServerVar::getInstance();
	//
	ConfigManager& configManager = ConfigManager::getInstance();
	ServerVar& serverVar = ServerVar::getInstance();
	
	return 0;
}

