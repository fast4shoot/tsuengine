#ifndef PISKVORKA_H
#define PISKVORKA_H
#include "WhiteBox.h"

extern bool hrac;

class Piskvorka : public WhiteBox{  
  public:    
    
    Piskvorka(double x, double y, double w, double h);
    bool onClick(const vec2d& position, MouseButton button);
    bool isSet;
};

#endif
