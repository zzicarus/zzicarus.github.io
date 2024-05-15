# Algorithm

!!! abstract
    标准库提供了一组算法，大多数都独立于容器存在。
    [referrence](https://en.cppreference.com/w/cpp/algorithm)

    [Short Video](https://www.fluentcpp.com/2017/01/05/the-importance-of-knowing-stl-algorithms/)
    
    多数算法在`algorithm`文件中提供:

    - find

    还有一部分在`numeric`中:

    - accumulate
    - 

一般情况下，算法库中的算法操作的对象都是迭代器而非容器本身。

## 罗列

!!! note "注意"
    1. 对于**接受单一迭代器表示第二个容器的算法，默认后一个容器长度大于等于第一个**
    2. 下面的参数为迭代器即可，不一定是begin(),end()

### find

```c++

```

### accumulate

<span class="box box-blue">numeric</span>

`accumulate(vec.begin(),vec.end(),element);`

1. ==第三个参数决定了使用的加法运算符和返回值的类型，同时加法也是在 element 的基础上进行操作==
2. 要注意是否可加

### equal

`equal(vec.begin(),vec.end(),vec2.begin());`

!!! warning ""
    > 要确保第二个序列的长度>=第一个

    且所有第二个容器只用一个迭代器表示的算法都默认这一条规则



### fill
<span class="box box-yellow">写操作</span>

!!! warning "warning"
    writing操作默认有足够的空间容纳写的元素

    一个很典型的错误是向空容器写入值

    为了保证在写入元素时存在足够的空间，可以使用`back_inserter`
    ```cpp
        vector<int> a;
        fill_n(back_inserter(a), 10, 0);
    ```

`fill(begin,end,element);`

`fill_n(iter,n,element)`

### copy

copy 
```c++
auto b = copy(a.begin(), a.begin() + 5, back_inserter(c));
copy(a.begin(), a.begin() + 1, b);
```

copy_if
```c++
std::copy_if(from_vector.begin(), from_vector.end(),
                 std::back_inserter(to_vector),
                 [](int x) { return x % 3 == 0; });
```



## 重排

### unique

```c++
auto b = unique(a.begin(), a.end());
Print(a);
// unique 算法操作的是迭代器，为了删除元素，只能使用容器操作
a.erase(b, a.end());
Print(a);
```
### sort

## 定制操作

