#ifndef CPLAYER_H
#define CPLAYER_H

#include "CWorldEntity.h"
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <btBulletDynamicsCommon.h>
#include "utils/CameraTransform.h"

class CPlayer : public CWorldEntity{
  public:
    void spawn();
    void think();
    ~CPlayer();
  protected:
    btKinematicCharacterController* m_player;
    btPairCachingGhostObject* m_ghost;
    btConvexShape* m_shape;
    btVector3 lastDirection;
    CameraTransform* m_camera;
    double m_speed;
    Model* model;
    double m_yaw;
    double m_pitch;
};

ENTITY_DESCRIPTOR(CPlayer, CWorldEntity)
  virtual void registerEntity(){
    spawnable(true);
    classname("player");
  }
};

#endif // CPLAYER_H
