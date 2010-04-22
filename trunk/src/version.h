#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.04;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 1;
	static const long BUILD = 198;
	static const long REVISION = 1105;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 352;
	#define RC_FILEVERSION 1,1,198,1105
	#define RC_FILEVERSION_STRING "1, 1, 198, 1105\0"
	static const char FULLVERSION_STRING[] = "1.1.198.1105";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 98;
	

}
#endif //VERSION_h
