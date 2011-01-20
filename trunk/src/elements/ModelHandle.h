#ifndef MODELHANDLE_H
#define MODELHANDLE_H

#include "datatypes.h"
#include "elements/ModelBase.h"

class ModelHandle{
  public:
    ModelHandle(ModelBase* model, ModelType type);
    virtual ~ModelHandle();

  protected:
    ModelBase* m_model;
    ModelType  m_type;
};

inline ModelHandle::ModelHandle(ModelBase* model, ModelType type){
  m_model = model;
  m_type = type;
}

#endif // MODELHANDLE_H
