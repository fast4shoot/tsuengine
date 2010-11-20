#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.11";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 12;
	static const long BUILD = 1217;
	static const long REVISION = 6774;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2086;
	#define RC_FILEVERSION 0,12,1217,6774
	#define RC_FILEVERSION_STRING "0, 12, 1217, 6774\0"
	static const char FULLVERSION_STRING[] = "0.12.1217.6774";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 17;
	

}
#endif //VERSION_H
