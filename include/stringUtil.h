#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <codecvt>
#include <locale>
#include <vector>

namespace util {

/**
 * @brief Converts a UTF-32 string to a UTF-8 string.
*/
extern std::string u32_to_u8(const std::u32string& str);

/**
 * @brief Converts a UTF-8 string to a UTF-32 string.
*/
extern std::u32string u8_to_u32(const std::string& str);

/**
 * @brief Splits a string by a delimiter.
*/
template <typename chartype>
std::vector<std::basic_string<chartype>> split(const std::basic_string<chartype>& str, chartype delimiter) {
    std::vector<std::basic_string<chartype>> result;
    std::basic_string<chartype> current;
    for (chartype c : str) {
        if (c == delimiter) {
            result.push_back(current);
            current.clear();
        }
        else {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}

} // namespace util

#endif // STRING_UTIL_H
