package main

import (
	"net"
	"github.com/golang/protobuf/proto"
	initmsg "agent/protocol/initmsg_protocol"
	//"time"
	//"strconv"
	//"log"
)

//gameclient used to connect to the game server

type GameClinet struct {
	ip string
	port string
	conn *net.TCPConn
}

func (s *GameClinet) Start() {
	gsAddr := s.ip + ":" + s.port
	tcpAddr, err := net.ResolveTCPAddr("tcp4", gsAddr)
	checkErr(err)

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	checkErr(err)
	s.conn = conn
}

func (s *GameClinet) Send(msg []byte) {
	if s.conn != nil {
		s.conn.Write(msg)		
	}
}

func (s *GameClinet) Process() {
	s.sendHeartBeatMsg()
}

func (s *GameClinet) sendHeartBeatMsg() {
	msg := &initmsg.InitMsgA2C{
		Times: proto.Uint32(18),
		Name:  proto.String("lwj"),
	}
	sendData, err := proto.Marshal(msg)
	checkErr(err)

	//sendData := "asdf"

	if s.conn != nil {
		s.conn.Write([]byte(sendData))
	}
}



