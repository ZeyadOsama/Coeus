//
// Created by Zeyad Osama on 25/04/2021.
//

#include <coeus/utils/ExpressionHelper.hpp>

#include <coeus/common/Definitions.hpp>

using namespace coeus::utils;
using namespace coeus::common;

std::string
ExpressionHelper::InfixToPostfix(std::unordered_set<std::string> aInputTable) {
    // Applying the range operation inorder to remove the range and replace it
    // with repetitive unions before converting to postfix.
    this->ApplyRangeOperationIfExists();

    std::string regex = this->GetValue();
    std::stack<std::string> infix_to_postfix_stack;
    std::string postfix = "";
    std::string input_identifier = "";
    bool input_acceptor = false;
    std::string input_detector = "";
    //iterating till the end of the regex
    for (int i = 0; i < regex.size(); i++) {
        // If the scanned character is an operand, add it to output string.
        if (!RegexHelper::IsReservedCharacter(regex[i]) || regex[i] == COEUS_REGEX_ESCAPE_CHAR) {
            while (!input_acceptor) {
                input_identifier += regex[i];
                for (const auto &element: aInputTable) {
                    if (input_identifier.compare(element) == 0) {
                        input_acceptor = true;
                        break;
                    }
                }

                i++;
            }
            //Check if the next character is an operator or end of string
            //If no then add a concatintaion operator between the 2 characters
            //else do nothing
            if (!RegexHelper::IsConcatenated(regex[i]) && i + 1 <= regex.size()) {
                regex.insert(i, "-", 1);
            }

            i--;
            postfix += input_identifier;
            input_acceptor = false;
            input_identifier = "";

        }
            // If the scanned character is an ‘(‘, push it to the stack.
        else if (regex[i] == COEUS_REGEX_PARENTHESES_LEFT)

            infix_to_postfix_stack.push(std::string(1, COEUS_REGEX_PARENTHESES_LEFT));

            // If the scanned character is an ‘)’, pop and to output string from the stack
            // until an ‘(‘ is encountered.
        else if (regex[i] == COEUS_REGEX_PARENTHESES_RIGHT) {

            std::string popped_character;
            while (!infix_to_postfix_stack.empty() && infix_to_postfix_stack.top()[0] != COEUS_REGEX_PARENTHESES_LEFT) {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
                postfix += popped_character;
            }
            if (infix_to_postfix_stack.top()[0] == COEUS_REGEX_PARENTHESES_LEFT) {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
            }
            if (regex[i + 1] == COEUS_REGEX_PARENTHESES_LEFT && i + 1 <= regex.size()) {
                regex.insert(i + 1, "-", 1);
            }
        }
            /* If an operator is scanned. */
        else {
            std::string popped_character;
            while (!infix_to_postfix_stack.empty() &&
                   RegexHelper::PrecedenceDecision(std::string(1, regex[i])) <=
                   RegexHelper::PrecedenceDecision(infix_to_postfix_stack.top())) {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
                postfix += popped_character;
            }
            if (regex[i] == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE && regex[i + 1] == '.') {
                postfix += COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE;
                regex.insert(i + 1, "-", 1);
            } else {
                infix_to_postfix_stack.push(std::string(1, regex[i]));
            }
            if (regex[i] == COEUS_REGEX_OPERATOR_POSITIVE_CLOSURE && regex[i + 1] == COEUS_REGEX_PARENTHESES_LEFT) {
                regex.insert(i + 1, "-", 1);
            }
        }

    }
    std::string popped_character;
    /* Pop all the remaining elements from the stack. */
    while (!infix_to_postfix_stack.empty()) {
        popped_character = infix_to_postfix_stack.top();
        infix_to_postfix_stack.pop();
        postfix += popped_character;
    }
    return postfix;
}