#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <common/servercommon.h>
#include <string>

class ConfigManager
{
	SINGLETON_DECLARATION(ConfigManager)
public:
	ConfigManager();
	~ConfigManager();
public:
	void LoadConfig(std::string path);
};



































#endif //_CONFIG_MANAGER_H_
