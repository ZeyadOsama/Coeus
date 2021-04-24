//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_UTILS_STRING_HELPER_HPP
#define COEUS_UTILS_STRING_HELPER_HPP

#include <string>
#include <vector>

namespace coeus {
    namespace utils {

        class StringHelper {
        public:
            /**
             * @brief Removes trailing and starting spaces from a string.
             *
             * @param[in,out] aStr the string to remove from.
             *
             * @note Algorithm occurs in place.
             */
            static void
            TrimBothEnds(std::string &aStr);

            /**
             * @brief Removes the first and last chars whatever their value from a string.
             *
             * @param[in,out] aStr the string to remove from.
             *
             * @note Algorithm occurs in place.
             */
            static void
            StripFirstAndLastChars(std::string &aStr);

            /**
             * @brief Removes all spaces in every position from a string.
             *
             * @param[in,out] aStr the string to remove from.
             *
             * @note Algorithm occurs in place.
             */
            static void
            RemoveAllSpaces(std::string &aStr);

            static void
            RemoveExtraSpaces(std::string &aStr);

            /**
             * @brief Splits a string on any given aDelimiter character into a vector of tokens.
             *
             * @param[in] aStr the string to operate on.
             *
             * @return vector<string> the tokens resulted from the split of the string.
             */
            static std::vector<std::string>
            SplitOnDelimiter(const std::string &aStr, char aDelimiter);

            static std::vector<std::string>
            SplitOnFirstOfDelimiters(const std::string &aStr, const std::string &aDelimiter);

            static std::vector<std::string>
            SplitOnStringDelimiter(const std::string &aStr, const std::string &aDelimiter);


            /**
             * @brief A Generic Comparable Function that works on pairs and defines comparability 
             * based on first element's length.
             * 
             * @param[in] aSrc the first pair in comparison.
             *
             * @param[in] aDst the second pair in comparison.
             *
             * @return bool aSrc boolean that is true if the first pair is larger and false otherwise.
            */
            template<class T>
            static bool
            ComparePairsAccordingToFirstLength(const std::pair<T, T> &aSrc, const std::pair<T, T> &aDst);

            template<typename T>
            static std::vector<T *>
            ConvertFrom(std::vector<T> &aSrc);

        private:
            StringHelper() = default;
        };

    } // namespace utils
} // namespace coeus


#endif //COEUS_UTILS_STRING_HELPER_HPP
