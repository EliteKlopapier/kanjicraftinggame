#ifndef STRING_UTIL_H
#define STRINGUTIL_H

#include <codecvt>
#include <locale>

namespace util {

/**
 * @brief Converts a UTF-32 string to a UTF-8 string.
*/
std::string u32_to_u8(const std::u32string& str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(str);
}

/**
 * @brief Converts a UTF-8 string to a UTF-32 string.
*/
std::u32string u8_to_u32(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.from_bytes(str);
}

} // namespace util

#endif // STRING_UTIL_H
