#include <stdio.h>
#include "configmanager.h"

SINGLETON_DEFINITION(ConfigManager)

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::LoadConfig(std::string path)
{
	printf("ConfigManager::LoadConfig:%s", path.c_str());
}
