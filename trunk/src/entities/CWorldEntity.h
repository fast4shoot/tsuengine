#ifndef CWORLDENTITY_H
#define CWORLDENTITY_H

#include "CBaseEntity.h"


class CWorldEntity : public CBaseEntity{
  public:
    void init();
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);
    virtual void setPosition(const vec3d& newPosition);
    virtual void setRotation(double yaw, double pitch, double roll);
    vec3d m_position;
    vec3d m_rotation;
  protected:
    btTransform m_transform;

};

inline void CWorldEntity::setPosition(const vec3d& newPosition){
  m_transform.setOrigin(btVector3(newPosition.x, newPosition.y, newPosition.z));
}

inline void CWorldEntity::setRotation(double yaw, double pitch, double roll){
  m_transform.setRotation(btQuaternion(yaw, pitch, roll));
}

ENTITY_DESCRIPTOR(CWorldEntity, CBaseEntity)
  virtual void registerEntity(){
    spawnable(false);
    classname("CWorldEntity");
    value("position",&CWorldEntity::m_position);
    value("rotation",&CWorldEntity::m_rotation);
  }
};



#endif // CWORLDENTITY_H
