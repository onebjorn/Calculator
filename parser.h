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

    Expression parse() { return parse_binary_expression(0); }

    double solve(const Expression & expr)
    {
        switch (expr.getSize())
        {
        case 2: // бинарных операций
        {
            double a = solve(expr.args[0]);
            double b = solve(expr.args[1]);
            if (expr.token == "+") return a + b;
            if (expr.token == "-") return a - b;
            if (expr.token == "*") return a * b;
            if (expr.token == "/") return a / b;
        }

        case 1: // унарных операций
        {
            double a = solve(expr.args[0]);
            if (expr.token == "+") return +a;
            if (expr.token == "-") return -a;
        }

        case 0: // чисел
            return strtod(expr.token.c_str(), nullptr); // Функция strtod преобразовывает строку string в double.
        }

        throw runtime_error("некорректный ввод, строка содержит недопустимое выражение");
    }

private:

    string parse_token()
    {
        while (isspace(*input)) ++input; // Пропуск пробелов в вводе

        if (isdigit(*input)) {
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

    Expression parse_simple_expression()
    {
        auto token = parse_token();

        if (token.empty()) throw runtime_error("некорректный ввод");

        if (token == "(")
        {
            auto result = parse();
            if (parse_token() != ")") throw runtime_error("Expected ')'");
            return result;
        }

        if (isdigit(token[0]))
            return Expression(token);

        return Expression(token, parse_simple_expression());
    }

    Expression parse_binary_expression(int min_priority)
    {
        auto leftExpr = parse_simple_expression();

        for (;;) {
            auto op = parse_token();
            auto priority = get_priority(op);
            if (priority <= min_priority) {
                input -= op.size();
                return leftExpr;
            }

            auto rightExpr = parse_binary_expression(priority);
            leftExpr = Expression(op, leftExpr, rightExpr);
        }
    }

    int get_priority(const string & binary_op)
    {
        if (binary_op == "+") return 1;
        if (binary_op == "-") return 1;
        if (binary_op == "*") return 2;
        if (binary_op == "/") return 2;
        return 0;
    }



    const char* input;

};


