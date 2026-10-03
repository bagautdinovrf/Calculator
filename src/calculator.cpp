#include <cmath>
#include <stack>
#include <stdexcept>

#include "calculator.h"
#include "mymath.h"

namespace {
bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ||
           ch == '\f' || ch == '\v';
}
}

Calculator::Calculator()
{
    m_token_map['('] = Token("(", 0, Token::OPEN_BRACKET);
    m_token_map[')'] = Token(")", 0, Token::CLOSE_BRACKET);
    m_token_map['+'] = Token('+', 2);
    m_token_map['-'] = Token('-', 2);
    m_token_map['*'] = Token('*', 3);
    m_token_map['/'] = Token('/', 3);
    m_token_map['^'] = Token('^', 4);
    m_token_map['~'] = Token('~', 5);
}

double Calculator::calc(const char* str)
{
    const auto postfix = sortFromInfix(str);
    return calculate(postfix);
}

std::vector<std::string> Calculator::sortFromInfix(const char* str) const
{
    if (str == nullptr)
        throw std::runtime_error("Null expression...");

    std::vector<std::string> postfix;
    std::stack<Token> operators;
    bool expect_operand = true;

    while (*str != '\0') {
        if (isWhitespace(*str)) {
            ++str;
            continue;
        }

        if (MyMath::isDigitDot(*str)) {
            if (!expect_operand)
                throw std::runtime_error("Operator expected between operands...");

            std::string number;
            bool has_dot = false;
            bool has_digit = false;
            while (MyMath::isDigitDot(*str)) {
                if (MyMath::isDot(*str)) {
                    if (has_dot)
                        throw std::runtime_error("Multiple decimal points in number...");
                    has_dot = true;
                } else {
                    has_digit = true;
                }
                number.push_back(*str++);
            }
            if (!has_digit)
                throw std::runtime_error("Number must contain a digit...");

            postfix.push_back(number);
            expect_operand = false;
            continue;
        }

        const auto found = m_token_map.find(*str);
        if (found == m_token_map.end())
            throw std::runtime_error("Invalid token: '" + std::string(1, *str) + "'...");
        const Token current = found->second;

        if (current.type() == Token::OPEN_BRACKET) {
            if (!expect_operand)
                throw std::runtime_error("Operator expected before '('...");
            operators.push(current);
        } else if (current.type() == Token::CLOSE_BRACKET) {
            if (expect_operand)
                throw std::runtime_error("Operand expected before ')'...");
            while (!operators.empty() && operators.top().type() != Token::OPEN_BRACKET) {
                postfix.push_back(operators.top().valueString());
                operators.pop();
            }
            if (operators.empty())
                throw std::runtime_error("Open bracket: '(' not found...");
            operators.pop();
            expect_operand = false;
        } else if (expect_operand) {
            if (*str != '-' && *str != '~')
                throw std::runtime_error("Operand expected...");
            // Prefix operators wait for their operand, including other prefix operators.
            operators.push(m_token_map.at('~'));
        } else {
            if (*str == '~')
                throw std::runtime_error("Operator expected before unary minus...");
            const bool right_associative = *str == '^';
            while (!operators.empty() && operators.top().type() == Token::OPERATOR &&
                   (operators.top().priority() > current.priority() ||
                    (!right_associative && operators.top().priority() == current.priority()))) {
                postfix.push_back(operators.top().valueString());
                operators.pop();
            }
            operators.push(current);
            expect_operand = true;
        }
        ++str;
    }

    if (expect_operand)
        throw std::runtime_error("Empty or incomplete expression...");

    while (!operators.empty()) {
        if (operators.top().type() == Token::OPEN_BRACKET)
            throw std::runtime_error("Closing bracket: ')' not found...");
        postfix.push_back(operators.top().valueString());
        operators.pop();
    }
    return postfix;
}

double Calculator::calculate(const std::vector<std::string>& postfix_list) const
{
    std::stack<double> numbers;
    for (const auto& token : postfix_list) {
        if (MyMath::isDigitDot(token.front())) {
            numbers.push(MyMath::my_atod(token.c_str()));
            continue;
        }

        const char op = token.front();
        if (op == '~') {
            if (numbers.empty())
                throw std::runtime_error("Unary operator requires an operand...");
            numbers.top() = -numbers.top();
            continue;
        }
        if (numbers.size() < 2)
            throw std::runtime_error("Binary operator requires two operands...");

        const double right = numbers.top();
        numbers.pop();
        const double left = numbers.top();
        numbers.pop();
        double result = 0;
        switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/':
            if (right == 0)
                throw std::runtime_error("Division by zero...");
            result = left / right;
            break;
        case '^': result = std::pow(left, right); break;
        default: throw std::runtime_error("Unknown operator...");
        }
        if (!std::isfinite(result))
            throw std::runtime_error("Non-finite arithmetic result...");
        numbers.push(result);
    }
    if (numbers.size() != 1)
        throw std::runtime_error("Expression must produce exactly one result...");
    return numbers.top();
}
