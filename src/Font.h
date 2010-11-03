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
      double            width();
      void              doLoad();
    private:
                        Font(FTGLTextureFont* font, const wstring& name, const double size);
                        ~Font();
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

inline void Font::render(const double size, const std::wstring& text){
  render(vec2d(0.,0.), size, text);
}

inline void Font::render(const double size, const std::wstring& text, const rgba& color){
  glColor4f(color.r,color.g, color.b, color.a);
  render(vec2d(0.,0.), size, text);
}

#endif // FONT_H
