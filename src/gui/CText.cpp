#include "CText.h"
#include "CBaseEngine.h"

CText::CText(const vec2d& pos, const vec2d& size, const double height):
  CGuiPanel(pos,size),
  _textContainer(new CGuiPanel(pos,size)),
  _height(height),
  _font(engine->fonts->getFont("ARIALUNI.TTF", height)),
  _text()
{
  invalidate();
  addChild(_textContainer);
}

