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
        cout << "virtual A::f(), " << mi << endl;
    }
    void g()
    {
        cout << "A::g()" << mi << endl;
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
    void B_single()
    {
        cout << "B::B_single()" << mi << "," << mj << endl;
    }
    void g()
    {
        cout << "B::g()" << mi << "," << endl;
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

    A *a = new A(1);
    B *b = new B(2, 5);
    a->f();
    b->f();
    /*
    A::f(), 1
    B::f(), 2, 5
    */
    // a(1)
    // 转换之后，调用, 虚函数仍然是原来的，这与vitual Table相关
    (static_cast<B *>(a))->f();
    (static_cast<B *>(a))->B_single();
    (static_cast<B *>(a))->g();
    /*
    >> A::f(), 1
    >> B::B_single()1,0
    >> B::g()1
    */
    // b(2,5)
    (static_cast<A *>(b))->f();
    // >> B::f(), 2, 5
    (static_cast<A *>(b))->g();
    // >> A::g() 2
    // (static_cast<A *>(b))->B_single();
}