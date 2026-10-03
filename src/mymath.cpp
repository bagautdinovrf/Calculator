#include <cstring>
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "mymath.h"


using namespace std;

MyMath::MyMath()
{
    //
}


int MyMath::my_atoi( char str[] )
{
    int result = 0;

    while( *str != '\0') {
        result = result*10 + (*str-'0');
        ++str;
    }

return result;
}

/**
 * @brief MyMath::my_atod
 * Например число 54.87, с точкой
 * @param str - указатель на строку
 * @return - возвращаем число
 */
double MyMath::my_atod(const char* str)
{
    if (str == nullptr || *str == '\0')
        throw std::runtime_error("Empty number...");
    double result = 0;
    double fractional_place = 0.1;
    bool has_dot = false;
    bool has_digit = false;
    for (; *str != '\0'; ++str) {
        if (isDot(*str)) {
            if (has_dot)
                throw std::runtime_error("Multiple decimal points in number...");
            has_dot = true;
        } else if (isDigit(*str)) {
            has_digit = true;
            const int digit = *str - '0';
            if (has_dot) {
                result += digit * fractional_place;
                fractional_place *= 0.1;
            } else {
                result = result * 10 + digit;
            }
            if (!std::isfinite(result))
                throw std::runtime_error("Number out of range...");
        } else {
            throw std::runtime_error("Invalid character in number...");
        }
    }
    if (!has_digit)
        throw std::runtime_error("Number must contain a digit...");
    return result;
}

void MyMath::str_size(const char *str)
{
    cout << strlen(str) << endl;
    cout << sizeof (str) << endl;
    cout << sizeof (*str) << endl;
}

bool MyMath::isDigit( const char ch )
{
    if( (ch >='0' && ch <= '9') )
        return true;

return false;
}

bool MyMath::isDot( const char ch )
{
    if ( ch == '.' )
        return true;
return false;
}


bool MyMath::isDigitDot( const char ch )
{
    if( (ch >='0' && ch <= '9') || ch == '.' )
        return true;

return false;
}


