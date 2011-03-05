#ifndef STATICMODEL_H
#define STATICMODEL_H

#include <list>
#include "typedefs.h"
#include "Vertex.h"
#include "json/json.h"
#include "elements/StaticModelPart.h"
#include "elements/Model.h"
#include "elements/StaticModelImpl.h"


class StaticModel: public Model{

  public:
    StaticModel(StaticModelImpl* impl);
    //double getRadius() const;
    void render();
    virtual void setPhysics(PhysicsType physics);

  protected:
    StaticModelImpl* m_impl;

  friend class CModelMgr;
};

/*
inline double StaticModel::getRadius() const{
  return m_impl;
}*/



#endif // STATICMODEL_H
