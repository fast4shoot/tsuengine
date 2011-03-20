#include "CPhysicsMgr.h"

#include "CBaseEngine.h"
#include "datatypes.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
CPhysicsMgr::CPhysicsMgr(){

	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0,-10,0));
	m_dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

}

void CPhysicsMgr::update(){
  m_dynamicsWorld->stepSimulation(engine->getTimeDelta());
}

btRigidBody* CPhysicsMgr::addBody(Model* mdl, PhysicsModel* physMdl, PhysicsType type){
  if(type == P_NONE){
    return NULL;
  }
  if(type == P_DYNAMIC && physMdl->getMass() == 0.){
    engine->warning("Can't create dynamic body without mass!");
    type = P_KINEMATIC;
  }

  double mass = (type == P_DYNAMIC?physMdl->getMass():0.);

  btVector3 localInertia(0,0,0);
	if (type == P_DYNAMIC){
		physMdl->getCollisionShape()->calculateLocalInertia(mass,localInertia);
	}

  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mdl, physMdl->getCollisionShape(),localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

  body->setUserPointer(mdl);

  if(type == P_KINEMATIC){
    body->setCollisionFlags( body->getCollisionFlags() |
    btCollisionObject::CF_KINEMATIC_OBJECT);
    body->setActivationState(DISABLE_DEACTIVATION);
  }else{
    body->setActivationState(ACTIVE_TAG);
  }

  m_dynamicsWorld->addRigidBody(body);

  if(type != P_KINEMATIC){
    body->setActivationState(ACTIVE_TAG);
  }

  m_bodies.insert(body);

  return body;
}

void CPhysicsMgr::removeAll(){
  for(BodyList::iterator it = m_bodies.begin(); it != m_bodies.end(); ++it){
    m_dynamicsWorld->removeRigidBody(*it);
    delete (*it);
  }
  m_bodies.clear();
}
