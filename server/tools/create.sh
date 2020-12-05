
echo "-- Clean"
rm ./cpp/* -rf
rm ./go/* -rf
rm ../agent/protocol/* -rf
rm ../share/protocol/* -rf

if [ ! -d "./cpp" ]; then
	mkdir ./cpp
fi

if [ ! -d "./cpp/protocol" ]; then
	mkdir ./cpp/protocol
fi

if [ ! -d "./cpp/msghandle" ]; then
	mkdir ./cpp/msghandle
fi

if [ ! -d "./go" ]; then
	mkdir ./go
fi

if [ ! -d "../share/protocol" ]; then
	mkdir ../share/protocol
fi

if [ ! -d "../agent/protocol" ]; then
	mkdir ../agent/protocol
fi

echo "-- Create for cpp"
for file in ./protobuf/*
do
	echo -e "-- Processing $file ... \c"
	protoc -I=./protobuf/ --cpp_out=./cpp/protocol/ $file
	echo -e "\033[32m\033[1mDone\033[0m"
done

echo -e "-- Create protocol.pb.h & msghandle.h .\c"

touch ./protocol.pb.h
touch ./gameMsgHandle.h
touch ./centerMsgHandle.h

touch temp.game.include
touch temp.center.include
touch temp.enum.include

touch temp.msgHandle.game.include
touch temp.msgHandle.center.include

echo "enum MsgType" >> temp.enum.include
echo "{" >> temp.enum.include

echo "static struct MsgInfo gameMsgInfo[] = {" >> temp.game.include
echo "static struct MsgInfo CenterMsgInfo[] = {" >> temp.center.include

for file in ./protobuf/*_protocol.*
do
	while read line
	do
		message=${line% *}
		if [ "$message" = "message" ]; then
			messagename=${line##* }
			targetsername=${line##*2}

			#for GameServer
			if [ "$targetsername" == "G" ]; then
				echo "	{E"$messagename", new MessageSer<"$messagename"Handle, "$messagename">}," >> temp.game.include

				#for handle
				echo "class" $messagename"Handle" >> temp.msgHandle.game.include
				echo "{" >> temp.msgHandle.game.include
				echo "public:" >> temp.msgHandle.game.include
				echo "	"$messagename"Handle();" >> temp.msgHandle.game.include
				echo "	~"$messagename"Handle();" >> temp.msgHandle.game.include
				echo "public:" >> temp.msgHandle.game.include
				echo "	void OnMessage("$messagename" msg);" >> temp.msgHandle.game.include
				echo "};" >> temp.msgHandle.game.include
				echo "" >> temp.msgHandle.game.include
			fi

			#for centerServer
			if [ "$targetsername" == "M" ]; then
				echo "	{E"$messagename", new MessageSer<"$messagename"Handle, "$messagename">}," >> temp.center.include

				#for handle
				echo "class" $messagename"Handle" >> temp.msgHandle.center.include
				echo "{" >> temp.msgHandle.center.include
				echo "public:" >> temp.msgHandle.center.include
				echo "	"$messagename"Handle();" >> temp.msgHandle.center.include
				echo "	~"$messagename"Handle();" >> temp.msgHandle.center.include
				echo "public:" >> temp.msgHandle.center.include
				echo "	void OnMessage("$messagename" msg);" >> temp.msgHandle.center.include
				echo "};" >> temp.msgHandle.center.include
				echo "" >> temp.msgHandle.center.include
			fi						
		fi
	done < $file
done

python ./tool.py CreateEnum

if [ ! $? == 0 ]; then
	echo -e "\033[31m\033[1mNG! Proccess Stop\033[0m"
	exit 1
else
	cat temp.enum >> temp.enum.include
fi

echo "};" >> temp.enum.include
echo "" >> temp.enum.include
echo "};" >> temp.game.include
echo "" >> temp.game.include
echo "};" >> temp.center.include
echo "" >> temp.center.include

cat ./protocol_include/protocol.head.include >> ./protocol.pb.h

for file in ./cpp/protocol/*
do
	filename=${file##*/}
	extname=${filename##*.}
	if [ "$extname" = "h" ];then
		echo "#include \"protocol/$filename\"" >> ./protocol.pb.h
	fi
done

cat ./protocol_include/protocol.body.include >> ./protocol.pb.h
cat ./temp.enum.include >> ./protocol.pb.h
cat ./protocol_include/protocol.foot.include >> ./protocol.pb.h

cat ./protocol_include/handle.head.include >> ./gameMsgHandle.h
cat ./protocol_include/handle.head.include >> ./centerMsgHandle.h
cat ./temp.msgHandle.game.include >> ./gameMsgHandle.h
cat ./temp.msgHandle.center.include >> ./centerMsgHandle.h
cat ./temp.game.include >> ./gameMsgHandle.h
cat ./temp.center.include >> ./centerMsgHandle.h
cat ./protocol_include/handle.foot.include >> ./gameMsgHandle.h
cat ./protocol_include/handle.foot.include >> ./centerMsgHandle.h

rm ./temp.*

mv ./protocol.pb.h ./cpp/protocol/
mv ./gameMsgHandle.h ./cpp/msghandle/
mv ./centerMsgHandle.h ./cpp/msghandle/

echo -e "\033[32m\033[1m Done\033[0m"

echo -e "\033[32m\033[1m""-- Copy to server common workspace ...\033[0m \c"
cp ./cpp/protocol/* ../share/protocol/ -rf
cp ./cpp/msghandle/gameMsgHandle.h ../game/msghandle/msghandle.h
cp ./cpp/msghandle/centerMsgHandle.h ../center/msghandle/msghandle.h
echo -e "\033[32m\033[1mDone\033[0m"

echo "-- Create for golang"
for file in ./protobuf/*.proto
do
	echo -e "-- Processing $file ... \c"
	filename=${file##*/}
	path=${filename%.*}
	mkdir ./go/$path
	protoc -I=./protobuf/ --go_out=./go/$path $file
	echo -e "\033[32m\033[1mDone\033[0m"
done

echo -e "\033[32m\033[1m"-- Copy to agent workspace ..."\033[0m \c"
cp ./go/* ../agent/protocol/ -rf
echo -e "\033[32m\033[1mDone\033[0m"


echo -e "\033[32m\033[1m"-- All Done"\033[0m"
