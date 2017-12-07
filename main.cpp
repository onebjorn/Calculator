#include <iostream>
#include <iomanip>
#include "expression.h"
#include "parser.h"

int errors;

void test(const char* input, double expected) {
    try
    {
        Parser p(input);
        auto result = eval(p.parse());
        if (result == expected) return;
        cout << input << " = " << expected << " : error, got " << result << '\n';
    }
    catch (exception& e)
    {
        cout << input << " : exception: " << e.what() << '\n';
    }
    ++errors;
}

int main() {

    char* s = "-10.23 + (8 * 2.5) - (3 / 1,5)";
    double res;
    //std::cin >> s;
    Parser p(s);
    res = eval(p.parse());
    cout << setprecision(3) << res << endl;


    test("sdf", 0);
    test("0,5 + 0,5", 1.0);
    test("0,1 * 1", 0.1);
    test("0.8 / 0.8", 1.0);
    test("1", 1);
    test("9", 9);
    test("10", 10);
    test("+1", 1);
    test("-1", -1);
    test("(1)", 1);
    test("(asd1 asd)", -1);
    test("1+20", 21);
    test("1 + 20", 21);
    test("1+20+300", 321);
    test("1+20+300+4000", 4321);
    test("-1+20", 19);
    test("--1+20", 21);
    test("---1+20", 19);
    test("(1+20)", 21);
    test("-2*3", -6);
    test("2*-3", -6);
    test("1++2", 3);
    test("1+10*2", 21);
    test("10*2+1", 21);
    test("(1+20)*2", 42);
    test("2*(1+20)", 42);
    test("(1+2)*(3+4)", 21);
    test("2*3+4*5", 26);
    test("100+2*10+3", 123);
    test("5 * 4 + 3 * 2 + 1", 27);
    std::cout << "Done with " << errors << " errors.\n";
}
