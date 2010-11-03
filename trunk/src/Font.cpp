#include "Font.h"

#include <cmath>
#include "CFontMgr.h"
#include "macros.h"
void Font::render(const vec2d& pos,  const double size, const std::wstring& text){
  glPushMatrix();
  glTranslatef(pos.x,size+pos.y,0.f);
  glScalef(size/_size,-size/_size,1.f);
  _font->Render(text.c_str());
  glPopMatrix();
}

Font::Font(FTGLTextureFont* font, const wstring& name, const double size){
  _name=name;
  _size=size;
  _font=font;
}

Font::~Font(){
  delete _font;
}
