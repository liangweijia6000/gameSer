#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

SINGLETON_DECLARATION(ConfigManager)

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();
public:
	GetConfig(string path);
};



































#endif //_CONFIG_MANAGER_H_
