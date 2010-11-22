#include "Font.h"

#include <cmath>
#include "CFontMgr.h"
#include "macros.h"
void Font::renderImpl(const String& text){
  _font->Render(text.c_str());
  //_font->Render("ěščřžýáíé, 日本人");
}

Font::Font(FTGLTextureFont* font, const String& name, const double size):
  FontBase(size),
  _name(name),
  _font(font)
{}

Font::~Font(){
  delete _font;
}
