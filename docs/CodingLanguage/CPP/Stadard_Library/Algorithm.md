# Algorithm

!!! abstract
    标准库提供了一组算法，大多数都独立于容器存在。
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

> 要确保第二个序列的长度>=第一个

### fill
<span class="box box-yellow">写操作</span>

!!! warning "warning"
    writing操作默认有足够的空间容纳写的元素

    为了保证在写入元素时存在足够的空间，可以使用[`back_inserter`](../基础.md)

`fill(begin,end,element);`

`fill_n(iter,n,element)`



