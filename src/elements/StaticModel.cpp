#include "StaticModel.h"

#include "CBaseEngine.h"

StaticModel::StaticModel(StaticModelImpl* impl):
Model(M_STATIC),
m_physType(P_NONE),
m_impl(impl)
{}

void StaticModel::render(int pass){
  m_impl->render(pass);
}

void StaticModel::setPhysics(PhysicsType physics){
  m_physType = physics;
  m_body = engine->physics->addBody(this, m_impl->getPhysModel(), physics);
}

void StaticModel::enablePhysics(bool physics){
  engine->physics->getWorld()->removeCollisionObject(m_body);
  if(physics){
    engine->physics->getWorld()->addCollisionObject(m_body);
  }
}
