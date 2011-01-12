#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "12";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.01";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 16;
	static const long BUILD = 1629;
	static const long REVISION = 8981;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2731;
	#define RC_FILEVERSION 0,16,1629,8981
	#define RC_FILEVERSION_STRING "0, 16, 1629, 8981\0"
	static const char FULLVERSION_STRING[] = "0.16.1629.8981";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 29;
	

}
#endif //VERSION_H
