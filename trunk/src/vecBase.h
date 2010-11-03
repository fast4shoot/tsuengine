#ifndef VECBASE_H
#define VECBASE_H

#include "macros.h"

template<class T, int N, class Derived>
class vecBase
{
  public:
            vecBase();
            vecBase(const Derived& rhs);
    virtual ~vecBase() {}

    Derived& operator=(const Derived& rhs);

    Derived& operator+=(const Derived& rhs);
    Derived& operator-=(const Derived& rhs);
    Derived& operator*=(const T& rhs);
    Derived& operator/=(const T& rhs);

    const Derived operator+(const Derived& rhs) const;
    const Derived operator-(const Derived& rhs) const;
    const Derived operator*(const T& rhs) const;
    const Derived operator/(const T& rhs) const;
  protected:
    T data[N];
  private:
};



template<class T, int N, class Derived>
inline vecBase<T,N,Derived>::vecBase(){
  for(int i=0;i<N;i++){
    data[i]=0.;
  }
}

template<class T, int N, class Derived>
inline vecBase<T,N,Derived>::vecBase(const Derived& rhs){
  for(int i=0;i<N;i++){
    data[i]=rhs.data[i];
  }
  //MSGBOX(L"vecBase::vecBase()");
}

template<class T, int N, class Derived>
inline Derived& vecBase<T,N,Derived>::operator=(const Derived& rhs){
  for(int i=0;i<N;i++){
    data[i]=rhs.data[i];
  }
  //MSGBOX(L"vecBase::operator=");
  return dynamic_cast<Derived&>(*this);
}

template<class T, int N, class Derived>
inline Derived& vecBase<T,N,Derived>::operator+=(const Derived& rhs){
  for(int i=0;i<N;i++){
    data[i]+=rhs.data[i];
  }
  return dynamic_cast<Derived&>(*this);
}

template<class T, int N, class Derived>
inline Derived& vecBase<T,N,Derived>::operator-=(const Derived& rhs){
  for(int i=0;i<N;i++){
    data[i]-=rhs.data[i];
  }
  return dynamic_cast<Derived&>(*this);
}

template<class T, int N, class Derived>
inline Derived& vecBase<T,N,Derived>::operator*=(const T& rhs){
  for(int i=0;i<N;i++){
    data[i]*=rhs;
  }
  return dynamic_cast<Derived&>(*this);
}

template<class T, int N, class Derived>
inline Derived& vecBase<T,N,Derived>::operator/=(const T& rhs){
  for(int i=0;i<N;i++){
    data[i]/=rhs;
  }
  return dynamic_cast<Derived&>(*this);
}

template<class T, int N, class Derived>
inline const Derived vecBase<T,N,Derived>::operator+(const Derived& rhs) const{
  return (Derived(dynamic_cast<const Derived&>(*this)) += rhs);
}

template<class T, int N, class Derived>
inline const Derived vecBase<T,N,Derived>::operator-(const Derived& rhs) const{
  return (Derived(dynamic_cast<const Derived&>(*this)) -= rhs);
}

template<class T, int N, class Derived>
inline const Derived vecBase<T,N,Derived>::operator*(const T& rhs) const{
  return (Derived(dynamic_cast<const Derived&>(*this)) *= rhs);
}

template<class T, int N, class Derived>
inline const Derived vecBase<T,N,Derived>::operator/(const T& rhs) const{
  return (Derived(dynamic_cast<const Derived&>(*this)) /= rhs);
}

#endif // VECBASE_H
