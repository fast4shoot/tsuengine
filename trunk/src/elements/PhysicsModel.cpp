#include "PhysicsModel.h"


#include "vec3d.h"
#include "typedefs.h"
#include "CBaseEngine.h"

PhysicsModel::PhysicsModel():
  m_mass(0.),
  m_shape(NULL)
{}


PhysicsModel::PhysicsModel(const json::mValue& value){
  const String& type = value.get_obj().find("type")->second.get_str();
  json::mObject::const_iterator it=value.get_obj().find("mass");
  if(it != value.get_obj().end()){
    m_mass = it->second.get_real();
  }else{
    m_mass = 0.;
  }
  if(type == "none"){
    engine->log("type == \"none\"");
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
  }else{
    engine->warning(sformat("Unknown physics model type: %s",type.c_str()));
  }
}

