#include <vector>
#include "CBaseEntity.h"
#include "CBaseEngine.h"
#include "globals.h"
#include "macros.h"
#include "CParamMgr.h"

//TODO: rewrite completely

CBaseEntity::CBaseEntity(){
  //link all parameters to variables here
  LINKVARTOPARAM(targetname,"targetname");

}


void CBaseEntity::init(){
  worldModel=0;
  collisionModel=0;
  visible=0;
  movetype=NONE;
}

void CBaseEntity::think(){

}

void CBaseEntity::draw(){
  if(visible){
    /*engine->setDrawPos(pos);
    engine->setDrawColor(1.0,1.0,1.0,1.0);
    engine->drawModel(worldModel);*/
  }
}

vec3d CBaseEntity::getPos(){
  return pos;
}

void CBaseEntity::processCollision(CBaseEntity *collider){}
