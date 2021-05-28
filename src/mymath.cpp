#include "mymath.h"


MyMath::MyMath()
{

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

    if( *str == '\0' )
        return result;

    // Перешагиваем через точку
    ++str;

    int i = 1;
    while( *str != '\0') {
        result = result*10 + (*str-'0');
        ++str;
        i *= 10;
    }

    result = result / i;

return result;
}
