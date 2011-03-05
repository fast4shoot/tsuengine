#ifndef MODEL_H
#define MODEL_H

#include "datatypes.h"
#include "elements/ModelBase.h"
#include "btBulletDynamicsCommon.h"


class Model: public btMotionState{
  public:
    Model(ModelType type);
    virtual ~Model(){}
    virtual ModelType getType() const;
    virtual void setPosition(const vec3d& newPosition);
    virtual void setRotation(float pitch, float yaw, float roll);
    virtual ModelType getModelType();

    virtual void setPhysics(PhysicsType physics)=0;

    void getWorldTransform(btTransform &worldTrans) const;
    void setWorldTransform(const btTransform &worldTrans);

    virtual void draw();
    virtual void render()=0;

  protected:
    ModelType  m_type;
    btTransform m_transform;

};

inline Model::Model(ModelType type):
  m_type(type),
  m_transform()
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



inline ModelType Model::getModelType(){
  return m_type;
}



#endif // MODEL_H
