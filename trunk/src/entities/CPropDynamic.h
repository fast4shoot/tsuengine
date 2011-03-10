#ifndef CPROPDYNAMIC_H
#define CPROPDYNAMIC_H

#include "CWorldEntity.h"


class CPropDynamic : public CWorldEntity{
  public:
    void spawn();
    Model* m_model;
};

ENTITY_DESCRIPTOR(CPropDynamic, CWorldEntity)
  virtual void registerEntity(){
    spawnable(true);
    classname("prop_dynamic");
    value("model",&CPropDynamic::m_model);
  }
};

#endif // CPROPDYNAMIC_H
