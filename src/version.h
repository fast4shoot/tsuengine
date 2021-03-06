#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "13";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 43;
	static const long BUILD = 4375;
	static const long REVISION = 4081;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 8152;
	#define RC_FILEVERSION 0,43,4375,4081
	#define RC_FILEVERSION_STRING "0, 43, 4375, 4081\0"
	static const char FULLVERSION_STRING[] = "0.43.4375.4081";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 75;
	

}
#endif //VERSION_H
