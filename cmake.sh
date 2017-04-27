#!/bin/bash
mkdir -p build #create build folder if not exsists
cd build #change workspace to the build folder
rm -rf * #Remove content of build folder

cmake .. #run Cmake
make #Build the application
cpack -G DEB #Create .deb package
