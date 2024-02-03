#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
using namespace std;

void testFunc(const int a)
{
    return;
}

void error_msg(int type, initializer_list<string> il)
{
    for (auto j : il)
        cout << j;
    cout << endl;
}
const string return_string(void)
{
    string m = "Error";
    m.append("k");
    return m;
}

int main()
{
    string a = "NO";
    error_msg(0, {"Yes", " or ", a});
    cout << return_string();
    return 0;
}