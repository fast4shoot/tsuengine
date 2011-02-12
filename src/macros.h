#ifndef MACROS_H
#define MACROS_H

#include <windows.h>
#include <cstddef>

#define LINKVARTOPARAM(lvtp_mem,lvtp_name) params.linkVariableToParam((void*)&lvtp_mem,lvtp_name)
#define MSGBOX(msg) MessageBoxA(NULL,msg,"Message",MB_OK)
#define HANDLEMSFAILURE(x) if(FAILED(x)){throw CodeFailure(#x);}
#define CLIPMINMAX(val,min,max) ( (val)>=(max)?(max):( (val)<=(min)?(min):(val) ) )
#define CLIPMIN(val,min) ((val)<=(min)?(min):(val))
#define CLIPMAX(val,max) ((val)>=(max)?(max):(val))

#define BUFFER_OFFSET(n) ((char*)NULL + n)

#define ENTITY_DESCRIPTOR(This, Base) \
class This##Descriptor: public Base##Descriptor{ \
  protected: \
    virtual CBaseEntity* createInstance(){ \
      return new This(); \
    } \
  public:

#define REGISTER_ENTITY(Entity) static bool Entity ## Registered = DescriptorList::instance()->registerDescriptor(new Entity ## Descriptor());


#endif
