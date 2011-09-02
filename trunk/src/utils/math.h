#ifndef MATH_H
#define MATH_H

#include <algorithm>
#include <cmath>

extern const double PI;

template <class T>
inline T clamp(const T& val, const T& min, const T& max){
  return std::min(max, std::max(min, val));
}

template <class T>
inline T saw(const T& value, const T& period, const T& amp){
  return (value/period-floor(value/period))*amp;
}

template <class T>
inline T toDeg(const T& radians){
  return radians*180/PI;
}

template <class T>
inline T toRad(const T& degrees){
  return degrees*PI/180;
}

#endif
