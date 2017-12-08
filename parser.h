#pragma once
#include "expression.h"
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>

class Parser
{
public:
    Parser(const char * input) : input(input) {}

    Expression parse() { return parseBinaryExpression(0); }

    double solve(const Expression & expr)
    {
        switch (expr.getSize())
        {
        case 2: // Бинарная операция
        {
            double a = solve(expr.getArgs()[0]);
            double b = solve(expr.getArgs()[1]);
            if (expr.getToken() == "+") return a + b;
            if (expr.getToken() == "-") return a - b;
            if (expr.getToken() == "*") return a * b;
            if (expr.getToken() == "/" && b != 0) return a / b;
            else throw runtime_error("Division by zero!");
        }

        case 1: // Унарная операция
        {
            double a = solve(expr.getArgs()[0]);
            if (expr.getToken() == "+") return +a;
            if (expr.getToken() == "-") return -a;
        }

        case 0: return strtod(expr.getToken().c_str(), nullptr); // Возвращаем число
        }

        throw runtime_error("Некорректный ввод, строка содержит недопустимое выражение");
    }

    ~Parser() = default;

private:

    string parseToken() // Возвращает токен
    {
        while (isspace(*input)) ++input; // Пропуск пробелов в вводе

        if (isdigit(*input)) // Если встречается цифра, то пытаемся парсить число полностью
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

        const string tokens[] = { "+", "-", "*", "/", "(", ")" }; // Список допустимых токенов

        for(auto & t : tokens)
        {
            if (strncmp(input, t.c_str(), t.size()) == 0) // strncmp сравнивает символы двух строк
            {
                input += t.size();
                return t;
            }
        }

        return ""; // Возвращаем пустой токен, если не распознали
    }

    Expression parseSimpleExpression()
    {
        auto token = parseToken();

        if (token.empty()) throw runtime_error("Некорректный ввод"); // Если токен неизвестен

        if (token == "(")
        {
            auto result = parse();
            if (parseToken() != ")") throw runtime_error("Ожидается ')'");
            return result;
        }

        if (isdigit(token[0]))
            return Expression(token);

        return Expression(token, parseSimpleExpression());
    }

    Expression parseBinaryExpression(int minPriority)
    {
        auto leftExpr = parseSimpleExpression();  // Либо простое выражение, либо бинарное выражение, полученное на предыдущей итерации

        while(true) // Рекурсивным вызовом парсера получается выражение справа
        {
            auto op = parseToken();
            int priority = getPriority(op);

            if (priority <= minPriority) // Выходим из цикла если ее приоритет слишком низок
            {
                input -= op.size();
                return leftExpr;
            }

            auto rightExpr = parseBinaryExpression(priority);
            leftExpr = Expression(op, leftExpr, rightExpr);
        }
    }

    int getPriority(const string & operation) // Возвращает приоритет бинарной операции
    {
        if (operation == "+") return 1;
        if (operation == "-") return 1;
        if (operation == "*") return 2;
        if (operation == "/") return 2;
        return 0;
    }

    const char * input;
};



double Calculate(const char * input) // Функция для непосредственного вычисления подаваемой строки
{
    Parser parser(input);
    return parser.solve(parser.parse());
}
