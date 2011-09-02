#include "Font.h"

#include <cmath>
#include "CFontMgr.h"
#include "macros.h"
#include "CBaseEngine.h"
void Font::renderImpl(const String& text){
  _font->Render(text.c_str());
  //_font->Render("ěščřžýáíé, 日本人");
}

void Font::reset(FTGLTextureFont* font, const String& name, const double size){
  delete _font;
  FontBase::reset(size);
  _name = name;
  _font = font;
}

Font::Font(FTGLTextureFont* font, const String& name, const double size):
  FontBase(size),
  _name(name),
  _font(font)
{}

Font::~Font(){
  delete _font;
}

double Font::width(const String& text, double size){
  return (size/_size)*_font->Advance(text.c_str());
}
