//
// Created by Zeyad Osama on 24/04/2021.
//

#ifndef COEUS_LEX_PARSERS_LANGUAGE_PARSER_HPP
#define COEUS_LEX_PARSERS_LANGUAGE_PARSER_HPP

#include <coeus/data-units/RegularExpression.hpp>

#include <string>
#include <unordered_set>
#include <vector>

namespace coeus {
    namespace parsers {
        class LanguageParser {
        public:
            explicit LanguageParser(std::string &aFilePath);

            ~LanguageParser();

            int
            Parse();

            inline const std::vector<dataunits::RegularExpression> &
            GetExpressions() const { return this->mExpressions; }

            const std::unordered_set<std::string> &
            GetInputTable() const { return this->mInputTable; }

        private:
            /**
             * @brief Knows its way through the keywords and punctuations rules that exist
             * in file and parses them into RE and Input Syms.
             *
             * @param aRule The rule read from file as string.
             */
            int
            HandlerKeywordAndPunctuation(std::string aRule);

            /**
             * @brief Unlike his brother keyword handler, that RE handler knows his way through other
             * types of rules and again parses them into REs and Input Syms.
             *
             * @param aRule The aRule read from file as string.
            */
            int
            HandlerRegularExpression(std::string aRule);

            int
            UpdateExpressionsAndInputTable(std::string regex_name, std::string regex_value);

        private:
            std::string mFilePath;
            bool mIsParsed;
            std::unordered_set<std::string> mInputTable;
            std::vector<dataunits::RegularExpression> mExpressions;
            std::vector<std::pair<std::string, std::string>> mDefinitions;
        };

    } // namespace parsers
} // namespace coeus

#endif //COEUS_LEX_PARSERS_LANGUAGE_PARSER_HPP
