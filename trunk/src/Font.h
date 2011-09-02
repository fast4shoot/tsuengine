#ifndef FONT_H
#define FONT_H

#include <string>
#include "vec2d.h"
#include "datatypes.h"
#include <FTGL/ftgl.h>
#include "FontBase.h"
#include "typedefs.h"

class Font : public FontBase{
    public:
      double            width(const String& text, double size);
    protected:
      virtual void      renderImpl(const String& text);
                        Font(FTGLTextureFont* font, const String& name, const double size);
      void              reset(FTGLTextureFont* font, const String& name, const double size);
                        ~Font();
      FTGLTextureFont*  _font;
      String      _name;

    friend class CFontMgr;
    friend class FontWrapped;
};


#endif // FONT_H
