#ifndef CPHYSICSMGR_H
#define CPHYSICSMGR_H

#include <set>
#include "btBulletDynamicsCommon.h"
#include "elements/Model.h"
#include "elements/PhysicsModel.h"
#include "datatypes.h"

class CPhysicsMgr{
  public:
    CPhysicsMgr();
    void update();
    btRigidBody* addBody(Model* mdl, PhysicsModel* physMdl, PhysicsType type);
    void removeAll();
  protected:
    btBroadphaseInterface*	m_broadphase;
	btCollisionDispatcher*	m_dispatcher;
	btConstraintSolver*	m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDynamicsWorld*  m_dynamicsWorld;
	typedef std::set<btRigidBody*> BodyList;
	BodyList m_bodies;
};

#endif // CPHYSICSMGR_H
