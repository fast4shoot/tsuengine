#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "24";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.03";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 30;
	static const long BUILD = 3020;
	static const long REVISION = 6593;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 5101;
	#define RC_FILEVERSION 0,30,3020,6593
	#define RC_FILEVERSION_STRING "0, 30, 3020, 6593\0"
	static const char FULLVERSION_STRING[] = "0.30.3020.6593";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 20;
	

}
#endif //VERSION_H
