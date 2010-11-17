#ifndef FONTWRAPPED_H
#define FONTWRAPPED_H


#include "CBaseEngine.h"
#include "FontBase.h"
#include "Font.h"

class FontWrapped: public FontBase{
  public:
    FontWrapped(const std::wstring& fontFace, const double size, const double length);
    virtual ~FontWrapped();
  private:
    void            renderImpl(const std::wstring& text);
    FTSimpleLayout* _layout;
    Font*           _font;
    double          _length;
};

inline FontWrapped::FontWrapped(const std::wstring& fontFace, const double size, const double length):
  FontBase(size),
  _length(length),
  _layout(new FTSimpleLayout())
{
  _font=engine->fonts->getFont(fontFace,size);
  _layout->SetLineLength(_length);
  _layout->SetFont(_font->_font);
}

inline FontWrapped::~FontWrapped(){
  delete _layout;
}

inline void FontWrapped::renderImpl(const std::wstring& text){
  _layout->Render(text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
}


#endif // FONTWRAPPED_H
