
echo "-- Clean"
rm ./cpp/* -rf
rm ./go/* -rf

echo "-- Create for cpp"
for file in ./protobuf/*
do
	echo -e "-- Processing $file ... \c"
	protoc -I=./protobuf/ --cpp_out=./cpp/ $file
	echo Done
done


#protoc -I=./protobuf/ --cpp_out=./cpp/ ./protobuf/*.proto

echo "-- Create for golang"
for file in ./protobuf/*.proto
do
	echo -e "-- Processing $file ... \c"
	filename=${file##*/}
	path=${filename%.*}
	mkdir ./go/$path
	protoc -I=./protobuf/ --go_out=./go/$path $file
	echo Done
done

echo "-- Copy to agent workspace ..."
cp ./go/* ../../agent/protocol/ -rf

echo "-- All done"
