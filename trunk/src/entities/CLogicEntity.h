#ifndef CLOGICENTITY_H
#define CLOGICENTITY_H

#include "CBaseEntity.h"
#include "CBaseEntityDescriptor.h"


class CLogicEntity : public CBaseEntity{
  public:
    void test(CBaseEntity* originator);
    void print(CBaseEntity* originator);
    int random;
};

ENTITY_DESCRIPTOR(CLogicEntity, CBaseEntity)
  virtual void registerEntity(){
    inherit<CBaseEntityDescriptor>();
    classname("CLogicEntity");
    spawnable(false);
    input("test",&CLogicEntity::test);
    value("random", &CLogicEntity::random, 5);
  }
};

#endif // CLOGICENTITY_H
