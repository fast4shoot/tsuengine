#include "Model.h"

#include "utils/math.h"
#include "entities/CWorldEntity.h"

void Model::draw(int pass){
  if(getVisible()){
    glPushMatrix();
    btTransform transform;
    getWorldTransform(transform);
    glTranslatef(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z());
    btVector3 axis = transform.getRotation().getAxis();
    glRotatef(toDeg(transform.getRotation().getAngle()), axis.x(), axis.y(), axis.z());
    render(pass);
    glPopMatrix();
  }
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

void Model::setVisible(bool visible){
  if(m_visible != visible){
    enablePhysics(visible);
    m_visible = visible;
  }
}
