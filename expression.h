#pragma once
#include <string>
#include <vector>

using namespace std;

struct Expression
{
    Expression(string token) : token(token) {}
    Expression(string token, Expression a) : token(token), args{ a } {}
    Expression(string token, Expression a, Expression b) : token(token), args{ a, b } {}

    string token;
    vector<Expression> args;
};


double eval(const Expression& e)
{
    switch (e.args.size()) {
    case 2:
    {
        auto a = eval(e.args[0]);
        auto b = eval(e.args[1]);
        if (e.token == "+") return a + b;
        if (e.token == "-") return a - b;
        if (e.token == "*") return a * b;
        if (e.token == "/") return a / b;
        throw runtime_error("Unknown operator"); //ошибка выполнения с неизвестным символом
    }

    case 1:
    {
        auto a = eval(e.args[0]);
        if (e.token == "+") return +a;
        if (e.token == "-") return -a;
        throw runtime_error("Unknown operator"); // ошибка выполнения с неизвестным символом
    }

    case 0:
        return strtod(e.token.c_str(), nullptr);
    }

    throw runtime_error("Unknown expression type"); // ошибка выполнения с неизвестным символом
}


int get_priority(const string & binary_op)
{
    if (binary_op == "+") return 1;
    if (binary_op == "-") return 1;
    if (binary_op == "*") return 2;
    if (binary_op == "/") return 2;
    return 0;
}
