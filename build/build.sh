echo "-- clean"
echo "-- rm CMakeCache.txt"
rm CMakeCache.txt -rf
echo "-- rm CMakeFiles -rf"
rm CMakeFiles -rf
echo "-- rm cmake_install.cmake"
rm cmake_install.cmake -rf
echo "-- rm Makefile"
rm Makefile -rf
echo "-- start to cmake .. "
cmake ..
