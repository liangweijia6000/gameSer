package main

import (
	"log"
	"strconv"

	"github.com/larspensjo/config"
)

const path = "./server.conf"

//ConfigManager base struct for config info
type ConfigManager struct {
	configMap    map[string]string
	gsAddrConfig map[string]string
}

//LoadConfig a func for load config info
func (configMgr *ConfigManager) LoadConfig(id int) bool {
	log.Println("LoadConfig")

	cfg, err := config.ReadDefault(path)
	if err != nil {
		log.Fatalf("LoadConf readdefault error %v,%v", path, err)
	}

	if cfg.HasSection("agent" + strconv.Itoa(id)) {
		option, err := cfg.SectionOptions("agent" + strconv.Itoa(id))
		if err == nil {
			for _, v := range option {
				optionValue, err := cfg.String("agent"+strconv.Itoa(id), v)
				if err == nil {
					configMgr.configMap[v] = optionValue
				}
			}
		}
	} else {
		log.Println("!HasSection(agent)")
		return false
	}
	return true
}

func (configMgr *ConfigManager) getConfig(key string) string {
	return configMgr.configMap[key]
}
