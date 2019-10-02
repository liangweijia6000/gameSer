
if [ -f "./MakeFile" ];then
    make clean
fi
rm CMakeCache.txt CMakeFiles Makefile cmake_install.cmake -rf

rm agentBuild.log -rf

rm ../bin/agent/* -rf
