#include <cstring>
#include <iostream>

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
double MyMath::my_atod( char *str )
{
    double result = 0;


    while( *str != '.' && *str != '\0' ) {
        result = result*10 + (*str-'0');
        ++str;
    }

    // Возвращаем результат если дошли до конца строки
    if( *str == '\0' )
        return result;

    // Перешагиваем через точку
    ++str;

    int i = 1;
    while( *str != '\0') {
        //TODO: если встретили точку то exception -> Проверка на количество точек. Хотя в преобразовании в постфикс уже проверено
        result = result*10 + (*str-'0');
        ++str;
        i *= 10;
    }

    result = result / i;

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


