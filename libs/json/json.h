#ifndef JSON_H
#define JSON_H

#include "json_spirit.h"
#include "vecBase.h"

namespace json{
  using namespace json_spirit;

  //void extract(Model& result, const mValue& value);

  inline void extract(bool& result, const mValue& value){
    result = value.get_value<bool>();
  }

  inline void extract(String& result, const mValue& value){
    result = value.get_value<String>();
  }

  inline void extract(int& result, const mValue& value){
    result = value.get_value<int>();
  }

  inline void extract(float& result, const mValue& value){
    result = value.get_value<double>();
  }

  inline void extract(double& result, const mValue& value){
    result = value.get_value<double>();
  }

  template< class T, int N, class Derived >
  void extract(vecBase<T, N, Derived>& result, const mValue& value){
    const json::mArray& arr=value.get_array();
    if(arr.size()<N){
      throw std::runtime_error(sformat("Cannot parse %d-component vector from JSON: too few values",N));
    }
    for(int i = 0; i < N; i++){
      extract(result.data[i], arr[i]);
    }
  }
}


#endif
