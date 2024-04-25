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

int main()
{
    A a = 4;
    A aa(4);
}