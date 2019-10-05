package main

import (
	"github.com/larspensjo/config"
	"log"
)

const path  = "./server.conf"
var configMap = make(map[string]string)

func LoadConfig() bool{
	log.Println("LoadConfig")

	cfg, err := config.ReadDefault(path)
	if err != nil {
		return false
		log.Fatalf("LoadConf readdefault error %v,%v", path, err)
	}

	if cfg.HasSection("agent") {
		option, err := cfg.SectionOptions("agent")
		if err == nil {
			for _, v := range option {
				optionValue, err := cfg.String("agent", v)
				if err == nil {
					configMap[v] = optionValue
				}
			}
		}
	}else
	{
		log.Println("!HasSection(agent)")
		return false
	}
	return true
}

func getConfig(key string) string {
	return configMap[key]
}
