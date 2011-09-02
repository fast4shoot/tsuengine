#include "PointLight.h"

#include "CBaseEngine.h"

void PointLight::calculate(){
  m_stacks = int(clamp(m_size - 1., 8., 10.));  //OH GOD
  m_sphereDiameter = m_size / cos(PI/m_stacks);
  engine->log( ( format("stacks: %d, diameter: %f") % m_stacks % m_sphereDiameter ).str() );
}
