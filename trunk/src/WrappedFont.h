#ifndef WRAPPEDFONT_H
#define WRAPPEDFONT_H


class WrappedFont
{
    public:
      inline void       render(const std::wstring& text, const double size, const vec2d& pos, const rgba& color);
      void              render(const vec2d& pos,  const double size,        const std::wstring& text);
      inline void       render(const double size, const std::wstring& text);
      inline void       render(const double size, const std::wstring& text, const rgba& color);
      double            width();
      void              doLoad();
    private:
                        Font(Font *font);
                        ~Font();
      Font              _font;
};

#endif // WRAPPEDFONT_H
