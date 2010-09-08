#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.09";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 4;
	static const long BUILD = 419;
	static const long REVISION = 2298;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 753;
	#define RC_FILEVERSION 1,4,419,2298
	#define RC_FILEVERSION_STRING "1, 4, 419, 2298\0"
	static const char FULLVERSION_STRING[] = "1.4.419.2298";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 19;
	

}
#endif //VERSION_H
