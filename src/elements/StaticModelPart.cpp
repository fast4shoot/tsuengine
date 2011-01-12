#include "StaticModelPart.h"

#include "CBaseEngine.h"
#include "elements/Plane.h"

StaticModelPart::StaticModelPart(json::mValue& data){
  json::mObject& obj = data.get_obj();
  m_material = engine->materials->getMaterial(obj.find("material")->second.get_str());

  json::mArray& vertices = obj.find("vertices")->second.get_array();
  m_vertices.reserve(vertices.size());

  for(json::mArray::iterator it=vertices.begin(); it!=vertices.end(); ++it){
    m_vertices.push_back(Vertex(*it));
  }

  json::mArray& indices = obj.find("indices")->second.get_array();
  m_indices.reserve(indices.size());

  if(indices.size()%3){
    engine->warning(sformat("Incorrect number of indices: %d", indices.size()));
  }

  for(json::mArray::iterator it=indices.begin(); it!=indices.end(); ++it){
    int i1=(*it).get_int();
    ++it;
    if(it==indices.end()) break;
    int i2=(*it).get_int();
    ++it;
    if(it==indices.end()) break;
    int i3=(*it).get_int();
    if(i1 == i2 || i1 == i3 || i2 == i3){
      engine->warning(sformat("Indices %d, %d and %d do not form a triangle, skipping...", i1, i2, i3));
      continue;
    }
    Plane plane = Plane(m_vertices[i1], m_vertices[i2], m_vertices[i3]);
    m_vertices[i1].addNormal(plane.getNormal());
    m_vertices[i2].addNormal(plane.getNormal());
    m_vertices[i3].addNormal(plane.getNormal());
    m_indices.push_back(i1);
    m_indices.push_back(i2);
    m_indices.push_back(i3);
  }

}
