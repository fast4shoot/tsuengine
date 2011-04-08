#ifndef CDOORROTATING_H
#define CDOORROTATING_H

#include "CDoorBase.h"


class CDoorRotating : public CDoorBase{
  public:
    CDoorRotating();
    void init();
    void spawn();
    void think();
    vec3d m_rotationAxis;
    float m_rotationAngle;
    Model* m_model;
  protected:
    btQuaternion m_startAngle;
    btQuaternion m_endAngle;

};

ENTITY_DESCRIPTOR(CDoorRotating, CDoorBase)
  virtual void registerEntity(){
    spawnable(true);
    classname("func_door_rotating");
    value("model",&CDoorRotating::m_model);
    value("rotationAxis",&CDoorRotating::m_rotationAxis);
    value("rotationAngle",&CDoorRotating::m_rotationAngle);
  }
};


#endif // CDOORROTATING_H
