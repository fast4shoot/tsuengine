#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "13";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.01";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 16;
	static const long BUILD = 1630;
	static const long REVISION = 8988;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2731;
	#define RC_FILEVERSION 0,16,1630,8988
	#define RC_FILEVERSION_STRING "0, 16, 1630, 8988\0"
	static const char FULLVERSION_STRING[] = "0.16.1630.8988";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 30;
	

}
#endif //VERSION_H
