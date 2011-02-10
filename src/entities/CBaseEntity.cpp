#include <vector>
#include "CBaseEntity.h"
#include "CBaseEngine.h"
#include "globals.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "CEntMgr.h"
#include "DescriptorList.h"

CBaseEntity::CBaseEntity(){
  visible=0;
}

void CBaseEntity::think(){

}

vec3d CBaseEntity::getPos(){
  return pos;
}

REGISTER_DESCRIPTOR(CBaseEntity)
