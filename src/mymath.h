#ifndef MYMATH_H
#define MYMATH_H

#include <string>


class MyMath
{
public:
    MyMath();

    static int my_atoi( char str[] );
    static double my_atod( char * str );
    static void str_size( const char * str );
    static bool isDigit( const char ch );
    static bool isDot(const char ch);
    static bool isDigitDot(const char ch);
};

#endif // MYMATH_H
