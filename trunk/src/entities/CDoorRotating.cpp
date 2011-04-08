#include "CDoorRotating.h"
#include "DescriptorList.h"
#include "utils/math.h"

CDoorRotating::CDoorRotating():
  CDoorBase()
{
  m_rotationAxis = vec3d(0., 1., 0.);
  m_rotationAngle = 90.;
}

void CDoorRotating::init(){
  CDoorBase::init();
  m_model->setPhysics(P_KINEMATIC);
  m_model->linkToEntity(this);

}

void CDoorRotating::spawn(){
  m_startAngle = m_transform.getRotation();
  m_endAngle = m_transform.getRotation() * btQuaternion(m_rotationAxis, toRad(m_rotationAngle));
}

void CDoorRotating::think(){
  CDoorBase::think();
  m_transform.setRotation(m_startAngle.slerp(m_endAngle, m_fraction));
}

REGISTER_ENTITY(CDoorRotating)
