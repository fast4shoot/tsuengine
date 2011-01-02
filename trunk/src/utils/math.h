#include <algorithm>

template <class T>
inline T clamp(const T& val, const T& min, const T& max){
  return std::min(max, std::max(min, val));
}

template <class T>
inline T saw(const T& value, const T& period, const T& amp){
  return (value/period-floor(value/period))*amp;
}
