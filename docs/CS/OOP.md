# OOP

!!! info "INFO"
    个人在记这部分笔记的时候会有一部分拓展内容，可能考试并不要求掌握;也有一部分内容由于时间原因或者自己觉得没必要写于是没有着墨。BTW，也可能会有一些错误/纰漏，欢迎反馈！

    本来是想要把C++的笔记作为每个点一个Page，后来发现这样从复习OOP的角度非常不利。
	
    内容来源：陈翔老师上课内容及PPT，ljj老师PPT，及部分网络资源（ljj 21年的PPT中内容有一定纰漏，看的时候不要盲从，有一部分规范已经被较新的规范取代;但总体上还是挺实用的）

    - 一些题目收集的BLOG
		- [OOP Midterm Review](https://zhoutimemachine.github.io/note/courses/oop-mid-review/)
    - 历年卷
        - [98汇总](https://www.cc98.org/topic/5642245)
        - [新的98汇总](https://www.cc98.org/topic/5928482) **这个已经很全面了，建议看这个
    - 网站推荐
        - [cpp reference](https://en.cppreference.com/w/)
        - [modern CPP Programing](https://github.com/federico-busato/Modern-CPP-Programming) 这个里面讲得很多东西很实用
        - [陈翔老师推荐的了解算法库的视频](https://www.fluentcpp.com/getthemap/)
        - [this pointer](https://thispointer.com/)  看过一些关于Memory管理的内容
    - 一些工具的学习
        - [CMAKE](https://cmake.org/cmake/help/latest/index.html)  稍微看点例子，能明白基础用法；更高的就根据个人需要

!!! tip "课程评价/总结"
    授课教师：陈翔

    陈翔老师是OOP这门课公认的“神”，在课堂上用Vim演示代码讲解C++特性，~~很符合我对程序员的刻板印象~~

    关于考试：这门课的考试这几年不是很难，考前一定刷几套历年卷，虽然风格差异会比较大，但对于难点的考察大差不差。


!!! success "分数构成"
    分数构成多个教学班相差不大。据我个人了解，翁恺老师班会有期中考试、课前小测、签到，平时作业也会稍微多一点。cx老师班平时分基本给满

    - Attendance
    - Assignment 陈翔老师班级作业单周一个Lab，双周是简单的程序填空、选择
    - Lab
        - 平时Lab
        - Final Lab 做序列化的处理
    - Exam
        - Fill in Blank (text) -------- 30 points, 8 problems
            - write the output of the given code
        - Fill in blank (program) --- 30 points, 2 problems
            - single line code completion
        - Subjective (function) ----- 20 points, 1 problem 使用代码markdown代码块嵌进去，否则可能出现部分消失
            - class design
            - function implementation
        - Multiple Choice (SA) ----- 20 points, 1 problem  单选
            - miscellaneous 概念性，语言上的; 例如，C++语言的特性

## 零碎知识

!!! note "mention"
    这里的一部分内容（union）我只在ljj的21年PPT上看到过，不知道在不在考试范围内

### const

`const int` `int const` 等价

`int * const p` 这个指针是一个常量，必须在定义的时候赋值，指向一个`int`类型的变量 

`int const *p` 这个指针本身不是const，指向的对象是const对象 

`int const * const p` ~~"缝合怪"（~~

**类的const对象**

- 不能调用non-const函数

### inline

- 递归函数不能声明为inline函数
- 类中含有函数体默认为inline函数


### 引用

> 像是一个指针常量,只有在初始化的时候才会赋值,之后它的值不变,但是指向的可能会变. 
`const int &` 的限制是不能通过这个引用变量对值进行改变.

- 不能声明引用的引用，也不能定义引用的指针。如： 下例中的操作是达不到的：
    ```c++
    int a;
    int & & ra=a;
    int &*p=&ra;   //错误
    ```
- 不能建立数组的引用，因为数组是一个由若干个元素所组成的集合，所以就无法建立一个数组的别名。
- 不能建立空指针的引用，如：不能建立 `int &rp=NULL`
- 也不能建立空类型void的引用，如不能建立：`void &ra=3`
- 对于一个接受`non-const`变量的函数来说,传入的参数一定要是一个左值
    ```c++
    void func (int &);
    func (i * 3); // Warning or Error!
    ```

### static & extern

[NOTES](https://zzicarus.github.io/CodingLanguage/CPP/Static%26Extern/)

### inline Function
```c++
inline int add(int a,int b){...}
```

### Defalut Value
- Defalut value必须在函数最右侧
- 第一个缺省值出现之后，后面的所有缺省值都默认为缺省值
```c++
int fun(int I,int j=5,int k);   //错误
int fun(int I,int k = 1,int j=5);   //正确
fun(0,0)  // Right
fun(0)    // Right
fun(0,,0) // Wrong
```

### 作用域标识符
`::`在局部区域使用全局的值
```c++
int A = 500;
int main()
{
    int A = 40;
    cout << A << " " << ::A << endl;
    return 0;
}
```
### union
> The size of the union is equal to the size of the largest data type.

~~暂时感受不到他有什么用~~

1. 全局匿名union必须是static
2. 

### Named Casts

#### static_cast

根据**编译时状态**进行cast转换

- 只能转换相关的关系
- 不能移除const

1. 基础数据类型的转换
2. 派生的指针/引用向基类
3. 基类向派生类

??? example "example"
    ```c++
    class Base
    {
    public:
        int val;
        Base(int x) : val(x) { cout << "Base()" << endl; }
    };
    class Derived : public Base
    {
    public:
        Derived(int x) : Base(x) { cout << "Derived()" << endl; }
    };
    class Another
    {
    };
    int main()
    {
        double b = 1.01;
        int a = static_cast<int>(b);
        Base base(1), *bp;
        Derived d(2), *dp;
        bp = &base;
        // Derived d = static_cast<Derived>(base); 错误！只能指针/引用
        dp = static_cast<Derived *>(bp);
        cout << dp->val << endl;
        dp = &d;
        bp = static_cast<Base *>(dp);
        cout << bp->val << endl;
        return 0;
    }
    ```
    输出：
    ```c++
    Base()
    Base()
    Derived()
    1
    2
    ```
#### dynamic_cast

获得运行时的状态

- 必须要是多态，需要存在Virtual Function来获取运行时信息
- 只需要转换的基类是多态类就可以运行，但是可能产生nullptr

```c++
A *pa = new B;
C *pc = static_cast<C *>(pa);    // OK: but *pa is B!
cout << pa << endl;              // 0xe22580
cout << pc << endl;              // 0xe22580
B *pb = dynamic_cast<B *>(pa);   // OK:
C *pcDy = dynamic_cast<C *>(pa); // Not OK:
cout << pb << endl;              // 0xe22580
cout << pcDy << endl;            // 0 nullptr
```

#### reinterpret_cast

底层表示不变，但是理解为另外一种

```c++

```

#### const_cast

!!! warning "const"
    const之间有区别：编译时和编译后获得常量在程序中表现不同

```c++
int x = 7;
const int a = 7;    // if a = x
int *p;
p = const_cast<int *>(&a);
cout << a << endl;
cout << *p << endl;
*p = 155;
cout << a << endl;
cout << *p << endl;

> 7
> 7
> 7  // a = 155
> 155
```

### NameSpace

[GeeksForGeeks](https://www.geeksforgeeks.org/namespace-in-c/)

[C++  Reference](https://en.cppreference.com/w/cpp/language/namespace)

- 命名空间可以定义变量、函数、类型
- 命名空间可以嵌套
- 撞命名空间 -> Ambiguities
```c++

```
- 别名 `namespace short_ns = supercalifragilistic;`
- 合成
```c++
namespace mine { 
 using orig::Cat; // use Cat class from orig 
 void x(); 
 void y();
}
```
- 不一定在同一个module中
可以跨多文件存在


### 多重继承 MI

> ![alt text](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406301125157.png)

- 

**Protocol / Interface classes**

## Memory

### 内存基础知识

### 动态内存分配

[另一块笔记](https://zzicarus.github.io/CodingLanguage/CPP/Stadard_Library/%E5%8A%A8%E6%80%81%E5%86%85%E5%AD%98/)

## Class
!!! note "NOTE"
    考试的时候定义类的结束要记得加`;`

TODO: 左值和右值引用

::Error:: 非常量引用的初始值必须为左值C/C++(461)

```c++ hl_lines="7"
void fun(A &a)
{
    cout << "A a" << a.get();
}
int main()
{
    fun(A());
    return 0;
}
```

### construct / destruct

**Construct**

- 注意,一个类的构造函数中含有一个静态变量,这个静态变量只有第一次调用才会初始化

```c++ title="" hl_lines="9"
Date::Date(int y, int m, int d) // 定义构造函数
{
    year = y;
    month = m;
    day = d;
    Time time(11, 11, 11);
    // 在类Date定义的构造函数中定义类Time的对象（局部）
    // 这里也只定义一次
    static Time time1(12, 12, 12);
    // 在类Date定义的构造函数中定义类Time的静态对象（局部）
    cout << "Date Constructor" << year << ":" << month << ":" << day << endl;
}
```

### this指针

!!! note "this"
    this指针是一个隐含于每一个成员函数中的特殊指针。它指向**正操作该成员函数的对象**。
    
    当对一个对象调用成员函数时，编译程序先将对象的地址赋给this指针，然后调用成员函数。
    
    每次成员函数存取数据成员时，C++编译器将根据this指针所指向的对象来确定应该引用哪一个对象的数据成员。
    
    通常this指针在系统中是隐含存在的，也可以把它显式表示出来。

- this指针是一个const指针，不能在程序中修改它或给它赋值。
- this指针是一个局部数据，它的作用域仅在一个**对象的内部**,**通过 this 可以访问类的所有成员，包括 private、protected、public 属性的。**
- 有在对象被创建以后才会给 this 赋值，并且这个赋值的过程是编译器自动完成的，不需要用户干预，用户也不能显式地给 this 赋值。   


### Copy Control

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

#### 拷贝构造函数

!!! info "Copy"
    调用拷贝构造函数的情况有三种：
     （1）明确表示由一个对象初始化另一个对象。
     （2）当对象作为函数实参传递给函数形参时。
     （3）当对象作为函数的返回值，创建一个临时对象。

- 默认情况下，编译器会有一个
    - 原生类型值拷贝
    - class调用其拷贝函数
- 但是对于指针而言，它也是值拷贝，导致有两个指针指向同一个元素。这导致它的管理不明确，可能对同一块地址进行两次甚至多次`delete`.
这种情况下，要对析构函数、拷贝构造函数进行定义
- 默认的拷贝构造函数,会递归地对所有成员objects调用copy
- `Person(const Person &rhs) = delete;`

```c++
// 这里需要对类中的内存进行手动的管理,不然之后delete会重复删除同一块内存
Person::Person( const Person& w ) { 
 name = new char[::strlen(w.name) + 1]; 
 ::strcpy(name, w.name); 
}
```

!!! success "Why const and why &"
    - const: 不能改变
    - 引用: 不然传参数的时候发生值传递，又要调用拷贝函数，陷入死循环

!!! tip "编译器优化"
    ```c++
    Person copy_func( Person p ) { 
        p.print(); 
        return p; // copy ctor called! 
    } 
    Person nocopy_func( char *who ) { 
        return Person( who ); 
    } // no copy needed!
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

#### 拷贝赋值运算

!!! note "拷贝赋值"
    - 通常返回左值的引用
    ```c++
    Cube Cube1(20,20,20),Cube2; 
    Cube2=Cube1;        
    ```

#### 效率问题 Vector

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

### Friend
```c++
// Rectangle中的成员函数都可以使用Square中的所有成员
class Square { 
    friend class Rectangle; 
private:
    int side; 
public: 
    Square (int a) : side(a) {} 
};
```

- 友元的关系不能传递。
- 友元的关系是单向的而不是双向的

### 继承

!!! note "构造执行顺序"
    - 调用**基类**的构造函数;
    - 调用**内嵌对象成员**（子对象类）的构造函数（有多个对象成员时,调用顺序由它们在类中声明的顺序确定）;
    内嵌对象的构造优先级比较高
    - **派生类**的构造函数体中的内容
    - 同名函数的继承问题
    **一个派生类中override，其他基类同名函数也被覆盖掉(即使类型不同)**
    记得override所有的相关函数
    
??? example "example"
    ```c++
    #include <iostream>
    struct X {
        X() {
            std::cout << "X::X()" << std::endl;
        }
        ~X() {
            std::cout << "X::~X()" << std::endl;
        }
    };
    struct Y {
        Y() {
            std::cout << "Y::Y()" << std::endl;
        }
        ~Y() {
            std::cout << "Y::~Y()" << std::endl;
        }
    };
    struct Parent {
        Parent() {
            std::cout << "Parent::Parent()" << std::endl;
        }
        ~Parent() {
            std::cout << "Parent::~Parent()" << std::endl;
        }
        X x;
    };
    struct Child : public Parent {
        Child() {
            std::cout << "Child::Child()" << std::endl;
        }
        ~Child() {
            std::cout << "Child::~Child()" << std::endl;
        }
        Y y;
    };
    int main() {
        Child c;
    }
    ```
    ??? abstract "Answer"
    Line 1: 
    X::X()

    Line 2: 
    Parent::Parent()
    
    Line 3: 
    Y::Y()
    
    Line 4: 
    Child::Child()
    
    Line 5: 
    Child::~Child()
    
    Line 6: 
    Y::~Y()
    
    Line 7: 
    Parent::~Parent()
    
    Line 8: 
    X::~X()

- 基类构造函数不带参数时，派生类可不定义构造函数，但基类构造函数带有参数，则派生类必须定义构造函数。
- 基类和派生类的析构函数是各自独立的。
- 基类中的Private属性不能直接通过派生类访问 

```c++
// 进行初始化的时候,基类没有无参数的构造函数,派生类必须显式定义
class Derived：public Base
{
        Base d;     //d为基类对象，作为派生类的对象成员
    public：
        Derived(int i)：Base(i),d(i)
        {                    			
            cout<<"Constructing derived class\n";
        }
        ~Derived() 				//派生类的析构函数
        {   cout<<"Destructing derived class\n"; }
 };

```

![alt text](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406301125159.png)

#### 多继承

默认为`private`

`class z：x,public y` x为private


### 多态

!!! note ""
    静态多态性——函数重载和运算符重载；
    运行时的多态——继承和虚函数；
    
静态 : 在编译时就决定了函数所属
```c++
class A
{
public:
    void show() { cout << "A"; }
};
class B : public A
{
public:
    void show() { cout << "B"; }
};
int main()
{
    A a, *pc;
    B b;
    pc = &a;
    pc->show();
    pc = &b;
    pc->show();
    return 0;
}
```

#### virtual 虚函数
!!! note "virtual"
    1. 通过定义虚函数来使用C++提供的多态机制时，派生类应该从它的基类公有派生。赋值兼容规则成立的前提条件是派生类从其基类公有派生。
    2. 必须首先在**基类中定义虚函数**。在实际应用中，应该在类等级内需要具有动态多态性的几个层次中的最高层类内首先声明虚函数。
    3. 在派生类对基类中声明的虚函数进行重新定义时，关键字virtual可以写也可以不写。
    4. **使用对象名和点运算符的方式也可以调用虚函数，但是这种调用在编译时进行的是静态联编，它没有充分利用虚函数的特性。只有通过基类指针访问虚函数时才能获得运行时的多态性**
    5. 虚函数**必须是其所在类的成员函数，而不能是友元函数，也不能是静态成员函数，因为虚函数调用要靠特定的对象来决定该激活哪个函数。但是虚函数可以在另一个类中被声明为友元函数**
    6. 内联函数不能是虚函数，因为内联函数是不能在运行中动态确定其位置的。即使虚函数在类的内部定义，编译时仍将其看作是非内联的
    7. **构造函数不能是虚函数**。因为虚函数作为运行过程中多态的基础，主要是针对对象的，而构造函数是在对象产生之前运行的，因此虚构造函数是没有意义的
    8. **析构函数可以是虚函数，而且通常说明为虚函数**
    
!!! tip "Default Value"
    在虚函数中，可以使用Default value，但是需要注意：默认值是在编译时决定的，而虚函数是运行时动态绑定的



**纯虚函数**

`virtual void show()=0;`

至少含有一个纯虚函数,就是一个抽象类

- 抽象类不能定义一个实例,不能作为函数返回值或者参数
- 可以定义抽象类的指针或者引用

```c++
class base
{
public:
    base()
    {
        cout << "base constructor" << endl;
    }
    virtual ~base()
    {
        cout << "base destructor" << endl;
    }
};
class derived : public base
{
public:
    derived()
    {
        cout << "derived constructor" << endl;
    }
    ~derived()
    {
        cout << "derived destructor" << endl;
    }
};

int main()
{
    base *pb = new derived;
    delete pb;
}
```

!!! note "接口 Interface"
    全为virtual函数


## 重载 Overload



### 函数重载

### 运算符重载

**可以重载的类型**

```
+ - * / % ^ & | ~
= < > += -= *= /= %=
^= &= |= << >> >>= <<= ==
!= <= >= ! && || ++ --
, ->* -> () []
new new[]
delete delete[]
```

**不可以**

```
.  .*  ::  ?:
```

不可以自己创造类型

#### `Class member`

- **No type conversion performed on receiver**

```c++
x + y;    // x.operator+(y)
z = x + y // Good  
z = x + 3 // Good
z = 3 + y // Error
// 二元 binary
Integer operator+(const Integer & n) const{
    return Integer(i + n.i);
}
// 一元 unary
Integer operator-() const {
    return Integer(-i);
}
```


#### `Global operators `

- 对类内`private`没有访问权限，可能需要是friend
- 参数至少有一个是`class`或者`enum`类型

```c++
class Integer {
public:
    friend Integer operator+(const Integer&, const Integer&);
    ...
private:
    int i;
};
Integer operator+(const Integer& lhs, const Integer& rhs)
{
return Integer( lhs.i + rhs.i );
}
```

```c++
z = x + y; // operator+(x, y)
z = x + 3; // operator+(x, Integer(3))
z = 3 + y; // operator+(Integer(3), y)
z = 3 + 7; // Integer(10)  先求和 后转换
```

#### Detailed

- **+ - * / % ^ & | ~**
    `T operator X(const T& l, const T& r)`

- **!   &&   ||   <   <=   ==   >=   >**
    `bool operator X(const T& l, const T& r)`

- **[ ]**
    `E& T::operator [](int index)`

    一般还会有一个const版本，否则const容器无法使用返回值

    ```c++
    int &Vector::operator [](int index)
    {
        return Element[index];
    }
    ```

- **++  --   一元**
    区分 prefix postfix
    ```c++
    class Integer {
    public:
    ...
        Integer& operator++(); //prefix++
        Integer operator++(int); //postfix++
        Integer& operator--(); //prefix--
        Integer operator--(int); //postfix--
    ...
    };
    
    Integer x(5);
    ++x; // calls x.operator++();
    x++; // calls x.operator++(0);
    --x; // calls x.operator--();
    x--; // calls x.operator--(0);
    ```

- **=  赋值运算符**
    返回的一定要是引用，一般是`*this` `a = b = c`

    ```c++
    class Cargo{
        public:
        Cargo& operator=(const Cargo&)
        {
            return *this;
        }
    }
    // 自动版本，每个字段调用 = 
    class Truck{
        Cargo mc;
    }
    
    Truck a,b;
    a = b;
    ```

    `Copy constructor`和`assignment`

    **对于内含的指针变量，赋值函数要考虑释放原来的内存，不要使用默认 = . 防止重复释放同一块内存**

    注意`self-assiment!`，**Left Side可能本来就含有内容**

    ```c++
    class A
    {
    private:
    	char *p;
    public:
        A& operator=(const A& a){
            if(a == *this){
                ...
            }else{
                delete [] p;
                p = new char[strlen(a.p) + 1];
                strcpy(p,a.p);
                return *this;
            }
        }
        
    }
    ```

    `Forbid it`

    ```c++
    A& operator=(const A&) = delete;
    ```

- **( )  functor**
    `functor`  overloads the function call operator

    ```c++
    struct F {
        void operator()(int x) const {
            std::cout << x << "\n";
        }
    }; // F is a functor class
    F f; // f is a functor
    f(2); // calls f.operator()
    ```

    

    ```c++
    void transform(vector<int>& v,int (*f)(int))
    {
        for(int &x : v)
            x = f(x);
    }
    // 匿名函数 lambda
    int a = 4;
    transform(v,[](int x){return x * 2});
    // 具有环境变量的写法
    #include <functional>
    void transform(vector<int>& v,const function<int<int>> &f)
    {
        for(int &x : v)
            x = f(x);
    }
    
    // 捕获环境变量
    transform(v,[a](int x){return x * a;});
    ```

    构造了一个类（函数对象），这个类中重构`( )`符号，参数就是类中的一个变量；也就是说，完全可以由一个类定义，来代替Lambda 函数

!!! example "Code"
	```c++
	#include <iostream>
	#include <vector>
	using namespace std;
	
	class vec3
	{
	public:
	    vec3(int x = 0, int y = 0, int z = 0)
	    {
	        v[0] = x;
	        v[1] = y;
	        v[2] = z;
	    }
	    int operator[](int index) const
	    {
	        return v[index];
	    }
	    vec3 &operator+=(const vec3 &rhs)
	    {
	        for (int i = 0; i < 3; ++i)
	            v[i] += rhs.v[i];
	        return *this;
	    }
	
	private:
	    int v[3];
	};
	
	vec3 operator+(const vec3 &v1, const vec3 &v2)
	{
	    return vec3(v1) += v2;
	}
	
	ostream &
	operator<<(ostream &out, const vec3 &v)
	{
	    out << '(' << v[0] << ' ' << v[1] << ' ' << v[2] << ')';
	
	    return out;
	}
	
	int main()
	{
	    vec3 v1(1, 2, 3), v2(4, 5, 6);
	    vec3 v = v1 + v2;
	    v += v2;
	    cout << v << endl;
	}
	```

### 隐式转换

!!! note "隐式转换"
    **C++的类型转换**

    - **Built-in conversions**
    - **User-defined type conversions T => C** 通过单参数构造函数进行
        - if `C(T)` is a **valid constructor call** for C
        - if `operator C()` is defined for T


`explicit`  不允许隐式转换

**Single argument constructors**

```c++
class PathName {
string name;
public:
explicit PathName(const string&);
~ PathName();
};

string abc("abc");
PathName xyz(abc); // OK!
xyz = abc; // Error! OK if without explicit
```

这里，由于`C(int)`为`explicit`类型，所以在隐式转换时不会考虑这个函数，通过`C(double)`进行转换

```c++
class C
{
public:
    explicit C(int)
    {
        cout << "i" << endl;
    }
    C(double)
    {
        cout << "d" << endl;
    }
};
int main()
{
    C c1(7);
    C c2 = 7;
    return 0;
}
> i
> d
```

**Conversion Operator | 类的转换**

`X::operator T()`

- No explicit arguments
- No return type

```c++
class Rational {
public:
    operator double() const {
        return numerator / (double)denominator;
    }
}
Rational r(1,3);
double d = 1.3 * r; // r => double
```


## Stream

**优势**

- Better type safety
- Extensible
- More object-oriented

**类型**

```c++
// 基类
istream& operator>>(istream& in, T& obj){
    // 
    in >> obj. >> obj.;
    return in;
}
ostream& operator<<(ostream& out,T& obj){
    return out << " ";
}
```

### Stream流

- cin

	- standard input

- cout
	- standard output


- cerr 
	- unbuffered error (debugging) output

- clog
	- buffered error (debugging) output

### 输出控制

`#include <iomanip>`

![image-20240627181657729](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406271817909.png)



## 类型转换



## Template
!!! note "NOTE"
    - 
    
    **匹配推导顺序**
    
    ==常量修饰符：const 和 volatile 修饰符在推导过程中会被保留==
    
    1. 先找是否有完全匹配的普通函数
    
    2. 再找是否有完全匹配的模板函数
    
    3. 再找有没有通过进行隐式类型转换可以调用的函数

要应对这种隐式转换

- 显式声明一个模板
```c++
template<class T>
T max(T x, T y)
{
    return (x>y)?x:y;
}
int max(int, int)；//只声明一个非模板函数的原型
void func(int i,char c)
{
    max(i, i);    //正确 ,调用max(int,int)
    max(c, c);  // Error: 多个匹配的函数
    max(i, c);   //正确 ,调用 max(int,int),使用隐式类型转换
    max(c, i);   //正确 ,调用max(int,int),使用隐式类型转换
}
```

### Functional Overloading 函数重载

**Defalut value**

Error

- 有默认值的情况下再次定义会Error

```c++
void foo(int i = 5, int j = 4);
void foo(int i, int j = 4)
{
    cout << i << j << endl;
}
int main()
{
    foo();
}
```

### Function 函数模板

**inline的位置**

```c++
template <typename T>
inline bool compare(const T &a, const T &b)
{
    return a < b;
}
int main()
{
    cout << compare(5, 1.0);   // Error
    cout << compare<int>(5, 1.0);  // Good
}
```

- 不允许隐式转换

- typename <>中还可以存在其他变量甚至是缺省量 <typename T, size_t S = 100>

- 函数匹配
    ```c++
    template <typename T>
    inline bool compare(const T &a, const T &b)
    {
        return a < b;
    }
    bool compare(const float &a, const float &b)
    {
        return a < b;
    }
    int main()
    {
        cout << compare(5.0, 1.0);  // 调用 函数模板
    }
    ```

### Class 类模板

!!! note "NOTE"
    - 类模板中的都是模板函数
    如果在类外定义函数，记得`T Class::Function(T a)`


### 模板特化 Template specialization

```c++ title = "原模版"
template<class T1, class T2, int I>
class A { /* ... */ };
```

```c++ title = "全特化"
template<>
class A<int, double, 5> { /* ... */ };
```

```c++ title = "偏特化"
template<class T2>
class A<int, T2, 3> { /* ... */ };
// 另外一个例子，将指针类型进行 partial 
template <class T1>
class B<T1*>{ };
```

函数匹配顺序：
1. 优先寻找全特化
2. 

## Iterator

> Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

封装
```c++ 
template<class T>
class auto_ptr {
private:
 T *pointee;
public:
 /* ... */
 T& operator *() { return *pointee; }
 T* operator ->() { return pointee; }
};
```

`++ * ==`

注意不同的底层实现，其实对Iterator的操作有影响

比如，`set`使用红黑树作为底层实现，使用`It++`得到的结果不是按初始化顺序排列的

> 如何获得Iterator的类型以及其元素的类型 ?

### `iterator_traits`

```c++
template<class I>
class iterator_traits
{
public:
 typedef typename I::iterator_category iterator_category;
 typedef typename I::value_type value_type;
 typedef typename I::difference_type differece_type;
 typedef typename I::pointer pointer;
 typedef typename I::reference reference;
 /* ... */
}
```
### Catagory
![alt text](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406301125160.png)

category info
```c++
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag
 : public input_iterator_tag {};
struct bidirectional_iterator_tag
 : public forward_iterator_tag {};
struct random_access_iterator_tag
 : public bidirectional_iterator_tag {};
```

## 异常处理

!!! warning "注意"
    Try-Catch Block中，必须存在Try-Catch的配对，但是catch中的参数可以为空，表示这里不去捕捉处理错误


```c++
try {
 // -----------------------
 // main logic here
 open the file;
 determine its size;
 allocate that much memory;
 read the file into memory;
 close the file;
 // -----------------------
} catch ( fileOpenFailed ) {
   doSomething;
} catch ( sizeDeterminationFailed ) {
   doSomething;
} catch ( memoryAllocationFailed ) {
   doSomething;
} catch ( readFailed ) {
   doSomething;
} catch ( fileCloseFailed ) {
   doSomething;
}
```

!!! note "assert"
	Debug的时候会很有用，也可以放在Test里面。在MiniSQL里面有很多应用。
	```c++
	assert(index > 0 && index < size);
	```
	更详细的内容可见分区：【::TODO::】

? throw 一个对象回去，这个对象什么时候析构？

**`throw`**

- `throw exception` 抛出异常
- `throw`   throw 后面不加任何东西，直接传递给上层函数，**只能在catch中使用**
	- re-raises the exception being handled
	- valid only within a handler
- 可以 throw 任意类型的数据

```c++
void f0()
{
    try
    {
        f1();
    }
    catch (double)
    {
        cout << "f0() double" << endl;
    }
    cout << "f0() End" << endl;
}
```

尽量不要使用`throw new Exception()`，直接使用`throw Exception()`  否则new出来的对象也要自己去释放

**`catch`**

- `catch(...)`
- `catch(Exception)`

### 异常指定

==动态异常规范已经在C++11之后被取消==

`warning: dynamic exception specifications are deprecated in C++11`

**异常指定**是函数声明的一部分，必须同时出现在函数声明和函数定义的首行中，否则在进行函数的另一次声明时，编译系统会报告“类型不匹配”。

**匹配机制**

针对每一条catch，**依次进行匹配**，所以可能导致提前“截断”——基类处理将派生类处理顶掉

1. 类型完美匹配
2. 基类转化  一定要是指针/引用类型 ? TODO
3. `catch(...)` 所有都能匹配，必须放在结束位置，否则Error

```c++
// Warning : UnderFlowError will be caught by earlier Exception
try
{
    ...
}
catch (MathError &e)
{
    cout << "MathError" << endl;
}
catch (UnderFlowError &e)
{
    cout << "UnderFlow" << endl;
}
catch (...)
```

![image-20240625152920692](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406251529858.png)

**无异常函数**

`void foo() noexcept{...}`  在运行时检查，如果运行时仍然抛出异常，那么将会停止程序

FILE 类型的析构函数可以执行`f.close()`，无需在try block

### 构造异常

```c++
void f()
{
    // 不会发生内存泄漏
    X x;            // 
    Y *p = new Y(); // 内存
}
```

- 在调用构造函数时出现异常，退出
    - 析构函数不会被执行，但是已经生成、申请的内存不会被释放（指的是析构中产生的内存，比如`new int`）;

!!! example "example"
	```c++
	
	```

**解决方法**
- 在检测到Exception时手动释放内存
- 两层构造，通过另外一个函数init实现, 让用户手动实现类的Init
- 将原生指针放入一个warpper类
- 使用`unique_ptr`管理动态的资源，作用上相当于一个Wrapper的模板类

```c++

```

### 析构异常

不能抛出异常，将会执行`std::terminate()`

### 使用

- 在与外界模块进行交互的时候使用异常处理
- 库内部最好用`assert`来检查边界条件
- 抛出去最终没有catch将terminate

- 做到`exception-safe code`，要实现类似数据库中“原子性”的操作

### 标准库

## 智能指针

定义了一个模板类，来

- std::unique_ptr

`构建`

```c++
// Error
unique_ptr<A> pa = new A();
//
unique_ptr<A> pa(A());
// 了解,不推荐使用new去构建
unique_ptr<A> pa{new A()};

auto pa = make_unique<A>();
```

`std::move(source)`

```c++
string str("hello!");
string target(std::move(str));
所有权的转让
之后的str不能再使用，其中的值时undefined、
```

`pa.get()` 获得原生指针

``

- `std::shared_ptr`

`pt.use_count()` 引用计数

- `std::weak_ptr`

能够看到管理权，但是不会增加其`use_count`

> 比如两个类，彼此之间用shared_ptr互指，将造成死锁

-  `std::auto_ptr` (deprecated in C++11)


## Application

### 排序

`less`  `greater` 函数

## STL

### map 

```c++
 map<string, int> a = {{"a", 1}, {"b", 2}};
a.emplace("c", 4);
a["d"] = 4;
a.insert({"e", 5});
for (const auto &[key, value] : a)
{
    cout << "Key: " << key << ", Value: " << value << endl;
}
```

这里的i为pair类型

### list
