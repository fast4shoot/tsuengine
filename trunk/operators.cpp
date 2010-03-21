std::string operator+(const char *str1,const std::string &str2){
  std::string result;
  result.assign(str1);
  result.append(&str2);            
}

std::string operator+(const std::string &str1,const char *str2){
  std::string result;
  result.assign(&str1);
  result.append(str2);            
}

std::string operator+(const char *str1,const char *str2){
  std::string result;
  result.assign(str1);
  result.append(str2);            
}
