#ifndef VEC3D_H
#define VEC3D_H

#include "vecOpBase.h"
#include <btBulletDynamicsCommon.h>

class vec3d: public vecOpBase<double,3,vec3d>{
  public:
    double& x;
    double& y;
    double& z;

    vec3d& operator=(const vec3d& rhs);

    vec3d(const btVector3& rhs);
    vec3d(const vec3d& rhs);
    vec3d(double x=0., double y=0., double z=0.);
    void   set(double x, double y, double z);

    vec3d cross(const vec3d& val) const;

    operator btVector3();

};

inline vec3d::vec3d(double x, double y, double z):
  x(data[0]),
  y(data[1]),
  z(data[2])
{
  data[0]=x;
  data[1]=y;
  data[2]=z;
}

inline vec3d::vec3d(const vec3d& rhs):
  x(data[0]),
  y(data[1]),
  z(data[2]),
  vecOpBase<double,3,vec3d>(rhs)
{}

inline vec3d::vec3d(const btVector3& rhs):
  x(data[0]),
  y(data[1]),
  z(data[2])
{
  data[0] = rhs.x();
  data[1] = rhs.y();
  data[2] = rhs.z();
}


inline void vec3d::set(double x, double y, double z){
  data[0]=x;
  data[1]=y;
  data[2]=z;
}

inline vec3d& vec3d::operator=(const vec3d& rhs){
  return vecBase<double,3,vec3d>::operator=(rhs);
}

inline vec3d vec3d::cross(const vec3d& val) const{
  return vec3d(y*val.z - z*val.y, z*val.x - x*val.z, x*val.y - y*val.x);
}

inline vec3d::operator btVector3(){
  return btVector3(x, y, z);
}


#endif
