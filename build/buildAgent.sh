startTime=$(date +%s%N)

unameres=`uname`

if [[ $unameres = "Linux" ]];then
	echo "run on linux"
	targetSer="agent.bin"
else
	targetSer="agent.exe"
fi


if [ -e ../bin/agnet/$targetSer ]; then
    rm $targetSer
fi

cd ../server/agent

echo "Building..."

go build -o ../../bin/agent/$targetSer -v | tee ../../build/agentBuild.log

cd ../../bin

endTime=$(date +%s%N)
costTime=$(($(($endTime-$startTime))/1000000))

if [ -e ./agent/$targetSer ]; then
	echo -e "\033[32m\033[1m"Build Complete"\033[0m"
    echo "takes $costTime ms"
else
    echo "Build Error!"
	echo "ERROR!!"
fi

