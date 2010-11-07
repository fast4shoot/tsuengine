#ifndef FONTBASE_H
#define FONTBASE_H

#include <string>
#include "datatypes.h"

class FontBase{
  public:
    void            render(const std::wstring& text, const double size, const rgba& color);
    void            render(const std::wstring& text, const double size, const vec2d& pos, const rgba& color);
    void            render(const std::wstring& text, const double size);
    void            render(const std::wstring& text, const double size, const vec2d& pos);
                    FontBase(const double size);
        virtual     ~FontBase(){};
  protected:
    virtual void    renderImpl(const std::wstring& text)=0;
    int             _size;
};



#endif // FONTBASE_H
