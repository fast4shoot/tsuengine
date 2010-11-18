#include <algorithm>

template <class T>
const T& clamp(const T& val, const T& min, const T& max){
  return std::min(max, std::max(min, val));
}

