#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token
{
public:
    enum TypeToken { BAD, DIGIT, OPERATOR, OPEN_BRACKET = '(', CLOSE_BRACKET = ')'};

    Token() = default;
    Token( string val, int pr, TypeToken type = OPERATOR );
    Token( char val, int pr, TypeToken type = OPERATOR );
    Token( double val, TypeToken type = DIGIT );

    string valueString() const;
    double valueDouble() const;
    int priority() const;
    TypeToken type() const;

    bool isValid() const;

private:
    double mValueDouble = 0.0;
    string mValue = "";
    int mPriority = -1;
    TypeToken mType = BAD;

    bool mValid = false;
};


#endif // TOKEN_H
