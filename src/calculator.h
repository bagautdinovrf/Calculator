#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <list>
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
     list<string> sortFromInfix(const char* str );


    unordered_map< char, Token > mTokenMap;
};



#endif // CALCULATOR_H
