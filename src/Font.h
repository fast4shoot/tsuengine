#ifndef FONT_H
#define FONT_H

#include <string>
#include <gl/gl.h>
#include "vec2d.h"
#include "datatypes.h"
#include "FTGL/FTGL/ftgl.h"
#include "FontBase.h"

class Font : public FontBase{
    public:
      double            width(const std::wstring& text, double size);
    protected:
      virtual void      renderImpl(const std::wstring& text);
                        Font(FTGLTextureFont* font, const std::wstring& name, const double size);
                        ~Font();
      FTGLTextureFont*  _font;
      std::wstring      _name;

    friend class CFontMgr;
    friend class FontWrapped;
};

inline double Font::width(const std::wstring& text, double size){
  return (size/_size)*_font->Advance(text.c_str());
}


#endif // FONT_H
