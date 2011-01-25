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

#define BUFFER_OFFSET(n) ((void*)((char*)NULL + n))


#endif
