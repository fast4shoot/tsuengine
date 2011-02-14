#ifndef STATICMODEL_H
#define STATICMODEL_H

#include <list>
#include "typedefs.h"
#include "Vertex.h"
#include "json/json.h"
#include "elements/StaticModelPart.h"
#include "elements/ModelBase.h"

class StaticModel: public ModelBase{
  typedef std::list<StaticModelPart> PartList;
  public:
    StaticModel(const json::mValue& value);
    double getRadius() const;
    int getVertexCount() const;
    int getIndexCount() const;
    void assignVbos(GLuint vbo, int vboOffset, GLuint indexVbo, int indexVboOffset);
    void draw();
    void uploadData();
  protected:
    PartList m_parts;
    double m_radius;
    int m_vertexCount;
    int m_indexCount;

  friend class CModelMgr;
};

inline double StaticModel::getRadius() const{
  return m_radius;
}

inline int StaticModel::getVertexCount() const{
  return m_vertexCount;
}

inline int StaticModel::getIndexCount() const{
  return m_indexCount;
}

#endif // STATICMODEL_H
