#ifndef MODELHANDLE_H
#define MODELHANDLE_H

#include "elements/ModelBase.h"

class ModelHandle{
  public:
    ModelHandle(ModelBase* model){}
    virtual ~ModelHandle();
  protected:
};

#endif // MODELHANDLE_H
