# Static & Extern

!!! info ".h"
    


## Static

- 全局变量  限制在此文件内部
- 函数修饰  同上

- 类中变量  所有类共享变量**(注意需要在类的外部对这个变量进行定义，也是对他进行初始化的地方)**
不能在初始化列表中初始化静态变量


- 类中函数修饰  只能使用`static`变量，比如下面的例子中如果在foo函数中调用value就会报错
这个函数是独立于对象之外的，没有隐含的`this`指针
    - 没有`this`指针
    - 只能使用静态数据
    - 不能被dynamically Overridden

??? example "code"
    注意12，18行的写法

    ```c++ hl_lines="12 18 22 23 24"
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
    ```

## Extern
> extern is a declaration says there will be such a variable somewhere in the whole program


如果需要重复使用同一个变量，有两种方式：

1.使用头文件，然后声明它们，然后其他文件去包含头文件。

2.在其他文件中直接extern

