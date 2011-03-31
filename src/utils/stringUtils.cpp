#include "stringUtils.h"


WStr swformat(const wchar_t* format, ...){
 va_list args;
 va_start(args, format);
 WStr result = vswformat(format, args);
 va_end(args);
 return result;
}

WStr vswformat(const wchar_t* format, va_list args){
 const int bufferSize = 16384;
 wchar_t buffer[bufferSize];
 vswprintf(buffer, /*/bufferSize,*/ format, args);
 return WStr(buffer);
}

WStr swformat(const WStr& format, ...){
 va_list args;
 va_start(args, format);
 WStr result = vswformat(format, args);
 va_end(args);
 return result;
}

WStr vswformat(const WStr& format, va_list args){
 return vswformat(format.c_str(), args);
}

SStr sformat(const char* format, ...){
 va_list args;
 va_start(args, format);
 SStr result = vsformat(format, args);
 va_end(args);
 return result;
}

SStr vsformat(const char* format, va_list args){
 const int bufferSize = 16384;
 char buffer[bufferSize];
 vsnprintf(buffer, bufferSize, format, args);
 return SStr(buffer);
}

SStr sformat(const SStr& format, ...){
 va_list args;
 va_start(args, format);
 SStr result = vsformat(format, args);
 va_end(args);
 return result;
}

SStr vsformat(const SStr& format, va_list args){
 return vsformat(format.c_str(), args);
}

std::vector<String> explode(const String & in, const String & delim){
  typedef String::size_type size_type ;

  const size_type delim_len = delim.length() ;
  std::vector<String> result ;

  size_type i = 0, j ;
  while(1){
    j = in.find(delim, i) ;
    result.push_back(in.substr(i, j-i)) ;
    if (j == std::string::npos){
      break;
    }
    i = j + delim_len ;
  }

  return result ;
}
