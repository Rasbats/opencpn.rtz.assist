# opencpn.rtz.assist
Translation tool to convert OpenCPN GPX to/from RTZ format files

Compiling

*Windows*

Needed to reference the 'xerces-c_3.lib' file. Also the 'include' files. Built my own xerces and used that compilation for this. VS2017 was the IDE.

*Linux*

Removed xerces and built my own 3.2.3 version. CMake found the xerces library file and the includes. An executable file 'RTZassist' is created in the 'build' folder. This can be 
run with 'Terminal' ('./RTZassist') Unable to build a package at the moment. Extra files are needed for the schema and also the samples. These are found in 'RTZassist.windows.zip' in the release.

Code::Blocks was also used and with this it was possible to compile and run the 'RTZassist' file. Need to set 'Properties' for the build to make an executable, not the console application.
