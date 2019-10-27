package main

import (
	"./protocol/initmsg"
	"flag"
	"github.com/golang/protobuf/proto"
	"log"
	"strconv"
)

var id int

func init() {
	flag.IntVar(&id, "id", 1, "LineId(uniqueness, 1 or 2)")
}

func main() {
	flag.Parse()
	//log.Print(id)
	if id != 1 && id != 2 {
		log.Println("Illegal Id")
		return
	}

	log.Println("Agent" + strconv.Itoa(id) + " start")

	if !LoadConfig(id) {
		log.Println("LoadConfig error")
		return
	}

	ip := getConfig("ip")
	port := getConfig("port")

	if ip == "" {
		log.Println("error ip == \"\"")
		return
	}

	if port == "" {
		log.Println("error port == \"\"")
		return
	}

	log.Println("working on " + ip + ":" + port)

	msg := initmsg.InitMsg{
		Times: proto.Uint32(1),
	}

	log.Println("msg:", msg.GetTimes())

}
