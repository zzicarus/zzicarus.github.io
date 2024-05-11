# Copy Control

!!! info "Copy"
    - 函数传参数
    ```c++
    
    ```

```c++
class A
{
public:
    A(int i) : mi(i) {}
    A(const A &rhs) : mi(rhs.mi)
    {
        cout << "A::A(&)" << endl;
    }
    virtual void f()
    {
        cout << "A::f(), " << mi << endl;
    }
protected:
    int mi;
};
```

## 拷贝构造函数

- 默认情况下，编译器会有一个
    - 原生类型值拷贝
    - class调用其拷贝函数
- 但是对于指针而言，它也是值拷贝，导致有两个指针指向同一个元素。这导致它的管理不明确，可能对同一块地址进行两次甚至多次`delete`.这种情况下，要对析构函数、拷贝构造函数进行定义
!!! success "Why const and why &"
    - const: 不能改变
    - 引用: 不然传参数的时候发生值传递，又要调用拷贝函数，陷入死循环
```c++
A(const A &rhs) : mi(rhs.mi)
{

}
```

??? note "定义部分"
    ```c++
    #include <iostream>
    using namespace std;

    class A
    {
    public:
        A() : value(0) { cout << "A() " << endl; };
        A(int a) : value(a) { cout << "A(int a)" << endl; };
        A(const A &other)
        {
            this->value = other.value;
            cout << "A(&)" << other.value << endl;
        };

        ~A() { cout << "~A" << endl; };

    private:
        int value;
    };
    A f(int a)
    {
        cout << "f()" << endl;
        return A(a);
    }
    A bar(A a)
    {
        cout << "bar" << endl;
        return a;
    }
    ```

??? info "编译器优化问题"
    ```c++
    int main()
    {

        // 编译器优化
        // 拷贝构造被优化 相当于 xa = A(5)
        A xa = f(5);
        /*
        f()
        A(int a)
        */

        // 进行拷贝构造
        A xb = bar(xa);
        /*
        A(&)5  参数传入一次拷贝构造
        bar    bar 调用
        A(&)5  拷贝构造 xb = 传回参数
        ~A     应该是那个参数被销毁了
        */
        A xc = A(11);
    }
    ```

![alt text](images/custom-image-1.png)

## 拷贝赋值运算

!!! note "拷贝"
    - 通常返回左值的引用

## 效率问题 Vector

> 由于vector运行过程中会发生扩容，所以拷贝构造会多次进行
>

!!! info "优化拷贝"
    将`alist.push_back(A(0));`改为`alist.emplace_back(0);`，可以不执行拷贝构造而是直接构造

<span class="box box-blue">C11</span>
禁用copy，`Person(const Person &rhs) = delete;`


```c++
vector<A> alist;
// push_back
alist.push_back(A(0));
alist.push_back(A(1));
alist.push_back(A(2));

alist.emplace_back(0);
alist.emplace_back(1);
alist.emplace_back(2);
```
