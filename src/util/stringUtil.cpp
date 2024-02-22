#include "stringUtil.h"
#include <sstream>

namespace util {

std::string u32_to_u8(const std::u32string& str)  {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(str);
}

std::u32string u8_to_u32(const std::string& str)  {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.from_bytes(str);
}

char32_t unicodeToChar(const std::string& unicode) {
    return std::stoi(unicode.substr(2), nullptr, 16);
}

std::string charToUnicode(char32_t c) {
    std::stringstream ss;
    ss << std::hex << c;
    return "U+" + ss.str();
}

} // namespace util