#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <cstring>
#include <string>
#include <vector>
#include <cstdarg>
#include <cstdio>
#include "typedefs.h"

#include <boost/format.hpp>

using boost::format;

WStr swformat(const wchar_t* format, ...);
WStr vswformat(const wchar_t* format, va_list args);
WStr swformat(const WStr& format, ...);
WStr vswformat(const WStr& format, va_list args);

SStr sformat(const char* format, ...);
SStr vsformat(const char* format, va_list args);
SStr sformat(const SStr& format, ...);
SStr vsformat(const SStr& format, va_list args);

std::vector<String> explode(const String& in, const String& delim);

#endif
