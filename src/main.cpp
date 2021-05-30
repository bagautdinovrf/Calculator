#include <iostream>
#include <cstring>

#include "mymath.h"
#include "calculator.h"

using namespace std;


int main()
{
//    char str[] = "54.86";
//    char str[] = "1.87 + 63 + 56";
//    char str[]  = "(( 4. - 1.0)/((2.) -1.0))";
    char str[] = "3+4 * 2 / ( 1-5)^2";
//    char str[] = "2 ^ 2 ^ 3";

//    cout << MyMath::my_atod(str) << endl;

    Calculator calc;
    calc.calc( str );




//    const char test[][100] =
//    {
//        { ".10" }, {"(1.)"}, {"2.0 ^ 2. ^ 3.0"}, {"13. / 2.0"}, {"(( 4. - 1.0)/((2.) -1.0))"}
//    };

//    ".10"                             -> 0.1
//    "(1.)"                            -> 1.0
//    "2.0 ^ 2. ^ 3.0"                  -> 256.0
//    "13. / 2.0"                       -> 6.5
//    "(( 4. - 1.0)/((2.) -1.0))"     -> 3

return 0;
}
