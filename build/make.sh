
startTime=$(date +%s)
stms=$((startTime*1000+`date "+%N"`/1000000))
echo "startTime $stms"

make

endTime=$(date +%s)
etms=$((endTime*1000+`date "+%N"`/1000000))

costTime=$(($etms-stms))

echo "endTime $etms"

echo "takes $costTime ms"
