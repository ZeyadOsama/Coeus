//
// Created by Zeyad Osama on 25/04/2021.
//

#ifndef COEUS_UTILS_EXPRESSION_HELPER_HPP
#define COEUS_UTILS_EXPRESSION_HELPER_HPP

#include <string>

namespace coeus {
    namespace utils {

        class ExpressionHelper {
        public:
            /**
             * @brief Converts the incoming infix string to a postfix string
             *
             * @return a string with the postfix version of the infix input.
             */
            static
            std::string
            InfixToPostfix(std::unordered_set<std::string> aInputTable);

        private:
            ExpressionHelper() = default;
        };

    } // namespace utils
} // namespace coeus

#endif //COEUS_UTILS_EXPRESSION_HELPER_HPP
