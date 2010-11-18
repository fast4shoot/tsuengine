#ifndef VECOPBASE_H
#define VECOPBASE_H

#include <cmath>
#include "vecBase.h"

template<class T, int N, class Derived>
class vecOpBase : public vecBase<T,N,Derived>{
  public:
            vecOpBase();
            vecOpBase(const Derived& rhs);
    virtual ~vecOpBase(){};

    T dot(const Derived& b) const;
    Derived normalized() const;
    T length() const;
    T lengthSqr() const;

    bool operator==(Derived) const;
};



template<class T, int N, class Derived>
inline vecOpBase<T,N,Derived>::vecOpBase():
  vecBase<T,N,Derived>()
{}

template<class T, int N, class Derived>
inline vecOpBase<T,N,Derived>::vecOpBase(const Derived& rhs):
  vecBase<T,N,Derived>(rhs)
{}

template<class T, int N, class Derived>
inline T vecOpBase<T,N,Derived>::dot(const Derived& b) const{
  T sum=0.;
  for(int i=0;i<N;++i){
    sum+=this->data[i]*b.data[i];
  }
  return sum/(length()*b.length());
}

template<class T, int N, class Derived>
inline Derived vecOpBase<T,N,Derived>::normalized() const{
  return Derived(dynamic_cast<const Derived&>(*this))/length();
}

template<class T, int N, class Derived>
inline T vecOpBase<T,N,Derived>::lengthSqr() const{
  T sum=0.;
  for(int i=0;i<N;i++){
    sum+=vecOpBase<T,N,Derived>::data[i]*vecOpBase<T,N,Derived>::data[i];
  }
  return sum;
}

template<class T, int N, class Derived>
inline T vecOpBase<T,N,Derived>::length() const{
  return sqrt(length());
}


#endif // VECOPBASE_H
