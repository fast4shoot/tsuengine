#include "FontBase.h"

#include <gl/gl.h>

FontBase::FontBase(const double size){
  _size=size;
}

void FontBase::render(const std::wstring& text, const double size, const rgba& color){
  render(text, size, vec2d(0,0), color);
}

void FontBase::render(const std::wstring& text, const double size, const vec2d& pos, const rgba& color){
  glColor4f(color.r,color.g, color.b, color.a);
  render(text, size, pos);
}

void FontBase::render(const std::wstring& text, const double size){
  render(text, size, vec2d(0,0));
}

void FontBase::render(const std::wstring& text, const double size, const vec2d& pos){
  glPushMatrix();
  glTranslatef(pos.x,size+pos.y,0.f);
  glScalef(size/_size,-size/_size,1.f);
  renderImpl(text);
  glPopMatrix();
}

