echo "-- Clean all"

if [ -f "./Makefile" ];then
    make clean
fi
rm CMakeCache.txt CMakeFiles Makefile cmake_install.cmake -rf

rm agentBuild.log -rf

rm ../bin/agent/*.bin -rf
rm ../bin/agent/*.exe -rf
rm ../bin/game/*.bin -rf
rm ../bin/game/*.exe -rf
rm ../bin/center/*.bin -rf
rm ../bin/center/*.exe -rf
