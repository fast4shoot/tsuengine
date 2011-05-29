#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.05";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 35;
	static const long BUILD = 3563;
	static const long REVISION = 9578;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 6245;
	#define RC_FILEVERSION 0,35,3563,9578
	#define RC_FILEVERSION_STRING "0, 35, 3563, 9578\0"
	static const char FULLVERSION_STRING[] = "0.35.3563.9578";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 63;
	

}
#endif //VERSION_H
