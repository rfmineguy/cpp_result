#include "Result.hpp"
#include <string>
#include <iostream>

result::Result<int,const char*> toHex(const std::string& input) {
  bool state = std::all_of(input.begin(), input.end(), ::isxdigit);
  return state ? result::Ok<int, const char*>(std::stoi(input, nullptr, 16))
               : result::Err<int, const char*>("Failed to convert input to hex");
}

int main() {
  result::Result<int, const char*> result = toHex("3144");
  result.if_ok ([&](int s)         { std::cout << "Ok: "    << s << std::endl; });
  result.if_err([&](const char* s) { std::cerr << "Error: " << s << std::endl; });
}
