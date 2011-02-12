#include "CLogicEntity.h"
#include "DescriptorList.h"
#include "CBaseEngine.h"

void CLogicEntity::test(CBaseEntity* originator){
  engine->log(sformat("imho logicentity test: %d", random));
}


void CLogicEntity::print(CBaseEntity* originator){
  engine->log("rofl test z logické entity");
}

REGISTER_ENTITY(CLogicEntity)
