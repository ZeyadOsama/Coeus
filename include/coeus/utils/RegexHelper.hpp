//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_UTILS_REGEX_HELPER_HPP
#define COEUS_UTILS_REGEX_HELPER_HPP

#include <string>

namespace coeus {
    namespace utils {

        class RegexHelper {
        public:
            static bool
            IsReservedCharacter(char aChar);

            /**
             * @brief Checks if a character is possibly concatenated or not.
             *
             * @return boolean indicating the concatenation possibility.
             */
            static bool
            IsConcatenated(char aChar);

            /**
             * @brief Checks if the the aChar is not an operand.
             *
             * @return boolean indicating whether the aChar is an operand or not.
             */
            static bool
            IsNotOperator(char aChar);

            /**
             * @brief Decides which operator has a higher precedence and assigns a value for each operator.
             * The higher the value the higher the priority
             *
             * @return int representing the precedence priority.
             */
            static int
            PrecedenceDecision(std::string aOperatorSymbol);

        private:
            RegexHelper() = default;
        };

    } // namespace utils
} // namespace coeus

#endif //COEUS_UTILS_REGEX_HELPER_HPP
