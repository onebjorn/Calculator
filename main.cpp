#include <iostream>
#include <iomanip>
#include "expression.h"
#include "parser.h"

int main()
{
    char * s = "-10.23 + (8 * 2.5) - (3 / 1,5)";
    //std::cin >> s;
    cout << setprecision(3) << Calculate(s) << endl;
}
