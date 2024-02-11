#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <codecvt>
#include <locale>
#include <vector>
#include <utility>

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
 * @brief Converts a Unicode code point to the character it represents.
 * @param unicode The Unicode code point in the format U+<hex>.
*/
extern char32_t unicodeToChar(const std::string& unicode);

/**
 * @brief Splits a string by delimiters.
 * @param str The string to split.
 * @param delimiters A string with the delimiters to split the string by.
*/
template <typename chartype>
std::vector<std::basic_string<chartype>> split(const std::basic_string<chartype>& str, std::basic_string<chartype> delimiters) {
    std::vector<std::basic_string<chartype>> result;
    std::basic_string<chartype> current;
    for (chartype c : str) {
        if (delimiters.find(c) != std::basic_string<chartype>::npos) {
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

/**
 * @brief Finds all strings enclosed by a start and end character.
 * @param str The string to search.
 * @param start The start character.
 * @param end The end character.
 * @return A pair of a vector of strings enclosed by the start and end character and the remaining string.
*/
template <typename chartype>
std::pair<std::vector<std::basic_string<chartype>>, std::basic_string<chartype>> findEnclosedStrings(const std::basic_string<chartype>& str, chartype start, chartype end) {
    std::vector<std::basic_string<chartype>> result;
    std::basic_string<chartype> current;
    std::basic_string<chartype> remaining;
    bool inEnclosure = false;
    for (int i = 0; i < str.size(); i++) {
        chartype c = str[i];
        if (c == start) {
            inEnclosure = true;
            current.clear();
        }
        else if (c == end) {
            inEnclosure = false;
            result.push_back(current);
        }
        else if (inEnclosure) {
            current += c;
        }
        else {
            remaining += c;
        }
    }
    return {result, remaining};
}

} // namespace util

#endif // STRING_UTIL_H
