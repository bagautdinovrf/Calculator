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
//    char str[] = "3+45 * 2 / ( 1-5)^2";
//    char str[] = "2.5 * (-22 + 2 ^ 2 ^ 3) * (3 - 1)";
//    char str[] = "3 * ((-25 - 10 * -2 ^ 2 / 4) * (4 + 5)) / 2";
//    char str[] = "(10 - 15) * 3";
//    char str[] = "2 ^ 2 ^ 3";
//    char str[] ="3 + 40 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
//    char str[] = "2 * (2 + ~2 ^ 2 ^ 3) - 1";
//    char str[]  = "15*15/5*5";
    char str[]  = "9*-8";

    Calculator calc;
    double result = calc.calc( str );
    cout << "Answer = " << result << endl;

return 0;
}
