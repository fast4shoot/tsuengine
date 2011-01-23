#ifndef STATICMODELPART_H
#define STATICMODELPART_H

#include "libs/json/json.h"
#include "elements/Vertex.h"
#include "elements/Material.h"

class StaticModelPart{
  typedef std::vector<Vertex> VertexList;
  typedef std::vector<GLuint> IndexList;

  public:
    StaticModelPart(json::mValue& data);
    double getRadius() const;
    int getVertexCount() const;
    int getIndexCount() const;
    void setOffsets(int vboOffset, int indexVboOffset);
    void uploadData();
    void draw();
  protected:
    VertexList m_vertices;
    Material* m_material;
    IndexList m_indices;
    double m_radius;
    int m_vboOffset;
    int m_indexVboOffset;
};

inline double StaticModelPart::getRadius() const{
  return m_radius;
}

inline int StaticModelPart::getVertexCount() const{
  return m_vertices.size();
}

inline int StaticModelPart::getIndexCount() const{
  return m_indices.size();
}

inline void StaticModelPart::setOffsets(int vboOffset, int indexVboOffset){
  m_vboOffset = vboOffset;
  m_indexVboOffset = indexVboOffset;
}

#endif // STATICMODELPART_H
