#include "CWorldEntity.h"
#include "DescriptorList.h"

void CWorldEntity::init(){
  setPosition(m_position);
  setRotation(m_rotation.x, m_rotation.y, m_rotation.z);
}

void CWorldEntity::getWorldTransform(btTransform &worldTrans) const{
  worldTrans = m_transform;
}

void CWorldEntity::setWorldTransform(const btTransform &worldTrans){
  m_transform = worldTrans;
}

REGISTER_ENTITY(CWorldEntity)
