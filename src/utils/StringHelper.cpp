//
// Created by Zeyad Osama on 24/04/2021.
//

#include <coeus/utils/StringHelper.hpp>

#include <algorithm>
#include <sstream>

using namespace coeus::utils;


void
StringHelper::TrimBothEnds(std::string &aStr) {
    const std::string &chars = "\t\n\v\f\r ";
    aStr.erase(aStr.find_last_not_of(chars) + 1);
    aStr.erase(0, aStr.find_first_not_of(chars));
}

void
StringHelper::StripFirstAndLastChars(std::string &aStr) {
    if (aStr.size() > 2) {
        aStr.erase(0, 1);
        aStr.erase(aStr.length() - 1);
    }
}

void
StringHelper::RemoveAllSpaces(std::string &aStr) {
    aStr.erase(std::remove(aStr.begin(), aStr.end(), ' '), aStr.end());
}

void
StringHelper::RemoveExtraSpaces(std::string &aStr) {
    bool seen_space = false;
    auto end{std::remove_if(aStr.begin(), aStr.end(),
                            [&seen_space](unsigned ch) {
                                bool is_space = std::isspace(ch);
                                std::swap(seen_space, is_space);
                                return seen_space && is_space;
                            })};
    if (end != aStr.begin() && std::isspace(static_cast<unsigned>(end[-1]))) {
        --end;
    }
    aStr.erase(end, aStr.end());
}

std::vector<std::string>
StringHelper::SplitOnDelimiter(const std::string &aStr, char aDelimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream s(aStr);
    while (std::getline(s, token, aDelimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string>
StringHelper::SplitOnFirstOfDelimiters(const std::string &aStr, const std::string &aDelimiter) {
    std::size_t current, previous = 0;
    std::vector<std::string> tokens;
    current = aStr.find_first_of(aDelimiter);
    while (current != std::string::npos) {
        std::string token = aStr.substr(previous, current - previous);
        tokens.push_back(token);
        previous = current + 1;
        current = aStr.find_first_of(aDelimiter, previous);
    }
    tokens.push_back(aStr.substr(previous, current - previous));
    return tokens;
}

std::vector<std::string>
StringHelper::SplitOnStringDelimiter(const std::string &aStr, const std::string &aDelimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    size_t delimiter_len = aDelimiter.length();
    std::string token;
    std::vector<std::string> tokens;

    while ((pos_end = aStr.find(aDelimiter, pos_start)) != std::string::npos) {
        token = aStr.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter_len;
        tokens.push_back(token);
    }
    tokens.push_back(aStr.substr(pos_start));
    return tokens;
}

template<class T>
bool
StringHelper::ComparePairsAccordingToFirstLength(const std::pair<T, T> &aSrc, const std::pair<T, T> &aDst) {
    return aSrc.first.length() > aDst.first.length();
}

template<typename T>
std::vector<T *>
StringHelper::ConvertFrom(std::vector<T> &aSrc) {
    std::vector<T *> target(aSrc.size());
    std::transform(aSrc.begin(), aSrc.end(), target.begin(), [](T &t) { return &t; });
    return target;
}