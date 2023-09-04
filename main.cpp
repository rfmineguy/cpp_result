#include "Result.hpp"
#include <string>
#include <iostream>

result::Result<int,const char*> toHex(const std::string& input) {
  bool state = std::all_of(input.begin(), input.end(), ::isxdigit);
  return state ? result::Result<int, const char*>::Ok(std::stoi(input, nullptr, 16))
               : result::Result<int, const char*>::Err("Failed to convert input to hex");
}

int main() {
  auto result = toHex("314dah4");
  result
    .if_ok ([&](int s)         { std::cout << "Ok: "    << s << std::endl; })
    .if_err([&](const char* s) { std::cerr << "Error: " << s << std::endl; });
}
