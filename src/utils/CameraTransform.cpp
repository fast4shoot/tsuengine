#include "CameraTransform.h"

#include "CBaseEngine.h"
#include "entities/CWorldEntity.h"
#include "utils/math.h"

CameraTransform::CameraTransform(){
  m_infinite = false;
}

CameraTransform::CameraTransform(double timeout){
  m_timeout = engine->getTime()+timeout;
}

bool CameraTransform::isActive(){
  if(m_infinite) return true;
  if(m_timeout < engine->getTime()) return true;
  return false;
}

void CameraTransform::doTransform(){

  btTransform transform = getTransform();

  btVector3 axis = transform.getRotation().getAxis();
  glRotatef(-toDeg(transform.getRotation().getAngle()), axis.x(), axis.y(), axis.z());
  glTranslatef(-transform.getOrigin().x(), -transform.getOrigin().y(), -transform.getOrigin().z());

  /*float matrix[16];
  for(int i = 0; i < 16; i++){
    matrix[i] = 1.f;
  }
  transform.inverse().getOpenGLMatrix(matrix);
  glMultMatrixf(matrix);*/

}

btTransform CameraTransform::getTransform(){
  btTransform transform;
  if(m_base){
    m_base->getWorldTransform(transform);
  }else{
    transform.setIdentity();
  }

  transform.setOrigin(transform.getOrigin()+btVector3(m_position.x, m_position.y, m_position.z));
  if(m_angleOverride){
    transform.setRotation(m_angle);
  }else{
    transform.setRotation(transform.getRotation()+m_angle);
  }

  return transform;

}

vec3d CameraTransform::getTransformedPosition(){
  btVector3 pos = getTransform().getOrigin();
  return vec3d(pos.x(), pos.y(), pos.z());
}
vec3d getTransformedDirection(){
  btVector3 dir(1., 0., 0.);

}
