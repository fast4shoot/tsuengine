#include "StaticModel.h"


#include <algorithm>
#include "CBaseEngine.h"


StaticModel::StaticModel(StaticModelImpl* impl):
Model(M_STATIC),
m_impl(impl)
{}

void StaticModel::render(){
  m_impl->render();
}

void StaticModel::setPhysics(PhysicsType physics){
  engine->log(sformat("addBody(%p, %p, %d);",this, m_impl->getPhysModel(), physics));
  engine->physics->addBody(this, m_impl->getPhysModel(), physics);
}
