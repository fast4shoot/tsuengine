#ifndef STATICMODELIMPL_H
#define STATICMODELIMPL_H

#include <list>
#include "elements/StaticModelPart.h"
#include "elements/PhysicsModel.h"

class StaticModelImpl{
  typedef std::list<StaticModelPart> PartList;
  public:
    StaticModelImpl(const json::mValue& value);
    double getRadius() const;
    int getVertexCount() const;
    int getIndexCount() const;
    void assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset);
    void render();
    void uploadData();
    PhysicsModel* getPhysModel();
  protected:
    PartList m_parts;
    double m_radius;
    int m_vertexCount;
    int m_indexCount;
    PhysicsModel* m_physModel;
};

inline double StaticModelImpl::getRadius() const{
  return m_radius;
}

inline int StaticModelImpl::getVertexCount() const{
  return m_vertexCount;
}

inline int StaticModelImpl::getIndexCount() const{
  return m_indexCount;
}

inline PhysicsModel* StaticModelImpl::getPhysModel(){
  return m_physModel;
}

#endif // STATICMODELIMPL_H
