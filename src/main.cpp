#include <iostream>


#include "mymath.h"

using namespace std;


int main()
{
    char str[] = "54.";

    cout << MyMath::my_atoi( str ) << endl;
    cout << MyMath::my_atod( str ) << endl;

return 0;
}
