#ifndef JSON_H
#define JSON_H
#include "json_spirit.h"

namespace json{
  using namespace json_spirit;

  template< class T >
  inline void extract(T& result, const mValue& value){
    result = value.get_value<T>();
  }

};
#endif
