#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "02";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.01";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 15;
	static const long BUILD = 1533;
	static const long REVISION = 8483;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2570;
	#define RC_FILEVERSION 0,15,1533,8483
	#define RC_FILEVERSION_STRING "0, 15, 1533, 8483\0"
	static const char FULLVERSION_STRING[] = "0.15.1533.8483";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 33;
	

}
#endif //VERSION_H
