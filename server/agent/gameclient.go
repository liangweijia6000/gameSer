package main

import (
	initmsg "agent/protocol/initmsg_protocol/initMsg"
	"net"

	"github.com/golang/protobuf/proto"
	//"time"
	//"strconv"
	//"log"
)

//GameClinet client info of connection
type GameClinet struct {
	ip   string
	port string
	conn *net.TCPConn
}

//Start the GameClient
func (s *GameClinet) Start() {
	gsAddr := s.ip + ":" + s.port
	tcpAddr, err := net.ResolveTCPAddr("tcp4", gsAddr)
	checkErr(err)

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	checkErr(err)
	s.conn = conn
}

//Send msg
func (s *GameClinet) Send(msg []byte) {
	if s.conn != nil {
		s.conn.Write(msg)
	}
}

//Process GameClient
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
