#include "Model.h"

#include "utils/math.h"
#include "entities/CWorldEntity.h"

void Model::draw(){
  glPushMatrix();
  glTranslatef(m_transform.getOrigin().x(), m_transform.getOrigin().y(), m_transform.getOrigin().z());
  btVector3 axis = m_transform.getRotation().getAxis();
  glRotatef(toDeg(m_transform.getRotation().getAngle()), axis.x(), axis.y(), axis.z());
  render();
  glPopMatrix();
}

void Model::getWorldTransform(btTransform &worldTrans) const{
  if(m_linkedWorldEntity){
    if(getPhysics() == P_DYNAMIC){
      m_linkedWorldEntity->getWorldTransform(worldTrans);
    }else{
      btTransform entTransform;
      m_linkedWorldEntity->getWorldTransform(entTransform);
      worldTrans.mult(entTransform, m_transform);
    }
  }else{
    worldTrans = m_transform;
  }
}

void Model::setWorldTransform(const btTransform &worldTrans){
  if(getPhysics() == P_DYNAMIC){
    if(m_linkedWorldEntity){
      m_linkedWorldEntity->setWorldTransform(worldTrans);
    }else{
      m_transform = worldTrans;
    }
  }
}

void Model::linkToEntity(CBaseEntity* ent){
  m_linkedBaseEntity = ent;
  m_linkedWorldEntity = NULL;
}

void Model::linkToEntity(CWorldEntity* ent){
  m_linkedBaseEntity = ent;
  m_linkedWorldEntity = ent;
}
