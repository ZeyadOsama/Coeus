//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP
#define COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP

#include <string>
#include <unordered_set>

namespace coeus {
    namespace dataunits {
        class RegularExpression {
        public:
            explicit RegularExpression(std::string &aKey, std::string &aVal);

            ~RegularExpression();

        public:
            inline const std::string &
            GetName() const { return this->mKey; };

            inline const std::string &
            GetValue() const { return this->mVal; };

            void
            ApplyRangeOperationIfExists();

            std::unordered_set<std::string>
            ExtractInputSymbols();

            /**
             * @brief Converts the incoming infix string to a postfix string
             *
             * @return a string with the postfix version of the infix input.
             */
            std::string
            InfixToPostfix(std::unordered_set<std::string> aInputTable);

        private:
            std::string mKey;
            std::string mVal;
        };

    } // namespace dataunits
} // namespace coeus

#endif //COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP
