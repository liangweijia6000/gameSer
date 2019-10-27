
startTime=$(date +%s%N)

make -j8

endTime=$(date +%s%N)

costTime=$(($(($endTime-$startTime))/1000000))


echo "takes $costTime ms"
