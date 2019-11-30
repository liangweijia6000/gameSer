#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <common/servercommon.h>
#include <string>


const static String INI_PATH="./server.conf";


struct IniNode
{
	IniNode(String root, String key, String value)
	{
		_root = root;
		_key = key;
		_value = value;
	}
	String _root;
	String _key;
	String _value;
};




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
