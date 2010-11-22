#ifndef CFONTMGR_H
#define CFONTMGR_H

#include <map>
#include "FTGL/FTGL/ftgl.h"
#include "typedefs.h"

class Font;

class CFontMgr{
  typedef std::map<String, Font*> FontList;
  public:
    Font* getFont(const String& name, const double size);
    FTGLTextureFont* loadFont(const String& name, const double size);
  private:
    FTGLTextureFont* createFTGLFont(const String& name);
    FontList _fonts;
};

#endif
