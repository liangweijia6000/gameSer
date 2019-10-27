package main

import (
	"github.com/larspensjo/config"
	"strconv"
	"log"
)

const path  = "./server.conf"
var configMap = make(map[string]string)

func LoadConfig(id int) bool{
	log.Println("LoadConfig")

	cfg, err := config.ReadDefault(path)
	if err != nil {
		return false
		log.Fatalf("LoadConf readdefault error %v,%v", path, err)
	}

	if cfg.HasSection("agent"+strconv.Itoa(id)) {
		option, err := cfg.SectionOptions("agent"+strconv.Itoa(id))
		if err == nil {
			for _, v := range option {
				optionValue, err := cfg.String("agent"+strconv.Itoa(id), v)
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
