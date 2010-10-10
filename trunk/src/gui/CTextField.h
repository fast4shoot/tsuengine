#ifndef CTEXTFIELD_H
#define CTEXTFIELD_H

#include "CGuiPanel.h"
#include "CLabel.h"

class CTextField : public CGuiPanel
{
  public:
                    CTextField(const vec2d& position, const vec2d& size, const std::wstring& text=L"");
    virtual void    onKeyboard(const std::wstring& string);
    virtual void    draw();
  protected:
    std::wstring    _string;
    CLabel*         _label;
};

#endif // CTEXTFIELD_H
