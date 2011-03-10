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
    void setPhysics(PhysicsType physics);
    PhysicsType getPhysics() const;

  protected:
    StaticModelImpl* m_impl;
    PhysicsType m_physType;

  friend class CModelMgr;
};

/*
inline double StaticModel::getRadius() const{
  return m_impl;
}*/

inline PhysicsType StaticModel::getPhysics() const{
  return m_physType;
}

#endif // STATICMODEL_H
