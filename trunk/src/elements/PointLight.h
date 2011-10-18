#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "rgb.h"
#include "vec3d.h"
#include "GL/glew.h"
#include "utils/math.h"
#include "Program.h"

class PointLight{
  public:
    PointLight(const vec3d& pos, const rgb& color, float size);
    void setSize(float size);
    float getSize();
    void setColor(const rgb& color);
    rgb getColor();
    void setPosition(const vec3d& pos);
    vec3d getPosition();
    void drawVolume();
    void transform();
    void setUniforms(Program* program);
  private:
    void calculate();
    vec3d m_position;
    rgb m_color;
    float m_size;
    float m_sphereDiameter;
    int m_stacks;
    GLUquadric* m_quadric;
};

inline PointLight::PointLight(const vec3d& pos, const rgb& color, float size):
  m_position(pos),
  m_color(color),
  m_size(size)
{
  calculate();
  m_quadric = gluNewQuadric();
}

inline void PointLight::setSize(float size){
  m_size = size;
}

inline float PointLight::getSize(){
  return m_size;
}

inline void PointLight::setColor(const rgb& color){
  m_color = color;
}

inline rgb PointLight::getColor(){
  return m_color;
}

inline void PointLight::setPosition(const vec3d& pos){
  m_position = pos;
}

inline vec3d PointLight::getPosition(){
  return m_position;
}

inline void PointLight::drawVolume(){
  gluSphere(m_quadric, m_sphereDiameter, m_stacks, m_stacks);
}

inline void PointLight::transform(){
  glTranslatef(m_position.x, m_position.y, m_position.z);
}

inline void PointLight::setUniforms(Program* program){
  //program -> setUniformf("lightPos", m_position.x, m_position.y, m_position.z);
  //program -> setUniformf("color", m_color.r, m_color.g, m_color.b);
  //program -> setUniformf("size", m_size);
}

#endif // POINTLIGHT_H
