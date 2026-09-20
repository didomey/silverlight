#include"strop.h"
#include<algorithm>

/*size_t
strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}*/

std::vector<std::string> splitString(const std::string &str, std::initializer_list<char> delimiters) {
    std::vector<std::string> ret;

    std::string remainingStr = str;

    while (true) {
        unsigned int endCpy = 0xFFFFFFFF;

        for (char c: delimiters)
            endCpy = std::min(endCpy, remainingStr.find(c));

        if (endCpy == std::numeric_limits<unsigned int>::max()) {
            if (!remainingStr.empty())
                ret.push_back(remainingStr);
            return ret;
        }

        ret.push_back(remainingStr.substr(0, endCpy));
        remainingStr = remainingStr.substr(endCpy + 1);
    }
}

uint32_t reverseOneDirectionLevenshteinDistanceCstr(const char *input, const char *compair) {
    if (*input == ' ' ||
        *input == '-' ||
        *input == '_')
        return reverseOneDirectionLevenshteinDistanceCstr(input + 1, compair);

    if (*compair == ' ' ||
        *compair == '-' ||
        *compair == '_')
        return reverseOneDirectionLevenshteinDistanceCstr(input, compair + 1);

    if (strlen(input) == 0 ||
        strlen(compair) == 0)
        return 0;

    if (*input == std::tolower(*compair)) {
        if (std::tolower(*compair) != *compair)
            return 2 + reverseOneDirectionLevenshteinDistanceCstr(input + 1, compair + 1);
        else
            return std::max(
                    1 + reverseOneDirectionLevenshteinDistanceCstr(input + 1, compair + 1),
                    reverseOneDirectionLevenshteinDistanceCstr(input, compair + 1)
            );
    }
    return reverseOneDirectionLevenshteinDistanceCstr(input, compair + 1);
}

uint32_t calcStringMatchRating(std::string input, std::string compair) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });


    return reverseOneDirectionLevenshteinDistanceCstr(input.c_str(), compair.c_str());
}

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::optional<int> stringToInt(const std::string& str) {
	try {
		int num = std::stoi(str);
		return num;
	} catch (const std::exception& e) {
		return std::nullopt;
	}
}

std::vector<short> stringToShortArray(const std::string& str) {
    std::vector<short> result;
    for (char c : str) {
        result.push_back(static_cast<short>(c));
    }
    return result;
}
