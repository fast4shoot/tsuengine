#include "CPlayer.h"

#include "CBaseEngine.h"
#include "macros.h"
#include "DescriptorList.h"
#include "utils/math.h"
#include "utils/FilteredClosestRayResultCallback.h"

void CPlayer::think(){

  m_yaw += -engine->input->getMouseDelta().x * engine->getTimeScale() * 0.005;
  m_pitch += -engine->input->getMouseDelta().y * engine->getTimeScale() * 0.005;
  m_pitch = clamp(m_pitch, -1.5, 1.5);

  m_yaw = saw(m_yaw, 2.*PI, 2.*PI);
  //engine->log(format("timeDelta: %1%, mouseDelta.x: %2%") % engine->getTimeDelta() % engine->input->getMouseDelta().x);
  //engine->log(format("playerRot: %1%, %2%") % toDeg(m_yaw) % toDeg(m_pitch));

  bool moving;
  btVector3 direction(0., 0., 0.);

  if(engine->input->keyDown(DIK_W)){
    direction+=btVector3(0., 0., 1.);
  }

  if(engine->input->keyDown(DIK_S)){
    direction+=btVector3(0., 0., -1.);
  }

  if(engine->input->keyDown(DIK_A)){
    direction+=btVector3(1., 0., 0.);
  }

  if(engine->input->keyDown(DIK_D)){
    direction+=btVector3(-1., 0., 0.);
  }

  if(engine->input->keyPressed(DIK_SPACE)){
    m_player->jump();
  }

  moving = (direction != btVector3(0., 0., 0.)?true:false);

  if(moving){
    m_speed += 6 * engine->getTimeDelta();
  }else{
    m_speed -= 6 * engine->getTimeDelta();
  }

  m_speed = clamp(m_speed, 0., 3. );

  if(moving){
    direction = direction.rotate(btVector3(0,1,0),m_yaw);
    direction.normalize();
    lastDirection = direction;
    direction*=m_speed;
  }else{
    direction = lastDirection*m_speed;
  }
  m_player->setVelocityForTimeInterval(direction, .1);

  //m_camera->setPosition(vec3d(0., 0.75, 0.));
  btQuaternion cameraAngle = btQuaternion(m_yaw+PI, m_pitch, 0.);
  m_camera->overrideAngle(cameraAngle);


  btTransform transform = m_ghost->getWorldTransform();
  transform.setRotation(btQuaternion(m_yaw, 0., 0.));
  m_ghost->setWorldTransform(transform);
  transform.setRotation(cameraAngle);
  this->setWorldTransform(transform);

  engine->debug(sformat("player pos: %.8f %.8f %.8f", getPosition().x, getPosition().y, getPosition().z ));

  if(engine->input->keyPressed(DIK_E)){
    vec3d from = getPosition();
    vec3d to = getPosition()+getForward()*1.2 + vec3d(0., 0.3, 0.);

    FilteredClosestRayResultCallback ray(from, to);
    ray.addToBlacklist(m_ghost);
    engine->physics->getWorld()->rayTest(from, to, ray);

    if(ray.m_collisionObject && ray.m_collisionObject->getUserPointer() && ((Model*)(ray.m_collisionObject->getUserPointer()))->getLinkedEntity()){
      (static_cast<Model*>(ray.m_collisionObject->getUserPointer()))->getLinkedEntity()->fireInput("use",this);
    }
  }
}

void CPlayer::spawn(){

  m_yaw = 0.;
  m_pitch = 0.;

  m_camera = new CameraTransform();
  m_camera->setBase(this);
  m_camera->setPosition(vec3d(0., 0.3, 0.));
  engine->camera->addTransform(m_camera);

  m_ghost = new btPairCachingGhostObject();
  btTransform transform;
  this->getWorldTransform(transform);
  m_ghost->setWorldTransform(transform);

  m_shape = new btCapsuleShape(0.30, 1.7);

  m_ghost->setCollisionShape(m_shape);
  m_ghost->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);


  m_player = new btKinematicCharacterController(m_ghost, m_shape,.3);
  m_player->setFallSpeed(2.);
  m_player->setJumpSpeed(5.);
  engine->physics->getWorld()->addCollisionObject(m_ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter);

  engine->physics->getWorld()->addAction(m_player);

}

CPlayer::~CPlayer(){
  engine->physics->getWorld()->removeAction(m_player);
  engine->physics->getWorld()->removeCollisionObject(m_ghost);
  delete m_player;
  delete m_ghost;
  delete m_shape;
}

REGISTER_ENTITY(CPlayer)
