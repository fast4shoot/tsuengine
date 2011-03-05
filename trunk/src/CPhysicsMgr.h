#ifndef CPHYSICSMGR_H
#define CPHYSICSMGR_H

#include "btBulletDynamicsCommon.h"
#include "elements/Model.h"
#include "elements/PhysicsModel.h"
#include "datatypes.h"

class CPhysicsMgr{
  public:
    CPhysicsMgr();
    void update();
    void addBody(Model* mdl, PhysicsModel* physMdl, PhysicsType type);
  protected:
    btBroadphaseInterface*	m_broadphase;
	  btCollisionDispatcher*	m_dispatcher;
	  btConstraintSolver*	m_solver;
	  btDefaultCollisionConfiguration* m_collisionConfiguration;
	  btDynamicsWorld*  m_dynamicsWorld;

};

#endif // CPHYSICSMGR_H
