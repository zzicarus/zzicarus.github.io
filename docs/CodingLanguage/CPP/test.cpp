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
    static int count; // 由实例共享
    static const int size = 100;
    const int selfRank;
    // int A[selfRank]; // Error
    // int A[count];    // Error
    int A[size];

public:
    void f()
    {
        cout << "SizeOF S" << sizeof(S) << endl;
    }
    void f() const
    {
        cout << "f() const" << endl;
    }

    static void g() // 可不由实例使用
    {
        cout << "Recall g()" << endl;
    }
    S() : selfRank(0) {}
    S(int rank) : selfRank(rank)
    {
    }
};

int S::count = 100;

class A
{
private:
    int x;
    int y;

protected:
    void UpdateX(int newX);

public:
    int count;
};
class B
{
    A a;
};
class C : A
{
};

int main()
{
    A a;
    B b;
    C c;
};
