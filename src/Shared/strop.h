#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// size_t strlen(const char *str);

template <typename T, typename Container, typename Predecate>
T &findClosestMatch(const std::string &matchVal, Container &list,
                    Predecate pred);

uint32_t calcStringMatchRating(std::string str1, std::string str2);

template <typename T>
inline std::string to_string_with_precision(const T &a_value, int n = 2);

inline std::string u16string_to_string(std::u16string str);

inline std::string toHexString(uint32_t num);

inline bool isUnsignedInt(const std::u16string &str);

inline uint32_t toUnsignedInt(const std::u16string &str);

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

std::optional<int> stringToInt(const std::string &str);

std::vector<short> stringToShortArray(const std::string& str);

#include "strop.inl"
