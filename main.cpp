#include <iostream>
#include <iomanip>
#include "expression.h"
#include "parser.h"

int main()
{
    string input;
    getline(cin, input);
    cout << setprecision(2) << Calculate(input.c_str()) << endl;

}
