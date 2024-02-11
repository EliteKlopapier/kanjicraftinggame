#include "stringUtil.h"

namespace util {

std::string u32_to_u8(const std::u32string& str)  {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(str);
}

std::u32string u8_to_u32(const std::string& str)  {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.from_bytes(str);
}

} // namespace util