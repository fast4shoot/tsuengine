#ifndef VECBASE_H
#define VECBASE_H

#include <cmath>
#include <exception>
#include "macros.h"
#include "json/json.h"
#include "utils/stringUtils.h"

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

    bool operator==(const Derived& rhs) const;
    bool operator!=(const Derived& rhs) const;

    Derived floored() const;

    void fromJson(const json::mValue& val);
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

template<class T, int N, class Derived>
inline Derived vecBase<T,N,Derived>::floored() const{
  Derived ret;
  for(int i=0;i<N;i++){
    ret.data[i]=floor(data[i]);
  }
  return ret;
}

template<class T, int N, class Derived>
inline bool vecBase<T,N,Derived>::operator==(const Derived& rhs) const{
  for(int i=0;i<N;i++){
    if(data[i]!=rhs.data[i]){
      return false;
    }
  }
  return true;
}

template<class T, int N, class Derived>
inline bool vecBase<T,N,Derived>::operator!=(const Derived& rhs) const{
  return !operator==(rhs);
}

template<class T, int N, class Derived>
inline void vecBase<T,N,Derived>::fromJson(const json::mValue& val){
  const json::mArray& arr=val.get_array();
  if(arr.size()<N){
    throw std::runtime_error(sformat("Cannot parse %d-component vector from JSON: too few values",N));
  }
  for(int i = 0; i < N; i++){
    data[i] = arr[i].get_real();
  }
}

namespace json{
  template< class T, int N, class Derived >
  inline int extract(vecBase<T, N, Derived>& result, const mValue& value){
    result = result.fromJson(value);
  }
}

#endif // VECBASE_H
