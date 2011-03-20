#include "PhysicsModel.h"


#include "vec3d.h"
#include "typedefs.h"
#include "CBaseEngine.h"

PhysicsModel::PhysicsModel():
  m_mass(0.),
  m_shape(NULL),
  m_meshInterface(NULL),
  m_indices(NULL),
  m_vertices(NULL)
{}

PhysicsModel::~PhysicsModel(){
  delete[] m_indices;
  delete[] m_vertices;
  delete m_meshInterface;
}


PhysicsModel::PhysicsModel(const json::mValue& value){
  const String& type = value.get_obj().find("type")->second.get_str();
  json::mObject::const_iterator it=value.get_obj().find("mass");
  if(it != value.get_obj().end()){
    m_mass = it->second.get_real();
  }else{
    m_mass = 0.;
  }
  if(type == "none"){
    m_mass = 0.;
    m_shape = NULL;
  }else if(type == "box"){
    vec3d size;
    json::extract(size, value.get_obj().find("size")->second);
    m_shape = new btBoxShape(btVector3(size.x,size.y,size.z));
  }else if(type == "cylinder"){
    vec3d size;
    json::extract(size, value.get_obj().find("size")->second);
    m_shape = new btCylinderShape(btVector3(size.x,size.y,size.z));
  }else if(type == "sphere"){
    double size;
    json::extract(size, value.get_obj().find("size")->second.get_real());
    m_shape = new btSphereShape(size);
  }else if(type == "mesh"){

    const json::mArray& indices = value.get_obj().find("indices")->second.get_array();
    const json::mArray& vertices = value.get_obj().find("vertices")->second.get_array();
    m_vertices = new btScalar[vertices.size()*3];
    m_indices = new int[indices.size()];
    int i = 0;
    for(json::mArray::const_iterator it = indices.begin(); it != indices.end(); ++it){
      json::extract(m_indices[i++], *it);
    }
    i = 0;
    for(json::mArray::const_iterator it = vertices.begin(); it != vertices.end(); ++it){
      vec3d vert;
      json::extract(vert, *it);
      m_vertices[i++] = vert.x;
      m_vertices[i++] = vert.y;
      m_vertices[i++] = vert.z;
    }
    m_meshInterface = new btTriangleIndexVertexArray(indices.size()/3, m_indices, 3*sizeof(int), vertices.size(), m_vertices, 3*sizeof(btScalar));
    m_shape = new btBvhTriangleMeshShape(m_meshInterface, false);
  }else{
    engine->warning(sformat("Unknown physics model type: %s",type.c_str()));
  }
}

