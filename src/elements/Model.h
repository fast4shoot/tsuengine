#ifndef MODEL_H
#define MODEL_H

#include "datatypes.h"
#include "elements/ModelBase.h"

class Model{
  public:
    Model(ModelBase* model, ModelType type);
    virtual ~Model(){}
    virtual ModelType getType() const;
    virtual ModelBase* getModelRepresentation() const;

  protected:
    ModelBase* m_model;
    ModelType  m_type;
};

inline Model::Model(ModelBase* model, ModelType type){
  m_model = model;
  m_type = type;
}

inline ModelType Model::getType() const{
  return m_type;
}

inline ModelBase* Model::getModelRepresentation() const{
  return m_model;
}

#endif // MODEL_H
