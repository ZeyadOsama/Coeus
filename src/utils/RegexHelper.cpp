//
// Created by Zeyad Osama on 24/04/2021.
//

#include <coeus/utils/RegexHelper.hpp>

#include <coeus/common/Definitions.hpp>

using namespace coeus::utils;
using namespace coeus::common;


bool
RegexHelper::IsReservedCharacter(char aChar) {
    return (aChar == COEUS_REGEX_PARENTHESES_LEFT || aChar == COEUS_REGEX_PARENTHESES_RIGHT
            || aChar == COEUS_REGEX_ESCAPE_CHAR
            || aChar == COEUS_REGEX_OPERATOR_KLEENE_CLOSURE
            || aChar == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE
            || aChar == COEUS_REGEX_OPERATOR_UNION
            || aChar == COEUS_REGEX_OPERATOR_CONCAT);
}

bool
RegexHelper::IsConcatenated(char aChar) {
    auto rc = false;
    if (aChar == COEUS_REGEX_OPERATOR_UNION || aChar == COEUS_REGEX_OPERATOR_KLEENE_CLOSURE ||
        aChar == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE ||
        aChar == COEUS_REGEX_PARENTHESES_RIGHT) {
        rc = true;
    }
    return rc;
}

bool
RegexHelper::IsNotOperator(char aChar) {
    auto rc = true;
    if (aChar == COEUS_REGEX_OPERATOR_UNION || aChar == COEUS_REGEX_OPERATOR_KLEENE_CLOSURE ||
        aChar == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE ||
        aChar == COEUS_REGEX_OPERATOR_CONCAT || aChar == COEUS_REGEX_PARENTHESES_LEFT ||
        aChar == COEUS_REGEX_PARENTHESES_RIGHT) {
        rc = false;
    }
    return rc;
}

int
RegexHelper::PrecedenceDecision(std::string aOperatorSymbol) {
    auto rc = -1;
    if (aOperatorSymbol[0] == COEUS_REGEX_OPERATOR_KLEENE_CLOSURE ||
        aOperatorSymbol[0] == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE) {
        rc = 3;
    } else if (aOperatorSymbol[0] == COEUS_REGEX_OPERATOR_CONCAT) {
        rc = 2;
    } else if (aOperatorSymbol[0] == COEUS_REGEX_OPERATOR_UNION) {
        rc = 1;
    }
    return rc;
}
