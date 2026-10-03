#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <string>
#include <unordered_map>

#include "token.h"

class Calculator
{
public:
    Calculator();
    double calc(const char* str);

private:
    std::vector<std::string> sortFromInfix(const char* str) const;
    double calculate(const std::vector<std::string>& postfix_list) const;

    std::unordered_map<char, Token> m_token_map;
};



#endif // CALCULATOR_H
