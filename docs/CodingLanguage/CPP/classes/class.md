# 基本问题

## 封装

### 访问控制

#### protected

当成员被声明为 protected 时，它们对于派生类是可访问的，但对于类外部是不可访问的。

- 派生类的访问：派生类可以访问其基类中声明为 protected 的成员。
- 类外部的访问：类外部不能直接访问基类中声明为 protected 的成员，包括派生类的对象也不能直接访问。
- 派生类的成员函数的访问：派生类的成员函数可以访问其基类中声明为 protected 的成员。
- 友元类和友元函数的访问：友元类和友元函数可以访问基类中声明为 protected 的成员。

#### private

- 针对类而言的概念，而不是针对某个实例. 针对下面的实例，
```c++
class A
{
    public:
        void Foo(Base * B){cout << B.val << endl;}
    private:
        int val;
}
```

### friend

!!! info "friend"
    - 一般来说，最好把友元声明集中放到类的开始部分
    - 需要注意的是，友元声明本身并不是一个正式的声明，我们要在类之外再次正式声明函数
    - **友元关系是单向的，不具有传递性。**
    - 友元关系不受访问控制符影响，即友元函数或友元类可以访问类的私有、保护和公有成员。
尽量少使用友元，因为它破坏了封装性，使代码更难理解和维护。只在确实需要访问私有成员但无法通过成员函数或接口实现时才使用友元。
友元函数或友元类的声明通常放在类的内部，但定义可以在类内或外。








## 构造与析构

- 在多态操作的时候，调用派生类\多态类的的析构函数时，要记得把析构函数定义为`vitual`

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

## 内存布局

- 成员函数存放在代码区
- `static`不在class区域的内存定义




### 

## 多态

!!! info "vitual"
    - vitual 通过一个函数指针实现  `8 bytes`
    - 指针指向**一个表**，包含所有虚函数的code
    - 这个函数指针放在前八个字节中，所以虚函数实际调用的时候就是通过这前八个字节进行索引



    
