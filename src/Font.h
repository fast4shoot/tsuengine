#ifndef FONT_H
#define FONT_H

#include <string>
#include "glew/glew.h"
#include "vec2d.h"
#include "datatypes.h"
#include "FTGL/FTGL/ftgl.h"
#include "FontBase.h"
#include "typedefs.h"

class Font : public FontBase{
    public:
      double            width(const String& text, double size);
    protected:
      virtual void      renderImpl(const String& text);
                        Font(FTGLTextureFont* font, const String& name, const double size);
                        ~Font();
      FTGLTextureFont*  _font;
      String      _name;

    friend class CFontMgr;
    friend class FontWrapped;
};

inline double Font::width(const String& text, double size){
  return (size/_size)*_font->Advance(text.c_str());
}


#endif // FONT_H
