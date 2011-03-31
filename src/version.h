#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.03";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 32;
	static const long BUILD = 3221;
	static const long REVISION = 7737;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 5526;
	#define RC_FILEVERSION 0,32,3221,7737
	#define RC_FILEVERSION_STRING "0, 32, 3221, 7737\0"
	static const char FULLVERSION_STRING[] = "0.32.3221.7737";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 21;
	

}
#endif //VERSION_H
