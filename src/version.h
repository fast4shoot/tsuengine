#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "24";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.11";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 13;
	static const long BUILD = 1327;
	static const long REVISION = 7338;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2253;
	#define RC_FILEVERSION 0,13,1327,7338
	#define RC_FILEVERSION_STRING "0, 13, 1327, 7338\0"
	static const char FULLVERSION_STRING[] = "0.13.1327.7338";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 27;
	

}
#endif //VERSION_H
