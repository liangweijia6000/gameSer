#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <common/servercommon.h>

struct IpAddr;
const static String INI_PATH="./server.conf";

class ConfigManager
{
	SINGLETON_DECLARATION(ConfigManager)
public:
	ConfigManager();
	~ConfigManager();
public:
	bool Init();
	const std::map<String, String>* GetConfigMap(String section);
	bool GetConfigIpAddr(String section, IpAddr &ipAddr);
private:
	bool LoadConfig(std::string path);

private:
	std::map<String, std::map<String, String>> _configMap;
};


#endif //_CONFIG_MANAGER_H_
