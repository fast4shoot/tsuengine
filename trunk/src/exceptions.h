#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>
#include <stdexcept>

class ParameterNonExistant : public std::runtime_error{
  public:
    ParameterNonExistant(std::string param);
};

class WrongParameterType : public std::runtime_error{
  public:
    WrongParameterType(std::string prm,std::string readType);
};

class CodeFailure : public std::runtime_error{
  public:
    CodeFailure(std::string line);
};

class GeneralFailure : public std::runtime_error{
  public:
    GeneralFailure(std::string error);
};
#endif
