
startTime=$(date +%s)
stms=$((startTime*1000+`date "+%N"`/1000000))

make -j8

endTime=$(date +%s)
etms=$((endTime*1000+`date "+%N"`/1000000))

costTime=$(($etms-stms))

echo "takes $costTime ms"
