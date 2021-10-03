#include <stdio.h>
#include <fstream>

#include "commoninclude.h"
#include "configmanager.h"
#include "network/networkmanager.h"

SINGLETON_DEFINITION(ConfigManager)

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::Init()
{
	LOG_DEBUG("ConfigManager::Init");
	if (!LoadConfig(INI_PATH))
	{
		return false;
	}
	return true;
}

const std::map<String, String>* ConfigManager::GetConfigMap(String section)
{
	if(_configMap.find(section) != _configMap.end())
	{
		return &_configMap[section];
	}
	
	return nullptr;
}

bool ConfigManager::GetConfigIpAddr(String section, IpAddr &ipAddr)
{
	if (_configMap.find(section) == _configMap.end())
	{
		return false;
	}

	std::map<String, String>& secConfigMap = _configMap[section];

	auto ipIter = secConfigMap.find("ip");
	if (ipIter == secConfigMap.end())
	{
		return false;
	}else
	{
		ipAddr.ip = ipIter->second;
	}

	auto portIter = secConfigMap.find("port");
	if (portIter == secConfigMap.end())
	{
		return false;
	}else
	{
		ipAddr.port = atoi(portIter->second.c_str());
	}

	return true;
}

bool ConfigManager::LoadConfig(String path)
{
	LOG_DEBUG("ConfigManager::LoadConfig");

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
	return true;
}


