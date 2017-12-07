#pragma once
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Expression
{
public:

    Expression(string token)  // Конструктор для чисел
        : token(token)
    {}

    Expression(string token, Expression a) // Конструктор унарных операций,
        : token(token)
        , args{ a }
    {}

    Expression(string token, Expression a, Expression b) // Конструктор бинарных операций,
        : token(token)
        , args{ a, b }
    {}

    int getSize() const
    {
        return args.size();
    }

    string const & getToken() { return token; }

    vector<Expression> const & getArgs() { return args; }

    string token;
    vector<Expression> args;
};



