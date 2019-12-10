package main

import (	
	"flag"	
	"log"
	"strconv"
	"os"
	"time"
)

var id int

func init() {
	flag.IntVar(&id, "id", 1, "LineId(uniqueness, 1 or 2)")
}

func main() {
	flag.Parse()
	if id != 1 && id != 2 {
		log.Println("Illegal Id")
		return
	}

	log.Println("Agent" + strconv.Itoa(id) + " start")

	configManager := ConfigManager{
		configMap : make(map[string]string),
		gsAddrConfig : make(map[string]string),
	}

	if !configManager.LoadConfig(id) {
		log.Println("LoadConfig error")
		return
	}

	ip := configManager.getConfig("ip")
	port := configManager.getConfig("port")

	if ip == "" {
		log.Println("error ip == \"\"")
		return
	}

	if port == "" {
		log.Println("error port == \"\"")
		return
	}

	log.Println("working on " + ip + ":" + port)

	gameClient := GameClinet {
		ip : "127.0.0.1",
		port : "15001",
	}

	gameClient.Start();

	for {
		time.Sleep(1000000000)
		gameClient.Process()
	}

	//msg := initmsg.InitMsg{
	//	Times: proto.Uint32(1),
	//}

	//log.Println("msg.times", msg.GetTimes())
}

func checkErr(err error) {
	if err != nil {
		log.Println(err.Error())
		os.Exit(1)
	}
}
