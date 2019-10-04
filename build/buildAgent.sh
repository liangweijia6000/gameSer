unameres=`uname`

if [[ $unameres = "Linux" ]];then
	echo "run on linux"
	targetSer="agent.bin"
else
	targetSer="agent.exe"
fi

startTime=$(date +%s)
stms=$((startTime*1000+10#`date "+%N"`/1000000))

if [ -e ../bin/agnet/$targetSer ]; then
    rm $targetSer
fi

cd ../server/agent

echo "Building..."

go build -o ../../bin/agent/$targetSer -v | tee ../../build/agentBuild.log

cd ../../bin

endTime=$(date +%s)
etms=$((endTime*1000+10#`date "+%N"`/1000000))

costTime=$(($etms-stms))

if [ -e ./agent/$targetSer ]; then
    echo "Build Complete"
    echo "takes $costTime ms"
else
    echo "Build Error!"
fi

