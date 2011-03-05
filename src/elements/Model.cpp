#include "Model.h"

#include "utils/math.h"

#include "CBaseEngine.h"

void Model::draw(){
  glPushMatrix();
  glTranslatef(m_transform.getOrigin().x(), m_transform.getOrigin().y(), m_transform.getOrigin().z());
  btVector3 axis = m_transform.getRotation().getAxis();
  glRotatef(toDeg(m_transform.getRotation().getAngle()), axis.x(), axis.y(), axis.z());
  render();
  glPopMatrix();
}

void Model::getWorldTransform(btTransform &worldTrans) const{
  //engine->log("getWorldTransform()");
  worldTrans = m_transform;
}

void Model::setWorldTransform(const btTransform &worldTrans){
  //engine->log("setWorldTransform()");
  m_transform = worldTrans;
}
