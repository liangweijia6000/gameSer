
echo "-- Clean"
rm ./cpp/* -rf
rm ./go/* -rf
rm ../agent/protocol/* -rf
rm ../share/protocol/* -rf

if [ ! -d "cpp" ]; then
	mkdir cpp
fi

if [ ! -d "go" ]; then
	mkdir go
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
	protoc -I=./protobuf/ --cpp_out=./cpp/ $file
	echo -e "\033[32m\033[1mDone\033[0m"
done

touch ./protocol.pb.h

for file in ./cpp/*
do
	filename=${file##*/}
	extname=${filename##*.}
	if [ "$extname" = "h" ];then
		echo "#include <protocol/$filename>" >> ./protocol.pb.h
	fi
done

cat ./enum.include >> ./protocol.pb.h

mv ./protocol.pb.h ./cpp/


echo -e "\033[32m\033[1m""-- Copy to server common workspace ...\033[0m"

cp ./cpp/* ../share/protocol/ -rf


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

echo -e "\033[32m\033[1m"-- Copy to agent workspace ..."\033[0m"
cp ./go/* ../agent/protocol/ -rf


echo -e "\033[32m\033[1m"-- All done"\033[0m"
