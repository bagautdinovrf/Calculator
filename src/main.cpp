#include <iostream>

using namespace std;

void print_size ( int array[] )
{
    cout << sizeof (*array) << endl;
}

void func_ch( char *str )
{
    cout << str << endl;
}


int my_atoi( char str[] )
{
    int result = 0;
    int i = 0;

    while( *str != '\0') {
//        cout << *str << endl;
        result = result*10 + (*str-'0');
        ++str;
        ++i;
    }

return result;
}

int main()
{
    char str[] = "548734634";
    cout << my_atoi( str ) << endl;

return 0;
}
