#include <iostream>
#include <iomanip>
#include "expression.h"
#include "parser.h"

int main()
{
    string input;
    getline(cin, input);
   // cout << setprecision(2) << Calculate(s.c_str()) << endl;

    try
    {
        auto res = Calculate(input.c_str());
        cout << input << " = " << setprecision(2) << res << endl;
    }
    catch (invalid_argument const & e)
    {
        cerr << input << e.what() << endl;
    }
    catch (exception const & e)
    {
        cerr << input << e.what() << endl;
    }

}
