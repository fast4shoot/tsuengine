#ifndef FONT_H
#define FONT_H

#include <string>
#include <gl/gl.h>
#include "vec2d.h"
#include "datatypes.h"
#include "FTGL/FTGL/ftgl.h"

using namespace std;

class CFontMgr;

class Font
{
    public:
      inline void       render(const vec2d& pos,  const double size,        const std::wstring& text, const rgba& color);
      void              render(const vec2d& pos,  const double size,        const std::wstring& text);
      inline void       render(const double size, const std::wstring& text);
      inline void       render(const double size, const std::wstring& text, const rgba& color);
      inline void       setSize(const int size);
    private:
                        Font(CFontMgr* mgr, const wstring& name);
      int               _size;  //-1 means not loaded
      FTGLTextureFont*  _font;
      CFontMgr*         _mgr;
      wstring           _name;

    friend class CFontMgr;
};

inline void Font::render(const vec2d& pos,  const double size, const std::wstring& text, const rgba& color){
  glColor4f(color.r,color.g, color.b, color.a);
  render(pos, size, text);
}

void Font::render(const double size, const std::wstring& text){
  render(vec2d(0.,0.), size, text);
}

void Font::render(const double size, const std::wstring& text, const rgba& color){
  glColor4f(color.r,color.g, color.b, color.a);
  render(vec2d(0.,0.), size, text);
}

void Font::setSize(const int size){
  _size=size;
  _font->FaceSize(size);
}

#endif // FONT_H
