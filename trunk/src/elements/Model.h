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
    virtual void setPosition(const vec3d& newPosition);
    virtual void setRotation(float pitch, float yaw, float roll);

    virtual void draw();

  protected:
    ModelBase* m_model;
    ModelType  m_type;
    vec3d m_position;
    vec3d m_rotation;
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

inline void Model::setPosition(const vec3d& newPosition){
  m_position = newPosition;
}

inline void Model::setRotation(float pitch, float yaw, float roll){
  m_rotation = vec3d(pitch, yaw, roll);
}

inline void Model::draw(){
  glPushMatrix();
  glTranslatef(m_position.x, m_position.y, m_position.z);
  glRotatef(m_rotation.x, 1, 0, 0);
  glRotatef(m_rotation.y, 0, 1, 0);
  glRotatef(m_rotation.z, 0, 0, 1);
  m_model->draw();
  glPopMatrix();
}

#endif // MODEL_H
