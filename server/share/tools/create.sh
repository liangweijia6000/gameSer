

protoc -I=./protobuf/ --cpp_out=./cpp/ ./protobuf/*.proto 

protoc -I=./protobuf/ --go_out=./go/ ./protobuf/*.proto
