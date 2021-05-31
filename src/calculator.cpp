#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <stdexcept>
#include <unordered_map>

#include "calculator.h"
#include "mymath.h"


using namespace std;

Calculator::Calculator()
{
    mTokenMap['('] = Token( "(", 0, Token::OPEN_BRACKET );
    mTokenMap[')'] = Token( ")", 0, Token::CLOSE_BRACKET );

    mTokenMap['+'] = Token( "+", 2 );
    mTokenMap['-'] = Token( "-", 2 );

    mTokenMap['*'] = Token( "*", 3 );
    mTokenMap['/'] = Token( "/", 3 );

    mTokenMap['^'] = Token( "^", 4 );
    mTokenMap['~'] = Token( "~", 5 );


//    for( const auto &token : mTokenMap ) {
//        cout << token.second->valueString() << token.second->priority() << endl;
//    }
}

double Calculator::calc( const char *str )
{
    double result = 0.0;

    auto postfix = sortFromInfix(str);

    for ( const auto &s : postfix ) {
        cout << s << endl;
    }

    return result;
}

list<string> Calculator::sortFromInfix( const char *str )
{
    list<string> postfix;
    stack< Token >  oper_stack;

    while( *str != '\0' ) {

        while ( *str == ' ' ) {
            ++str;
        }

        if( MyMath::isDigitDot(*str) ) {
            string num;
            while ( MyMath::isDigitDot( *str ) ) {

                int dot_count = 0;
                if( MyMath::isDot( *str ) ) {
                    ++dot_count;
                    if( dot_count > 1) {
                        throw std::runtime_error( "Floating point error..." );
                    }
                }

                num.push_back( *str );
                ++str;
            }

            postfix.push_back( num );
        }
        else {
            auto currentToken = mTokenMap[*str];
            if( currentToken.isValid() )
            {
                if( currentToken.type() == Token::OPERATOR ) {
                    if( oper_stack.empty() )
                        oper_stack.push( currentToken );
                    else {
                        // Если оператор из стека круче чем текущий или равен, то вынимаем в список из стека пока на вершине стека не будет меньше
                        if( oper_stack.top().priority() >= currentToken.priority() ) {
                            while( !oper_stack.empty() && oper_stack.top().priority() >= currentToken.priority() ) {
                                postfix.push_back( oper_stack.top().valueString() );
                                oper_stack.pop();
                            }
                        }
                        // Если нет, то кладем в стек или все вынули
                        oper_stack.push( currentToken );
                    }
                }
                // Если открываюшая скобка то кладет в стек
                else if( currentToken.type() == Token::OPEN_BRACKET ) {
                    oper_stack.push( currentToken );
                }
                // Если закрывающая то вынимаем все из стека в список пока не найдет открывающуюся
                else if( currentToken.type() == Token::CLOSE_BRACKET ) {
                    while( !oper_stack.empty() && oper_stack.top().type() != Token::OPEN_BRACKET ) {
                        postfix.push_back( oper_stack.top().valueString() );
                        oper_stack.pop();
                    }
                    // Вынимаем открывающую скобку
                    if( !oper_stack.empty() && oper_stack.top().type() == Token::OPEN_BRACKET ) {
                        oper_stack.pop();
                    } else {
                        throw std::runtime_error("OPEN_BRACKET '(' not found...");
                    }
                } else {
                    throw std::runtime_error("Unknown token: '" + currentToken.valueString() + "' ..." );
                }
            }
            else {
                string s;
                s.push_back(*str);
                throw std::runtime_error("Invalid token: '" + currentToken.valueString() + "' current char: '" + s + "' ...");
            }

            // Увеличивам указатель на 1
            ++str;
        }
    } // end of while


    while( !oper_stack.empty() ) {
        auto top = oper_stack.top();
        if( top.type() == Token::OPEN_BRACKET ) {
            throw std::runtime_error("Absent ). Found token: ( in stack...");
        }
        postfix.push_back( top.valueString() );
        oper_stack.pop();
    }

return postfix;
}

