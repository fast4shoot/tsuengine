#include "CWorldEntity.h"
#include "DescriptorList.h"

#include "CBaseEngine.h"
#include "utils/math.h"

CWorldEntity::CWorldEntity():
  CBaseEntity()
{
  //engine->log("identity");
  m_transform.setIdentity();
  m_position = vec3d();
  m_rotation = vec3d();
}

void CWorldEntity::init(){
  CBaseEntity::init();
  setPosition(m_position);
  setRotation(toRad(m_rotation.x), toRad(m_rotation.y), toRad(m_rotation.z));
}

void CWorldEntity::getWorldTransform(btTransform &worldTrans) const{
  worldTrans = m_transform;
}

void CWorldEntity::setWorldTransform(const btTransform &worldTrans){
  m_transform = worldTrans;
}

vec3d CWorldEntity::getPosition(){
  return vec3d(m_transform.getOrigin().x(), m_transform.getOrigin().y(), m_transform.getOrigin().z());
}

vec3d CWorldEntity::getForward(){
  btVector3 dir(0., 0., -1.);

  return vec3d(dir.rotate(m_transform.getRotation().getAxis(), m_transform.getRotation().getAngle())).normalized();
}

vec3d CWorldEntity::getUp(){
  btVector3 dir(0., 1., 0.);

  return vec3d(dir.rotate(m_transform.getRotation().getAxis(), m_transform.getRotation().getAngle())).normalized();
}

REGISTER_ENTITY(CWorldEntity)
