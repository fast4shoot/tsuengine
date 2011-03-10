#ifndef CLOGICENTITY_H
#define CLOGICENTITY_H

#include "CBaseEntity.h"
#include "CBaseEntityDescriptor.h"


class CLogicEntity : public CBaseEntity{
  public:
    void test(CBaseEntity* originator);
    void print(CBaseEntity* originator);
    void think();
    int random;
};

ENTITY_DESCRIPTOR(CLogicEntity, CBaseEntity)
  virtual void registerEntity(){
    classname("CLogicEntity");
    spawnable(false);
    input("test",&CLogicEntity::test);
    value("random", &CLogicEntity::random);
  }
};

#endif // CLOGICENTITY_H
