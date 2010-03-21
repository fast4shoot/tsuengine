#include "stringUtils.h"

/*WStr swprintf(const wchar_t* format, ...){
 va_list args;
 va_start(args, format);
 WStr result = vswprintf(format, args);
 va_end(args);
 return result;
}

WStr vswprintf(const wchar_t* format, va_list args){
 const int bufferSize = 16384;
 wchar_t buffer[bufferSize];
 vswprintf(buffer, bufferSize, format, args);
 return WStr(buffer);
}

WStr swprintf(const WStr& format, ...){
 va_list args;
 va_start(args, format);
 WStr result = vswprintf(format, args);
 va_end(args);
 return result;
}

WStr vswprintf(const WStr& format, va_list args){
 return vswprintf(format.c_str(), args);
}*/

SStr sprintf(const char* format, ...){
 va_list args;
 va_start(args, format);
 SStr result = vsprintf(format, args);
 va_end(args);
 return result;
}

SStr vsprintf(const char* format, va_list args){
 const int bufferSize = 16384;
 char buffer[bufferSize];
 vsnprintf(buffer, bufferSize, format, args);
 return SStr(buffer);
}

SStr sprintf(const SStr& format, ...){
 va_list args;
 va_start(args, format);
 SStr result = vsprintf(format, args);
 va_end(args);
 return result;
}

SStr vsprintf(const SStr& format, va_list args){
 return vsprintf(format.c_str(), args);
}

