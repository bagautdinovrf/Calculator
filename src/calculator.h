#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "token.h"

using namespace std;

class Calculator
{
public:
    Calculator();
    double calc(const char* str);

private:
     vector<string> sortFromInfix(const char* str );
     double calculate( vector<string> &postfix_list );


    unordered_map< char, Token > m_token_map;
};



#endif // CALCULATOR_H
