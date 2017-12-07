#pragma once
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct Expression
{
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

    string token;
    vector<Expression> args;
};


double eval(const Expression & e)
{
    switch (e.args.size()) {
    case 2: // бинарных операций
    {
        double a = eval(e.args[0]);
        double b = eval(e.args[1]);
        if (e.token == "+") return a + b;
        if (e.token == "-") return a - b;
        if (e.token == "*") return a * b;
        if (e.token == "/") return a / b;
    }

    case 1: // унарных операций
    {
        double a = eval(e.args[0]);
        if (e.token == "+") return +a;
        if (e.token == "-") return -a;
    }

    case 0: // чисел
        return strtod(e.token.c_str(), nullptr); // Функция strtod преобразовывает строку string в double.
    }

    throw runtime_error("некорректный ввод, строка содержит недопустимое выражение");
}


int get_priority(const string & binary_op)
{
    if (binary_op == "+") return 1;
    if (binary_op == "-") return 1;
    if (binary_op == "*") return 2;
    if (binary_op == "/") return 2;
    return 0;
}
