#include <iostream>

#include "token.h"

Token::Token( string val, int pr, TypeToken type ) :
    mValue(val),
    mPriority(pr),
    mType(type),
    mValid(true)
{
//    cout << mValue << mPriority << mValid << endl;
//    cout << valueString() << priority() << isValid() << endl;
}

Token::Token( char val, int pr, TypeToken type )
{
    string str;
    str.push_back(val);
    Token ( str, pr, type );
}

Token::Token(double val, Token::TypeToken type) :
    mValueDouble( val ),
    mType( type )
{

}


string Token::valueString() const
{
    return mValue;
}

double Token::valueDouble() const
{
    return mValueDouble;
}

int Token::priority() const
{
    return mPriority;
}

Token::TypeToken Token::type() const
{
    return mType;
}

bool Token::isValid() const
{
    return mValid;
}
