#ifndef VEC3D_H
#define VEC3D_H

class vec3d{
  public:
    double x;
    double y;
    double z;
  
    vec3d operator=(vec3d& in);
    vec3d operator+(vec3d& in);
    vec3d operator-(vec3d& in);
    vec3d operator*(double in);
    vec3d operator/(double in);
    
  
    double length();
    double lengthSqr();
    vec3d  normalized();
    
    vec3d();
    vec3d(double x, double y, double z);
    void   set(double x, double y, double z);
  
};

#endif
