#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>

class vec3d{
  public:
    double x;
    double y;
    double z;

    vec3d& operator=(const vec3d& rhs);

    vec3d& operator+=(const vec3d& rhs);
    vec3d& operator-=(const vec3d& rhs);
    vec3d& operator*=(const double& rhs);
    vec3d& operator/=(const double& rhs);

    const vec3d operator+(const vec3d& rhs) const;
    const vec3d operator-(const vec3d& rhs) const;
    const vec3d operator*(const double& rhs) const;
    const vec3d operator/(const double& rhs) const;

    double length() const;
    double lengthSqr() const;
    vec3d  normalized() const;

    vec3d();
    vec3d(double x, double y, double z);
    void   set(double x, double y, double z);

};

inline vec3d& vec3d::operator=(const vec3d& rhs){
  x=rhs.x;
  y=rhs.y;
  z=rhs.z;
  return *this;
}

inline vec3d& vec3d::operator+=(const vec3d& rhs){
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  return *this;
}

inline vec3d& vec3d::operator-=(const vec3d& rhs){
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  return *this;
}

inline vec3d& vec3d::operator*=(const double& rhs){
  x*=rhs;
  y*=rhs;
  z*=rhs;
  return *this;
}

inline vec3d& vec3d::operator/=(const double& rhs){
  x/=rhs;
  y/=rhs;
  z/=rhs;
  return *this;
}

inline const vec3d vec3d::operator+(const vec3d& rhs) const {
  return (vec3d(*this) += rhs);
}

inline const vec3d vec3d::operator-(const vec3d& rhs) const {
  return (vec3d(*this) -= rhs);
}

inline const vec3d vec3d::operator*(const double& rhs) const {
  return (vec3d(*this) *= rhs);
}

inline const vec3d vec3d::operator/(const double& rhs) const {
  return (vec3d(*this) /= rhs);
}

inline double vec3d::length() const {
  return sqrt(lengthSqr());
}

inline double vec3d::lengthSqr() const {
  return x*x+y*y+z*z;
}
#endif
