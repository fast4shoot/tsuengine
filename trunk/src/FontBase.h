#ifndef FONTBASE_H
#define FONTBASE_H

#include <string>
#include <gl/gl.h>
#include "datatypes.h"
#include "typedefs.h"

class FontBase{
  public:
    void            render(const String& text, const double size, const rgba& color);
    void            render(const String& text, const double size, const vec2d& pos, const rgba& color);
    void            render(const String& text, const double size);
    void            render(const String& text, const double size, const vec2d& pos);
                    FontBase(const double size);
        virtual     ~FontBase(){};
  protected:
    virtual void    renderImpl(const String& text)=0;
    int             _size;
};

inline void FontBase::render(const String& text, const double size, const rgba& color){
  render(text, size, vec2d(0,0), color);
}

inline void FontBase::render(const String& text, const double size, const vec2d& pos, const rgba& color){
  glColor4f(color.r,color.g, color.b, color.a);
  render(text, size, pos);
}

inline void FontBase::render(const String& text, const double size){
  render(text, size, vec2d(0,0));
}

inline void FontBase::render(const String& text, const double size, const vec2d& pos){
  glPushMatrix();
  glTranslatef(pos.x,size+pos.y,0.f);
  glScalef(size/_size,-size/_size,1.f);
  renderImpl(text);
  glPopMatrix();
}

#endif // FONTBASE_H
