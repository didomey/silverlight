#include<sstream>
#include<algorithm>
#include<array>
#include<locale>
#include <codecvt>
#include<Shared/Core/Logging.h>
#include "strop.h"


template<typename T, typename Container, typename Predecate>
T &findClosestMatch(const std::string &matchVal, Container &list, Predecate pred) {
    uint32_t currentBestValue = 0;

    T &currentBestMatch = list.front();

    for (T &elem: list) {
        uint32_t currentVal = calcStringMatchRating(matchVal, pred(elem));

        if (currentBestValue < currentVal) {
            currentBestValue = currentVal;
            currentBestMatch = elem;
        }
    }

    return currentBestMatch;
}

template<typename T>
inline std::string to_string_with_precision(const T &a_value, int n) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

inline std::string u16string_to_string(std::u16string str) {
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(str);
}

inline std::string toHexString(uint32_t num) {
    std::stringstream stream;
    stream << std::hex << num;
    return stream.str();
}

constexpr std::array<char16_t, 10> digits = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
};

inline bool isUnsignedInt(const std::u16string &str) {
    return
            std::all_of(str.begin(), str.end(), [](const char16_t &c) -> bool {
                return std::any_of(digits.begin(), digits.end(), [&](const char16_t &d) -> bool {
                    return c == d;
                });
            });
}

inline uint32_t toUnsignedInt(const std::u16string &str) {
    return std::stoul(std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(str));
}
