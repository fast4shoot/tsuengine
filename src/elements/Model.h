#ifndef MODEL_H
#define MODEL_H

#include "elements/ModelBase.h"
#include "btBulletDynamicsCommon.h"
#include "vec3d.h"
#include "datatypes.h"

class CBaseEntity;
class CWorldEntity;


class Model: public btMotionState{
  public:
    Model(ModelType type);
    virtual ~Model(){}
    virtual ModelType getType() const;

    virtual void setPosition(const vec3d& newPosition);
    virtual void setRotation(float pitch, float yaw, float roll);
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

    virtual void linkToEntity(CBaseEntity* ent);
    virtual void linkToEntity(CWorldEntity* ent);
    virtual CBaseEntity* getLinkedEntity() const;

    virtual void setPhysics(PhysicsType physics)=0;
    virtual PhysicsType getPhysics() const=0;

    void setVisible(bool visible);
    bool getVisible() const;

    virtual void draw(int pass);
    virtual void render(int pass)=0;

  protected:
    virtual void enablePhysics(bool physics)=0;
    ModelType  m_type;
    btTransform m_transform;
    CWorldEntity* m_linkedWorldEntity;
    CBaseEntity* m_linkedBaseEntity;
    bool m_visible;

};

inline Model::Model(ModelType type):
  m_type(type),
  m_transform(),
  m_visible(true),
  m_linkedBaseEntity(NULL),
  m_linkedWorldEntity(NULL)
{
  m_transform.setIdentity();

}

inline ModelType Model::getType() const{
  return m_type;
}

inline void Model::setPosition(const vec3d& newPosition){
  m_transform.setOrigin(btVector3(newPosition.x, newPosition.y, newPosition.z));
}

inline void Model::setRotation(float pitch, float yaw, float roll){
  m_transform.setRotation(btQuaternion(yaw, pitch, roll));
}

inline CBaseEntity* Model::getLinkedEntity() const{
  return m_linkedBaseEntity;
}

inline bool Model::getVisible() const{
  return m_visible;
}


#endif // MODEL_H
