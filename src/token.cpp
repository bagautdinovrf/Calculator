
#include <iostream>

#include "token.h"


Token::Token( string val, int pr, TypeToken type ) :
    mValue(val),
    mPriority(pr),
    mType(type),
    mValid(true)
{
    //
}

Token::Token( char val, int pr, TypeToken type ) : Token ( "", pr, type )
{
    mValue.push_back(val);
}

Token::Token(double val, Token::TypeToken type) :
    mValueDouble( val ),
    mType( type ),
    mValid(true)
{
    //
}

Token::~Token()
{
//    cout << "~Token()";
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
