# 基本问题

## 封装

### 访问控制

#### protected

当成员被声明为 protected 时，它们对于派生类是可访问的，但对于类外部是不可访问的。

- 派生类的访问：派生类可以访问其基类中声明为 protected 的成员。
- 类外部的访问：类外部不能直接访问基类中声明为 protected 的成员，包括派生类的对象也不能直接访问。
- 派生类的成员函数的访问：派生类的成员函数可以访问其基类中声明为 protected 的成员。
- 友元类和友元函数的访问：友元类和友元函数可以访问基类中声明为 protected 的成员。

### friend

!!! info "friend"
    - 一般来说，最好把友元声明集中放到类的开始部分
    - 需要注意的是，友元声明本身并不是一个正式的声明，我们要在类之外再次正式声明函数



## 构造与析构


## const

- 为函数添加const修饰，

!!! warning "assignment & Initialization"
    `const`对象的初始化
    ```c++
    
    ```


```c++
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

int main()
{
    const S s;
    S s2;
    S::g();
    s.f();
    s.g();
    s2.f();
};
```