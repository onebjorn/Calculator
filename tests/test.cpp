#include "gtest/gtest.h"
#include "../expression.h"
#include "../parser.h"
#include <sstream>
#include <iostream>
#include <ostream>
#include <unordered_set>

TEST(Calc_test, test_construction)
{
    Expression expr1("1");
    Expression expr2("2");
    Expression expr3("3");
    Expression expr4("4");

    Expression expr21("+", expr1);
    Expression expr22("-", expr2);

    Expression expr23("*", expr1, expr2);
    Expression expr24("/", expr3, expr4);

    EXPECT_EQ(expr1.getToken(), "1");
    EXPECT_EQ(expr2.getToken(), "2");
    EXPECT_EQ(expr3.getToken(), "3");
    EXPECT_EQ(expr4.getToken(), "4");

    EXPECT_EQ(expr21.getToken(), "+");
    EXPECT_EQ(expr22.getToken(), "-");
    EXPECT_EQ(expr23.getToken(), "*");
    EXPECT_EQ(expr24.getToken(), "/");

    EXPECT_EQ(expr21.getSize(), 1);
    EXPECT_EQ(expr23.getSize(), 2);
}


TEST(Calc_test, test_parser)
{
    string s1 = "1 + 2";
    Parser p1(s1.c_str());

    EXPECT_EQ(p1.solve(p1.parse()), 3);
}

TEST(Calc_test, test_calculations)
{
    Parser p1("11 * 9");
    EXPECT_EQ(p1.solve(p1.parse()), 99);

    EXPECT_EQ(Calculate("0,5 + 0,5"), 1);
    EXPECT_EQ(Calculate("0,1 * 1"), 0.1);
    EXPECT_EQ(Calculate("+1"), 1);
    EXPECT_EQ(Calculate("-1"), -1);
    EXPECT_EQ(Calculate("(1)"), 1);
    EXPECT_EQ(Calculate("1+ 1"), 2);
    EXPECT_EQ(Calculate("1 +  1"), 2);
    EXPECT_EQ(Calculate("1+10+100+1000"), 1111);
    EXPECT_EQ(Calculate("-1+10"), 9);
    EXPECT_EQ(Calculate("--1+10"), 11);
    EXPECT_EQ(Calculate("---1+10"), 9);
    EXPECT_EQ(Calculate("(1+10)"), 11);
    EXPECT_EQ(Calculate("-2 * 9"), -18);
    EXPECT_EQ(Calculate("2 *-9"), -18);
    EXPECT_EQ(Calculate("1+ +1"), 2);
    EXPECT_EQ(Calculate("1+ 10*10"), 101);
    EXPECT_EQ(Calculate("10 *10+1"), 101);
    EXPECT_EQ(Calculate("(1+ 10) *1"), 11);
    EXPECT_EQ(Calculate("2*(1+780)"), 1562);
    EXPECT_EQ(Calculate("(1+2)*(3+6)"), 27);
    EXPECT_EQ(Calculate("9*8+11*59"), 721);
    EXPECT_EQ(Calculate("100+19*10+3"), 293);
    EXPECT_EQ(Calculate("75 + 78 * 8 * 7 + 1.0"), 4444);
}

TEST(Calc_test, test_exception)
{
    EXPECT_ANY_THROW(Calculate("1 / 0"));
    EXPECT_THROW(Calculate("1 / 0"), runtime_error);
    EXPECT_ANY_THROW(Calculate("abc"));
    EXPECT_ANY_THROW(Calculate("abc+8"));
    EXPECT_ANY_THROW(Calculate("(((+7"));
    EXPECT_ANY_THROW(Calculate("(((+76)+89)"));
}


