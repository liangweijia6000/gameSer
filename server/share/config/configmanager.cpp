#include <stdio.h>
#include <fstream>

#include "configmanager.h"

SINGLETON_DEFINITION(ConfigManager)

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::Init()
{
	printf("ConfigManager::Init\n");
	if (!LoadConfig(INI_PATH))
	{
		return false;
	}	
}

const std::map<String, String>* ConfigManager::GetConfigMap(String section)
{
	if(_configMap.find(section) != _configMap.end())
	{
		return &_configMap[section];
	}
	
	return NULL;
}

bool ConfigManager::LoadConfig(String path)
{
	printf("ConfigManager::LoadConfig:%s\n", path.c_str());

	std::ifstream fileStream(path.c_str());

	String readStr;

	std::map<String, String>* pNodeMap;

	while (getline(fileStream, readStr))
	{
		String::size_type pos1 = readStr.find('[');
		String::size_type pos2 = readStr.find(']');

		if (String::npos == pos1 || String::npos == pos2)
		{
			if(!pNodeMap)
			{
				continue;
			}

			String::size_type pos = readStr.find('=');
			if(pos == String::npos)
			{
				continue;
			}

			String keyStr = readStr.substr(0, pos);
			String valueStr = readStr.substr(pos + 1, readStr.size()-1);

			(*pNodeMap)[keyStr] = valueStr;

			continue;
		}

		String strSection = readStr.substr(pos1=1, pos2-1);

		if(_configMap.find(strSection) == _configMap.end())
		{
			std::map<String, String> nodeMap;
			_configMap[strSection] = nodeMap;
		}

		pNodeMap = &_configMap[strSection];
	}
}


