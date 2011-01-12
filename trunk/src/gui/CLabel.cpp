#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "glew/glew.h"
#include "typedefs.h"

CLabel::CLabel(const vec2d& position, const vec2d& size, const String& text, ALIGN align):
CGuiPanel(position,size),
_text(text)
{
  allowKeyboardInput=false;
  _font=engine->fonts->getFont("ARIALUNI.TTF",getH());
}

void CLabel::draw(){
  setDrawColor(fgColor);
  _font->render(_text,getH());
}

