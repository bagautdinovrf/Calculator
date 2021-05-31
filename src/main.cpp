#include <iostream>
#include <cstring>

#include "mymath.h"
#include "calculator.h"

using namespace std;


int main()
{
//    char str[] = "0.86";
//    char str[] = "13. / 2.0";
//    char str[]  = "(( 4. - 1.0)/((2.) -1.0))";
//    char str[] = "3+4 * 2 / ( 1-5)^2";
//    char str[] = "2.5 * (-22 + 2 ^ 2 ^ 3) * (3 - 1)";
//    char str[] = "3 * ((-25 - 10 * -2 ^ 2 / 4) * (4 + 5)) / 2";
//    char str[] = "(10 - 15) * 3";
//    char str[] = "2 ^ 2 ^ 3";
//    char str[] ="3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
//    char str[] = "2 * (2 + ~2 ^ 2 ^ 3) - 1";


//    char s[] = ".";
//    cout << MyMath::my_atod(s) << endl;

    Calculator calc;
    double result = calc.calc( str );
    cout << "Answer = " << result << endl;


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
