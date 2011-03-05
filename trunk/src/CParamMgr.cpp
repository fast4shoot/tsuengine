#include <vector>
#include <cstdlib>
#include "CParamMgr.h"
#include "datatypes.h"
#include "exceptions.h"

/*
void CParamMgr::linkVariableToParam(void *memPointer,const std::string name){
  entParam* param=new entParam;
  param->memPointer=memPointer;
  param->name=name;
  params.push_back(param);
}

void CParamMgr::linkVariableToParam(void *memPointer,const char* name){
  entParam* param=new entParam;
  param->memPointer=memPointer;
  param->name.assign(name);
  params.push_back(param);
}

std::string CParamMgr::getStringParam(std::string name){
  int size=params.size();
  entParam *param;
  for(int i=0;i<size;i++){
    param=params.at(i);
    if(param->name == name){
      return param->name;
	}
  }
  throw ParameterNonExistant(name);
}

double CParamMgr::getDoubleParam(std::string name){
  return atof(getStringParam(name).c_str());
}

int CParamMgr::getIntParam(std::string name){
  return atoi(getStringParam(name).c_str());
}

*/
