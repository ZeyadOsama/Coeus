//
// Created by Zeyad Osama on 24/04/2021.
//

#include <coeus/lex/parsers/LanguageParser.hpp>

#include <coeus/data-units/RegularExpression.hpp>
#include <coeus/common/ReturnCodes.hpp>
#include <coeus/common/Definitions.hpp>
#include <coeus/utils/StringHelper.hpp>

#include <fstream>
#include <algorithm>

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
    // set the name of the regex according to one of the two types in this handler.
    //std::string regex_name = (aRule[0]==KEYWORD_INDICATOR) ? KEYWORD_NAME : PUNCTUATION_NAME;
    // remove expression type indicators ([,],{,}) and trim aRule.
    StringHelper::StripFirstAndLastChars(aRule);
    StringHelper::TrimBothEnds(aRule);
    // for each keyword/punctuation in the array defined, lets make a regex and populate the input table with new symbols!
    for (auto &it : StringHelper::SplitOnDelimiter(aRule, ' ')) {
        this->UpdateExpressionsAndInputTable(it, it);
    }
    return COEUS_RC_SUCCESS;
}

int
LanguageParser::HandlerRegularExpression(std::string aRule) {
    // Spaces are neglected and are optional by our definition of rules.
    StringHelper::RemoveAllSpaces(aRule);
    // Find ':' or '=' position and whomever appears first of them defines whether this is definition or expression.
    auto assign_pos = aRule.find_first_of(COEUS_INDICATOR_RULE_ASSIGN);
    for (auto &definition: this->mDefinitions) {
        // For each definition that exists inside this expression/definition
        // we replace the definition name with its value.
        // We pass the second param (assign_pos+1) to reduce the search space
        // for the function to start looking after assign.
        auto definition_pos = aRule.find(definition.first, assign_pos + 1);
        while (definition_pos != std::string::npos) {
            aRule.replace(definition_pos, definition.first.length(), "(" + definition.second + ")");
            definition_pos = aRule.find(definition.first, assign_pos + 1);
        }
    }
    // Assign regex's name and value according to the assign indicator position.
    std::string regex_name = aRule.substr(0, assign_pos);
    std::string regex_value = aRule.substr(assign_pos + 1);

    // Lets make a regex and populate the input table with new symbols.
    if (aRule[assign_pos] == COEUS_INDICATOR_REGULAR_EXP)
        UpdateExpressionsAndInputTable(regex_name, regex_value);
    else {
        this->mDefinitions.emplace_back(regex_name, regex_value);
        // Sort the definitions according to the length of the name to avoid
        // longer subsets of same names problem (e.g. digits overlap digit).
        std::sort(this->mDefinitions.begin(),
                  this->mDefinitions.end(),
                  StringHelper::ComparePairsAccordingToFirstLength<std::string>);
    }
    return COEUS_RC_SUCCESS;
}

int
LanguageParser::UpdateExpressionsAndInputTable(std::string regex_name, std::string regex_value) {
    RegularExpression regex = RegularExpression(regex_name, regex_value);
    this->mExpressions.push_back(regex);
    std::unordered_set<std::string> symbols = regex.ExtractInputSymbols();
    std::copy(symbols.begin(), symbols.end(), std::inserter(mInputTable, mInputTable.end()));
    return COEUS_RC_SUCCESS;
}