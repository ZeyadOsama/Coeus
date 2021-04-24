//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP
#define COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP

#include <string>

namespace coeus {
    namespace dataunits {
        class RegularExpression {
        public:
            explicit RegularExpression(std::string &aKey, std::string &aVal);

            ~RegularExpression();

        private:
            std::string mKey;
            std::string mVal;
        };

    } // namespace dataunits
} // namespace coeus

#endif //COEUS_DATA_UNITS_REGULAR_EXPRESSION_HPP
