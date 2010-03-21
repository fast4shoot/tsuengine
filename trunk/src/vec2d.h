#ifndef VEC2D_H
#define VEC2D_H

class vec2d{
  public:
    double x;
    double y;
  
           vec2d();
           vec2d(double x, double y);
           vec2d(const vec2d& in);
           vec2d(vec2d& in);
    void   set(double x, double y);
    void   set(const vec2d& in);
  
    vec2d operator+(const vec2d& in) const;
    vec2d operator-(const vec2d& in) const;
    vec2d operator*(double in) const;
    vec2d operator/(double in) const;
    vec2d operator=(const vec2d& in);
    
    bool operator>(const vec2d& in) const;
    bool operator<(const vec2d& in) const;
    bool operator==(const vec2d& in) const;
    bool operator>=(const vec2d& in) const;
    bool operator<=(const vec2d& in) const;
  
    double length();
    double lengthSqr();
    vec2d  normalized();
};

inline vec2d vec2d::operator+(const vec2d& in) const {
  vec2d ret;
  ret.x=x+in.x;
  ret.y=y+in.y;
 return ret;
}
  
inline vec2d vec2d::operator-(const vec2d& in) const {
  vec2d ret;
  ret.x=x-in.x;
  ret.y=y-in.y;
  return ret;
}

inline vec2d vec2d::operator*(double in) const {
  vec2d ret;
  ret.x=x*in;
  ret.y=y*in;
  return ret;
}

inline vec2d vec2d::operator/(double in) const {
  vec2d ret;
  ret.x=x/in;
  ret.y=y/in;
  return ret;
}

inline vec2d vec2d::operator=(const vec2d& in){
  x=in.x;      
  y=in.y;
  return *this;
}

inline bool vec2d::operator>(const vec2d& in) const {
  return x>in.x && y>in.y;     
}

inline bool vec2d::operator<(const vec2d& in) const {
  return x<in.x && y<in.y;     
}

inline bool vec2d::operator==(const vec2d& in) const {
  return x==in.x && y==in.y;     
}

inline bool vec2d::operator>=(const vec2d& in) const {
  return operator>(in) || operator==(in);     
}

inline bool vec2d::operator<=(const vec2d& in) const {
  return operator<(in) || operator==(in);     
}

#endif
