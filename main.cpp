#include "Result.hpp"
#include <string>
#include <iostream>

result::Result<int,const char*> toHex(const std::string& input) {
  // Size check
  if (input.size() > sizeof(int)) 
    return result::Result<int, const char*>::Err("Input out of range");

  // Valid character check
  bool state = std::all_of(input.begin(), input.end(), ::isxdigit);

  // Conversion / Failed conversion
  return state ? result::Result<int, const char*>::Ok(std::stoi(input, nullptr, 16))
               : result::Result<int, const char*>::Err("Failed to convert input to hex");
}

int main() {
  auto result = toHex("ffffffff");
  result
    .if_ok ([&](int s)         { std::cout << "Ok: "    << s << std::endl; })
    .if_err([&](const char* s) { std::cerr << "Error: " << s << std::endl; });

  std::string input;
  while (1) {
    std::cin >> input;
    auto result = toHex(input);
    if (result.is_ok()) break;
  }
  std::cout << "Valid: " << input << std::endl;

}
