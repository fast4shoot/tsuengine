#include "CLogicEntity.h"
#include "DescriptorList.h"
#include "CBaseEngine.h"


void CLogicEntity::test(CBaseEntity* originator){
  engine->log(sformat("imho logicentity test: %d", random));
}

void CLogicEntity::print(CBaseEntity* originator){
  engine->log("rofl test z logické entity");
}

void CLogicEntity::think(){
  if(engine->input->keyPressed(DIK_A)){
    fireInput("test", NULL);
  }
  random++;
}

//REGISTER_ENTITY(CLogicEntity)
