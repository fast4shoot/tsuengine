#include "Font.h"

#include <cmath>
#include "CFontMgr.h"
#include "macros.h"
void Font::renderImpl(const std::wstring& text){
  _font->Render(text.c_str());
}

Font::Font(FTGLTextureFont* font, const std::wstring& name, const double size):
  FontBase(size),
  _name(name),
  _font(font)
{}

Font::~Font(){
  delete _font;
}
