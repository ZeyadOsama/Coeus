//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_COMMON_DEFINITIONS_HPP
#define COEUS_COMMON_DEFINITIONS_HPP

namespace coeus {
    namespace common {
 /**
 * @brief
 * The algebraic operators that can be applied on regular expressions
 * while evaluating the regex.
 *
 * While, concat operator doesn't have a definite indicator, '-' is used for it since
 * this is already reserved for range extra operation as a user extension and not a
 * algebraic operator.
 *
 * The range extra operation indicator is ensured to be replaced early before processing
 * an infix to postfix conversion.
 */
#define COEUS_REGEX_OPERATOR_UNION              '|'             /* Regex for union operator. */
#define COEUS_REGEX_OPERATOR_CONCAT             '-'             /* Regex for concat operator. */
#define COEUS_REGEX_OPERATOR_KLEENE_CLOSURE     '*'             /* Regex for Kleene closure operator. */
#define COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE   '+'             /* Regex for positive closure operator. */

#define COEUS_REGEX_PARENTHESES_LEFT            '('             /* Regex for left operator. */
#define COEUS_REGEX_PARENTHESES_RIGHT           ')'             /* Regex for right parentheses. */
#define COEUS_REGEX_RANGE_EXTRA_OPERATION       '-'             /* Regex for extra operation. */
#define COEUS_REGEX_ESCAPE_CHAR                 '\\'            /* Regex for escape character. */
#define COEUS_INDICATOR_KEYWORD                 '{'             /* Indicates the beginning of a keyword. */
#define COEUS_INDICATOR_PUNCTUATION             '['             /* Indicates the beginning of punctuation. */
#define COEUS_INDICATOR_REGULAR_EXP             ':'             /* Indicates the beginning of a regex. */
#define COEUS_INDICATOR_RULE_ASSIGN             ":="            /* Indicates the beginning of an assigment rule. */
#define COEUS_NAME_KEYWORD                      "Keyword"       /* Definition for keyword string. */
#define COEUS_NAME_PUNCTUATION                  "Punctuation"   /* Definition for punctuation string. */

    } // namespace common
} // namespace coeus

#endif //COEUS_COMMON_DEFINITIONS_HPP
