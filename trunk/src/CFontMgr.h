#ifndef CFONTMGR_H
#define CFONTMGR_H

#include <map>
#include <string>
#include "FTGL/FTGL/ftgl.h"


using namespace std;

class Font;

typedef map<wstring, Font*> FontList;


class CFontMgr{
  public:
    Font* getFont(const wstring& name, const double size);
    FTGLTextureFont* loadFont(const wstring& name, const double size);
  private:
    FTGLTextureFont* createFTGLFont(const wstring& name);
    FontList _fonts;
};

#endif
