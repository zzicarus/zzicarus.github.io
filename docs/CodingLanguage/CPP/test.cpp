#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <memory>
#include <malloc.h>
using namespace std;

class S
{
public:
    void f()
    {
        cout << sizeof(S) << endl;
    }
    void x()
    {
        int a;
        return;
    }
    static int count;
};
int S::count = 0;

void f(shared_ptr<string> s)
{
    cout << s.unique() << endl;
    return;
}

int main()
{
    const char *s1 = "Hello"; // 指向静态变量的指针
    char *s3 = "Hello";
    char s2[] = "Hello";

    cout << (void *)main << endl;
    cout << (void *)s1 << endl;
    cout << (void *)s2 << endl;
    cout << (void *)s3 << endl;
    /*
    0x40158f
    0x404008
    0x61fe0a
    0x404008
    */
};
