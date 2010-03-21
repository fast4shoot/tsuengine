#include <exception>
#include "exceptions.h"

ParameterNonExistant::ParameterNonExistant(std::string param): std::runtime_error("ParameterNonExistant: "+param){}
WrongParameterType::WrongParameterType(std::string prm,std::string readType): std::runtime_error("WrongParameterType: "+prm+" is not "+readType){}
CodeFailure::CodeFailure(std::string line): std::runtime_error("The following code failed:\n"+line){}
GeneralFailure::GeneralFailure(std::string error): std::runtime_error("A general failure occured:\n"+error){}
