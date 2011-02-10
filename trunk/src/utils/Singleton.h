#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstring>

template<class T>
class Singleton
{
  public:
    static T* instance();
  protected:
    static T* m_instance;
};

template<class T>
T* Singleton<T>::m_instance = NULL;

template<class T>
T* Singleton<T>::instance(){
  if(!m_instance){
    m_instance = new T();
  }
  return m_instance;
}

#endif // SINGLETON_H
