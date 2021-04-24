//
// Created by Zeyad Osama on 24/04/2021.
//

#include <coeus/lex/parsers/LanguageParser.hpp>

#include <coeus/data-units/RegularExpression.hpp>
#include <coeus/common/ReturnCodes.hpp>
#include <coeus/common/Definitions.hpp>
#include <coeus/utils/StringHelper.hpp>

#include <fstream>

using namespace coeus::parsers;
using namespace coeus::dataunits;
using namespace coeus::common;
using namespace coeus::utils;


LanguageParser::LanguageParser(std::string &aFilePath)
        : mFilePath(aFilePath),
          mIsParsed(false) {}

LanguageParser::~LanguageParser() = default;

int
LanguageParser::Parse() {
    int rc = COEUS_RC_FAILURE;

    std::ifstream f(this->mFilePath);
    if (f.is_open()) {
        std::string rule;
        while (getline(f, rule))
            if (rule[0] == COEUS_INDICATOR_KEYWORD || rule[0] == COEUS_INDICATOR_PUNCTUATION)
                this->HandlerKeywordAndPunctuation(rule);
            else
                this->HandlerRegularExpression(rule);
        f.close();
        rc = COEUS_RC_SUCCESS;
    }
    return rc;
}

int
LanguageParser::HandlerKeywordAndPunctuation(std::string aRule) {
    return COEUS_RC_SUCCESS;
}

int
LanguageParser::HandlerRegularExpression(std::string aRule) {
    return COEUS_RC_SUCCESS;
}

int
LanguageParser::UpdateExpressionsAndInputTable(std::string regex_name, std::string regex_value) {
    return COEUS_RC_SUCCESS;
}