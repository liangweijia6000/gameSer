package main

import (
	"flag"
	"log"
)

var id int

func init(){
	flag.IntVar(&id,"id",1, "LineId(uniqueness, 1 or 2)")
}

func main(){
	flag.Parse()
	//log.Print(id)
	if(id != 1 && id != 2){
		log.println("Illegal Id")
		return
	}

	log.Println("agent start")

	if (!LoadConfig()){
		log.Println("LoadConfig error")
		return
	}

	ip := getConfig("ip")
	port := getConfig("port")

	log.Println("working on " + ip + ":" + port)

	//
}

