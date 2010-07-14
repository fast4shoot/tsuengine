#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "GLFT_Font.hpp"
#include "macros.h"

CLabel::CLabel(const vec2d& position, const vec2d& size):
CGuiPanel(position,size)
{
  init();
}

CLabel::CLabel(const vec2d& position, const vec2d& size, const std::string& text):
CGuiPanel(position,size)
{
  init();
  _text=text;
}

void CLabel::init(){
  MSGBOX("CLabel::init()");
  _text="";
  _height=1;
  _font=new FTGLPixmapFont("Arial.ttf");
  MSGBOX("font vytvoren");
	_font->FaceSize(_height);
	MSGBOX("nastavena velikost");
}

void CLabel::draw(){
  MSGBOX("CLabel::draw()");
  glEnable(GL_TEXTURE_2D);
  //glColor4f(fgColor);
  _font->Render(_text.c_str());
  glDisable(GL_TEXTURE_2D);
}

void CLabel::updateFont(){
}

