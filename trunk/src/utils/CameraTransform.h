#ifndef CAMERATRANSFORM_H
#define CAMERATRANSFORM_H

#include <LinearMath/btQuaternion.h>
#include "vec3d.h"
//#include "angle.h"

class CWorldEntity;

class CameraTransform{
  public:
    CameraTransform();
    CameraTransform(double timeout);
    void remove();
    bool isActive();
    void setBase(CWorldEntity* base);
    void setPosition(const vec3d& position);
    void setAngle(const btQuaternion& angle);
    void overrideAngle(const btQuaternion& angle);
    btTransform getTransform();
    vec3d getTransformedPosition();
    vec3d getTransformedDirection();
    void doTransform();
  protected:
    CWorldEntity* m_base;
    btQuaternion m_angle;
    bool m_angleOverride;
    vec3d m_position;
    double m_timeout;
    bool m_infinite;
  private:
};

inline void CameraTransform::remove(){
  m_timeout = 0;
  m_infinite = false;
}

inline void CameraTransform::setBase(CWorldEntity* base){
  m_base = base;
}

inline void CameraTransform::setPosition(const vec3d& position){
  m_position = position;
}

inline void CameraTransform::setAngle(const btQuaternion& angle){
  m_angle = angle;
  m_angleOverride = false;
}

inline void CameraTransform::overrideAngle(const btQuaternion& angle){
  m_angle = angle;
  m_angleOverride = true;
}

#endif // CAMERATRANSFORM_H
