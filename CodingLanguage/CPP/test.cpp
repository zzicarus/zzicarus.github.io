#include <iostream>
using namespace std;

class A
{
public:
    A(int i) : mi(i) {}
    A(const A &rhs) : mi(rhs.mi)
    {
        cout << "A::A(&)" << endl;
    }
    A &operator=(const A &rhs)
    {
        mi = rhs.mi;
        cout << "A::operator=()" << endl;
        return *this;
    }
    virtual void f()
    {
        cout << "A::f(), " << mi << endl;
    }

protected:
    int mi;
};

class B : public A
{
public:
    B(int i, int j) : A(i), mj(j) {}
    void f() override
    {
        cout << "B::f(), " << mi << ", " << mj << endl;
    }

private:
    int mj;
};

class Base
{
private:
public:
    int a;
    const int consA;
    Base(int a) : Base(a, a)
    {
        cout << "Call Base(int a)" << endl;
    }
    Base(int m, int ConstM) : a(m), consA(ConstM)
    {
        cout << "Call Base(int m, int ConstM)" << endl;
    }
};

int main()
{
    Base m(55);
    cout << m.a << " " << m.consA;
}