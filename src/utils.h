#ifndef UTILS_H
#define UTILS_H

#include <cmath>

inline double saw(double value, double period, double amp){
  return (value/period-floor(value/period))*amp;
}

#endif
