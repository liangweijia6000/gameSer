#include <stdio.h>
#include "common/servercommon.h"
#include "servervar/servervar.h"
#include "config/configmanager.h"
#include "protocol/protocol.pb.h"

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("main() argc error \n");
		return 0;
	}

	String serverNameStr = "game" + String(argv[1]);

	printf("Server %s running\n", serverNameStr.c_str());

	if (ConfigManager::getInstance().Init())
	{
		printf("ConfigManager::Init error \n");
		return 0;
	}

	const std::map<String, String>* pConfigMap = ConfigManager::getInstance().GetConfigMap(serverNameStr);

	for(auto& it:*pConfigMap)
	{
		printf("game1config %s\n", it.first.c_str());
		printf("game1config %s\n", it.second.c_str());
	}



	ServerVar& serverVar = ServerVar::getInstance();

	InitMsg msg;
	msg.set_times(1);

	//main loop
	//network

	//

	
	return 0;
}

