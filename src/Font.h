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
      double            width();
    protected:
      virtual void      renderImpl(const std::wstring& text);
                        Font(FTGLTextureFont* font, const std::wstring& name, const double size);
                        ~Font();
      FTGLTextureFont*  _font;
      std::wstring      _name;

    friend class CFontMgr;
    friend class WrappedFont;
};


#endif // FONT_H
