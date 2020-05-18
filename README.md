# opencpn.rtz.assist
Translation tool to convert OpenCPN GPX to/from RTZ format files

Compiling

*Windows*

Needed to reference the 'xerces-c_3.lib' file. Also the 'include' files. Built my own xerces and used that compilation for this. VS2017 was the IDE.

*Linux*

Removed xerces and built my own 3.2.3 version. CMake found the xerces library file and the includes. An executable file 'RTZassist' is created in the 'build' folder. This can be 
run with 'Terminal' ('./RTZassist') Unable to build a package at the moment. Extra files are needed for the schema and also the samples. These are found in 'RTZassist.windows.zip' in the release.

Code::Blocks was also used and with this it was possible to compile and run the 'RTZassist' file. Need to set 'Properties' for the build to make an executable, not the console application.

*MacOSX*

Install 'xerces-c'. 
'Homebrew' was used.
Ref: http://macappstore.org/xerces-c/

1. Press Command+Space and type Terminal and press enter/return key.
2. Run in Terminal app:

ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null
and press enter/return key.

If the screen prompts you to enter a password, please enter your Mac's user password to continue. When you type the password, it won't be displayed on screen, but the system would accept it. So just type your password and press ENTER/RETURN key. Then wait for the command to finish.

3. Run:
brew install xerces-c

Then run the installer pkg - 'RTZassist.pkg'.

