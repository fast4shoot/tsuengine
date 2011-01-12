#ifndef STATICMODELPART_H
#define STATICMODELPART_H

#include "libs/json/json.h"
#include "elements/Vertex.h"
#include "elements/Material.h"

class StaticModelPart{
  typedef std::vector<Vertex> VertexList;
  typedef std::vector<int> IndexList;

  public:
    StaticModelPart(json::mValue& data);
  protected:
    VertexList m_vertices;
    Material* m_material;
    IndexList m_indices;
};

#endif // STATICMODELPART_H
