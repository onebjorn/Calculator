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

        static const string tokens[] = { "+", "-", "*", "/", "(", ")" };
        for(auto& t : tokens)
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
        auto left_expr = parse_simple_expression();

        for (;;) {
            auto op = parse_token();
            auto priority = get_priority(op);
            if (priority <= min_priority) {
                input -= op.size();
                return left_expr;
            }

            auto right_expr = parse_binary_expression(priority);
            left_expr = Expression(op, left_expr, right_expr);
        }
    }

    const char* input;

};


