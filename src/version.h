#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "12";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.02";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 21;
	static const long BUILD = 2135;
	static const long REVISION = 1769;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 3484;
	#define RC_FILEVERSION 0,21,2135,1769
	#define RC_FILEVERSION_STRING "0, 21, 2135, 1769\0"
	static const char FULLVERSION_STRING[] = "0.21.2135.1769";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 35;
	

}
#endif //VERSION_H
