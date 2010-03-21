#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <cstring>
#include <string>
#include <cstdarg>
typedef std::string SStr;
/*typedef std::wstring WStr;

WStr swprintf(const wchar_t* format, ...);
WStr vswprintf(const wchar_t* format, va_list args);
WStr swprintf(const WStr& format, ...);
WStr vswprintf(const WStr& format, va_list args);*/

SStr sprintf(const char* format, ...);
SStr vsprintf(const char* format, va_list args);
SStr sprintf(const SStr& format, ...);
SStr vsprintf(const SStr& format, va_list args);

#endif
