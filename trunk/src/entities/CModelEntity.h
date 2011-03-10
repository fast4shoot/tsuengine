#ifndef CMODELENTITY_H
#define CMODELENTITY_H

#include "CVisibleEntity.h"
#include "elements/Model.h"


class CModelEntity : public CVisibleEntity{
  public:
    Model* m_model;
  protected:
  friend class CVisibleEntityDescriptor;
};

ENTITY_DESCRIPTOR(CModelEntity, CVisibleEntity)
  virtual void registerEntity(){
    spawnable(false);
    classname("CModelEntity");
    value("model",&CModelEntity::m_model);
  }
};


#endif // CMODELENTITY_H
