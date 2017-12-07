#pragma once
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Expression
{
public:
// Конструктор для чисел
    Expression(string token): token(token) {}
// Конструктор унарных операций(+a, -a, ---a)
    Expression(string token, Expression a): token(token), args{ a } {}
// Конструктор бинарных операций(a + b, a * b..)
    Expression(string token, Expression a, Expression b): token(token), args{ a, b } {}

    int getSize() const { return args.size(); } //

    string const & getToken() const { return token; } //

    vector<Expression> const & getArgs() const { return args; } //

    ~Expression() = default;

private:
    string token;
    vector<Expression> args;
};



