#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.12";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 14;
	static const long BUILD = 1441;
	static const long REVISION = 7955;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2462;
	#define RC_FILEVERSION 0,14,1441,7955
	#define RC_FILEVERSION_STRING "0, 14, 1441, 7955\0"
	static const char FULLVERSION_STRING[] = "0.14.1441.7955";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 41;
	

}
#endif //VERSION_H
