
echo "-- Clean"
rm ./cpp/* -rf
rm ./go/* -rf

echo "-- Create for cpp"
for file in ./protobuf/*
do
	echo -e "-- Processing $file ... \c"
	protoc -I=./protobuf/ --cpp_out=./cpp/ $file
	echo -e "\033[32m\033[1mDone\033[0m"
done

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
