if [ ! -f "./server.conf" ];then
    echo "make ./server"
    cp ./server_bak.conf ./server.conf
fi
echo "copy server.conf to agent"
cp ./server.conf ./agent/server.conf
cp ./server.conf ./cppAgent/server.conf
echo "copy server.conf to game"
cp ./server.conf ./game/server.conf
echo "copy server.conf to center"
cp ./server.conf ./center/server.conf
