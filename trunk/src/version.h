#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "27";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.01";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 18;
	static const long BUILD = 1851;
	static const long REVISION = 166;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 3099;
	#define RC_FILEVERSION 0,18,1851,166
	#define RC_FILEVERSION_STRING "0, 18, 1851, 166\0"
	static const char FULLVERSION_STRING[] = "0.18.1851.166";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 51;
	

}
#endif //VERSION_H
