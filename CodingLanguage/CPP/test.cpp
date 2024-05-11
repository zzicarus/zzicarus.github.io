#include <iostream>
using namespace std;

class A
{
public:
    A() : value(0) { cout << "A() " << endl; };
    ~A() { cout << "~A" << endl; };
    static int count;
    static void foo()
    {
        cout << "foo() " << count << endl;
    }

private:
    int value;
};
int A::count;
int main()
{
    A a;
    a.foo();
    A::foo();
    cout << a.count << endl;
    cout << A::count << endl;
}