echo "-- clean"
if [ -f "./MakeFile" ];then
	make clean
fi
rm CMakeCache.txt -rf
rm CMakeFiles -rf
rm cmake_install.cmake -rf
rm Makefile -rf
echo "-- start to cmake .. "
cmake ..
