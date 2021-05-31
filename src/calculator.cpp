#include <cstring>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <cmath>

#include "calculator.h"
#include "mymath.h"


using namespace std;

Calculator::Calculator()
{
    m_token_map['('] = Token( "(", 0, Token::OPEN_BRACKET );
    m_token_map[')'] = Token( ")", 0, Token::CLOSE_BRACKET );

    m_token_map['+'] = Token( "+", 2 );
    m_token_map['-'] = Token( "-", 2 );

    m_token_map['*'] = Token( '*', 3 );
    m_token_map['/'] = Token( '/', 3 );

    m_token_map['^'] = Token( '^', 4 );
    m_token_map['~'] = Token( '~', 5 );
}

double Calculator::calc( const char *str )
{

    auto postfix = sortFromInfix(str);
    for ( const auto &s : postfix ) {
        cout << s << endl;
    }
    return calculate(postfix);
//    return double();
}

vector<string> Calculator::sortFromInfix( const char *str )
{
    vector<string> postfix;
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
            auto current_token = m_token_map[*str];
            if( current_token.isValid() )
            {
                if( current_token.type() == Token::OPERATOR ) {
                    if( oper_stack.empty() )
                        oper_stack.push( current_token );
                    else {
                        // Если оператор из стека круче чем текущий или равен, то вынимаем в список из стека пока на вершине стека не будет меньше
                        if( oper_stack.top().priority() >= current_token.priority() ) {
                            while( !oper_stack.empty() && oper_stack.top().priority() >= current_token.priority() ) {
                                postfix.push_back( oper_stack.top().valueString() );
                                oper_stack.pop();
                            }
                        }
                        // Если нет, то кладем в стек или все вынули
                        oper_stack.push( current_token );
                    }
                }
                // Если открываюшая скобка то кладет в стек
                else if( current_token.type() == Token::OPEN_BRACKET ) {
                    oper_stack.push( current_token );
                }
                // Если закрывающая то вынимаем все из стека в список пока не найдет открывающуюся
                else if( current_token.type() == Token::CLOSE_BRACKET ) {
                    while( !oper_stack.empty() && oper_stack.top().type() != Token::OPEN_BRACKET ) {
                        postfix.push_back( oper_stack.top().valueString() );
                        oper_stack.pop();
                    }
                    // Вынимаем открывающую скобку
                    if( !oper_stack.empty() && oper_stack.top().type() == Token::OPEN_BRACKET ) {
                        oper_stack.pop();
                    } else {
                        throw std::runtime_error("Open bracket: '(' not found...");
                    }
                } else {
                    throw std::runtime_error("Unknown token: '" + current_token.valueString() + "' ..." );
                }
            }
            else {
                string s;
                s.push_back(*str);
                throw std::runtime_error("Invalid token: '" + current_token.valueString() + "' current char: '" + s + "' ...");
            }

            // Увеличивам указатель на 1
            ++str;
        }
    } // end of while


    while( !oper_stack.empty() ) {
        auto top = oper_stack.top();
        if( top.type() == Token::OPEN_BRACKET ) {
            throw std::runtime_error("Absent token: ')'. But found token: '(' in stack...");
        }
        postfix.push_back( top.valueString() );
        oper_stack.pop();
    }

    return postfix;
}


double Calculator::calculate( vector<string> &postfix_list )
{
    stack< double > number_stack;

    for( unsigned int i = 0; i < postfix_list.size(); ++i )
    {
        auto &token = postfix_list.at(i);

        if( token.empty() )
            continue;

        if( MyMath::isDigitDot( token.front() ) ) {
            number_stack.push( MyMath::my_atod (token.data() ) );
        } else {

            auto oper = m_token_map[token.front()];
            if( oper.valueString().front() != '^' ) {
                double right = number_stack.top();
                number_stack.pop();
                double left = number_stack.top();
                number_stack.pop();

                switch ( oper.valueString().front() ) {
                    case '+':
                        number_stack.push( left + right );
                    break;

                    case '-':
                        number_stack.push( left - right );
                    break;

                    case '*':
                        number_stack.push( left * right );
                    break;

                    case '/':
                        if( right != 0 )
                            number_stack.push( left / right );
                        else
                            throw std::runtime_error("Division by zero...");
                    break;


                }
            } else {
                unsigned int power_count = 1;
                unsigned int pow_position = i + 2;
                while( pow_position < postfix_list.size() && "^" == postfix_list.at( pow_position ) ) {
                    ++power_count;
                    i = pow_position;
                    pow_position += 2;

                    token = postfix_list.at(i-1);

                    if( MyMath::isDigitDot( token.front() ) ) {
                        number_stack.push( MyMath::my_atod (token.data() ) );
                    }
                     else {
                        throw std::runtime_error("Bad token, number expected...");
                    }
                }

                for( unsigned int pwc = 0; pwc < power_count; ++pwc ) {
                    auto right = number_stack.top();
                    number_stack.pop();
                    auto left = number_stack.top();
                    number_stack.pop();
                    number_stack.push( pow( left, right ) );
                }

            } // token '^' cycle
        }

    }

    return number_stack.top();
}
