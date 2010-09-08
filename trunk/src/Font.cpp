#include "Font.h"

#include <cmath>
#include "CFontMgr.h"
#include "macros.h"
void Font::render(const vec2d& pos,  const double size, const std::wstring& text){
  if(size>_size){;
    _mgr->loadFont(_name, (int)ceil(size));
  }
  glPushMatrix();
  glTranslatef(pos.x,size+pos.y,0.f);
  glScalef(size/_size,-size/_size,1.f);
  _font->Render(text.c_str());
  glPopMatrix();
}

Font::Font(CFontMgr* mgr, const wstring& name){
  _mgr=mgr;
  _size=-1;
  _font=NULL;
  _name=name;
}
