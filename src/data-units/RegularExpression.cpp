//
// Created by Zeyad Osama on 24/04/2021.
//

#include <coeus/data-units/RegularExpression.hpp>

#include <coeus/common/Definitions.hpp>
#include <coeus/common/ReturnCodes.hpp>
#include <coeus/utils/RegexHelper.hpp>

#include <stack>

using namespace std;
using namespace coeus::dataunits;
using namespace coeus::common;
using namespace coeus::utils;


RegularExpression::RegularExpression(string &aKey, string &aVal)
        : mKey(aKey),
          mVal(aVal) {}

RegularExpression::~RegularExpression() = default;


/**
    Expands the range operator to the full fledged meaning of it in the RE.
    Operates on the RE value of the instance being called on.
*/
void RegularExpression::ApplyRangeOperationIfExists() {
    for (auto char_index = 0; char_index < this->mVal.length(); char_index++) {
        // do we got a range operator and it is not escaped using escape character ?
        if (this->mVal[char_index] == COEUS_REGEX_RANGE_EXTRA_OPERATION and
            this->mVal[char_index - 1] != COEUS_REGEX_ESCAPE_CHAR) {
            // initialize local variables to clean up code and make more readable.
            std::string replacement_string;
            char begin_range = this->mVal[char_index - 1];
            char end_range = this->mVal[char_index + 1];
            auto length_to_replace = 3;
            // generate the exploded range given in regex and save into a string to replace in the end.
            for (char range_index = begin_range; range_index <= end_range; range_index++) {
                if (range_index == begin_range)
                    replacement_string += {COEUS_REGEX_PARENTHESES_LEFT, range_index, COEUS_REGEX_OPERATOR_UNION};
                else if (range_index == end_range)
                    replacement_string += {range_index, COEUS_REGEX_PARENTHESES_RIGHT};
                else
                    replacement_string += {range_index, COEUS_REGEX_OPERATOR_UNION};
            }
            // replace three characters in this form ('begin_range' '-' 'end_range') with the exploded string generated above.
            this->mVal.replace(char_index - 1, length_to_replace, replacement_string);
        }
    }
}

/**
    Extracts the existing input symbols from the RE value contained in this instance being called on.
    @return vector<string> a list of all input symbols found in an RE.
*/
std::unordered_set<std::string> RegularExpression::ExtractInputSymbols() {
    std::unordered_set<std::string> input_symbols;
    for (int char_index = 0; char_index < this->mVal.length(); char_index++)
        if (RegexHelper::IsReservedCharacter(this->mVal[char_index]))
            // if an escape character, we need to take it and the next character as a whole symbol.
            if (this->mVal[char_index] == COEUS_REGEX_ESCAPE_CHAR)
                input_symbols.insert({this->mVal[char_index], this->mVal[++char_index]});
                // if a range operation, we have to consider characters from the left till the right of the character.
            else if (this->mVal[char_index] == COEUS_REGEX_RANGE_EXTRA_OPERATION)
                for (int range_index = this->mVal[char_index - 1] + 1;
                     range_index < this->mVal[char_index + 1]; range_index++)
                    input_symbols.emplace(1, range_index);
                // otherwise, its a operator we don't need to place as symbol.
            else
                continue;
            // otherwise, its a normal non reserved character that we need to add as symbol.
        else
            input_symbols.emplace(1, this->mVal[char_index]);
    return input_symbols;
}
