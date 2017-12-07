#pragma once
#include "expression.h"
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>

class Parser
{
public:
    Parser(const char* input) : input(input) {}

    Expression parse() { return parseBinaryExpression(0); }

    double solve(const Expression & expr)
    {
        switch (expr.getSize())
        {
        case 2: // бинарных операций
        {
            double a = solve(expr.getArgs()[0]);
            double b = solve(expr.getArgs()[1]);
            if (expr.getToken() == "+") return a + b;
            if (expr.getToken() == "-") return a - b;
            if (expr.getToken() == "*") return a * b;
            if (expr.getToken() == "/") return a / b;
        }

        case 1: // унарных операций
        {
            double a = solve(expr.getArgs()[0]);
            if (expr.getToken() == "+") return +a;
            if (expr.getToken() == "-") return -a;
        }

        case 0: return strtod(expr.getToken().c_str(), nullptr); // Функция strtod преобразовывает строку string в double.
        }

        throw runtime_error("некорректный ввод, строка содержит недопустимое выражение");
    }

    ~Parser() = default;

private:

    string parseToken()
    {
        while (isspace(*input)) ++input; // Пропуск пробелов в вводе

        if (isdigit(*input))
        {
            string number;
            while (isdigit(*input) || *input == '.' || *input == ',')
            {
                if(*input == ',') // Возможность использования запятой, для разделения десятичной части числа
                {
                    number.push_back('.');
                    input++;
                }
                else number.push_back(*input++);
            }
            return number;
        }

        const string tokens[] = { "+", "-", "*", "/", "(", ")" };

        for(auto & t : tokens)
        {
            if (strncmp(input, t.c_str(), t.size()) == 0) //Эта функция сравнивает символы двух строк
            {
                input += t.size();
                return t;
            }
        }

        return "";
    }

    Expression parseSimpleExpression()
    {
        auto token = parseToken();

        if (token.empty()) throw runtime_error("некорректный ввод");

        if (token == "(")
        {
            auto result = parse();
            if (parseToken() != ")") throw runtime_error("Expected ')'");
            return result;
        }

        if (isdigit(token[0]))
            return Expression(token);

        return Expression(token, parseSimpleExpression());
    }

    Expression parseBinaryExpression(int minPriority)
    {
        auto leftExpr = parseSimpleExpression();

        for (;;)
        {
            auto op = parseToken();
            int priority = getPriority(op);
            if (priority <= minPriority)
            {
                input -= op.size();
                return leftExpr;
            }

            auto rightExpr = parseBinaryExpression(priority);
            leftExpr = Expression(op, leftExpr, rightExpr);
        }
    }

    int getPriority(const string & operation)
    {
        if (operation == "+") return 1;
        if (operation == "-") return 1;
        if (operation == "*") return 2;
        if (operation == "/") return 2;
        return 0;
    }

    const char * input;
};


