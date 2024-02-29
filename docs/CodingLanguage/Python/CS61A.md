# CS61A

!!! abstract "概述"

    这个文档记录了之前学习CS61A的一部分笔记，当时并没有听完所有课，这份笔记不算特别完善。（当然有一部分是觉得没什么记的必要）

    不得不说，这个课作为我上过的第一门国外网课，它的课程网站、作业OJ、包括指导教程都令我印象挺深的。（对比下来，某三本的课程指导，emm，依托...）

!!! info "资源"

    **FALL 2020**

    [CS 61A Fall 2020](https://inst.eecs.berkeley.edu/~cs61a/fa20/)
    
    **ANSEWR**
    
    [GitHub - HobbitQia/CS61A-Fall-2020: My solutions for CS61A Fall 2020.](https://github.com/HobbitQia/CS61A-Fall-2020)
    
    **Python Tutor**
    
    [Online Python Tutor - Composing Programs - Python 3](https://pythontutor.com/cp/composingprograms.html#mode=edit)
    
    **TextBook**
    
    [Composing Programs](http://www.composingprograms.com/)


## Chapter 1: Building Abstractions with Function

## 基本特征

### **Features**

- turediv   /     浮点数
- floordiv  //    整除

---

- 可以有多个返回值

def divide_exact(n,d)
return n//d, n%d

### 字符串

1. py 没有单独的字符类型，一个字符就是长度为 1 的字符串
2. Python 中的字符串不能改变
3. 反斜杠可以用来转义，使用 **r** 可以让反斜杠不发生转义。 如 **r"this is a line with \n"** 则 **\n** 会显示，并不是换行。（raw string）
4. 字符串的截取的语法格式如下：**变量[头下标:尾下标:步长]**

```python
str = '123456789'
print(str[0:-1])# 输出第一个到倒数第二个的所有字符
>>> 12345678
print(str[0])# 输出字符串第一个字符
>>> 1
print(str[2:5])# 输出从第三个开始到第六个的字符（不包含）print(str[2:])# 输出从第三个开始后的所有字符
>>> 345
print(str[1:5:2])# 输出从第二个开始到第五个且每隔一个的字符（步长为2）
>>> 24
```

5. 字符串可以用 **+** 运算符连接在一起，用 ***** 运算符重复

```python
print(ptr * 2)
```

### 交互

- **Print 和 return**

print输出的是 ‘’引号内的

return 所有

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328856.png)

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328857.png)

## environment

### ![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328858.png)

- environment is combined with many frames.
- global frame and others(local frame)
- And at one time, there\`s only one frame**( the program can\`t be in two distinct frames )**
- 定义并不会创建frame 只有当运行到函数时才会创建

### 高阶函数的 Environment

#### Nested / Higher

```python
# 一个嵌套函数
# make_adder(5) 将返回一个函数（+5的adder）
def compose(f,g):
 def h(x):
        return f(g(x))
    return h
def make_adder(x):
    def adder(y):
        return y + x
    return adder
>>> compose(f,make_adder(5))(4)  ```完成调用
```

```python
def print_sums(n):
    """Print all sums of arguments of repeated calls.
  n 为总和  k 为下一个加和数字
    >>> f = print_sums(1)(2)(3)(4)(5)
    1
    3
    6
    10
    15
    """
    print(n)
    def next_sum(k):
        return print_sums(n+k)
    return next_sum
```

#### 如何绘制

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328859.png)
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328860.png)

## funciton

- **from operator import add,mul   //**引入函数（build-in）
- docstring  ``````      **( HELP )**   comments #   注释

![这里的n是一个default values，可以改变，同样也是进入函数之后才创建](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328861.png)
**Print and None**

- Print 返回值为None 
**None**在py 中不是一个数值表达  ==>  NoneType 和 int 不能进行计算（type Error）

**Control**![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328862.png)

**bool ：**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328863.png)
对于 and 和 or 他们总是返回最后一个evaluate的对象，如果判断对象不是booleans，将返回数字；Ture and 13  will return 13 but not True

**iteration 迭代：**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328864.png)

**Test ：**
**Assertions**在False时 输出后面的字符串  **‘   ’**或者**“   ”**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328865.png)

**Doctest**

- 全局

**from doctest import testmod**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328866.png)

- 单个函数

**from doctest import run_docstring_examples**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328867.png)


- **文件**

**python3 -m doctest <python_source_file>**
运行所有 doctests

**高阶函数**

- **Currying**  只含有一个 参数

例如，g (x) (y)  等效于  f (x , y)  , 这个转换的过程就被称为currying
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328868.png)

```python
from operator import add, mul
def curry2(f):
    def g(x):
        def h(y):
            return f(x, y)
        return h
    return g
m = curry2(add)
add_three = m(3)
add_three(4)
m(2)(1)
```

- **Lambda Expressions**

定义此类函数时没有 intrinsic name

```python
b = lambda x: lambda: x  # Lambdas can return other lambdas!
c = b(88)
>>> c
Function
>>> c()
88
```

- **Decorators  修饰符**

用于更好地使用高阶函数
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328869.png)
triple 绑定的是 trace 在调用triple之后绑定的返回值
![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328870.png)
:::

```python
def print_sum(n):
    //打印n个数的总和
	print(n)
 def f(k):
     return print_sum(n+k)
 return f

>>> print_sum(3)(5)(7)
n  k   print_sum(3) f(5)
3  5 print_sum(8) f(7)
8  7 print_sum(15) f
```

### 含有任意参数的函数
```python
def average(*args):
        k,sum = 0,0
        while k < trials_count:
            sum += original_function(*args) 
            k += 1
        return sum / trials_count
    return average
```

### 修饰

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328871.png)

## Recursive Function

### 基本构成

1. basic case
2. recursive case

例如，f n+1 = f n  +  f (n-1)

3. 借助 helper 函数  操纵更多参数

## ** Lambda表示

### 基础使用

### Y算子/不动点

## Chapter 2 : Bulilding Abstractions with Data

## · Sequences

### Lists

```python
# 基本运算
>>> digits = [1, 8, 2, 8]
>>> len(digits)
4
>>> digits[3]
8

>>> [2, 7] + digits * 2  // mul 和 add 对 list
[2, 7, 1, 8, 2, 8, 1, 8, 2, 8]

>>> pairs = [[10, 20], [30, 40]] // 包含list的list 
>>> pairs[1]
[30, 40]
>>> pairs[1][0]
30
# unpack pair = [10,20]
1. pair[0]
2. x,y = pair
3.  >>> from operator import getitem
 >>> getitem(pair, 0)
 10

```

### Sequence Iteration

```python
for <name> in <expression>:
 <suite>
```

**unpacking iteration**

```python
# 将list中的多个值赋给变量
>>> pairs = [[1, 2], [2, 2], [2, 3], [4, 4]] // list含有相同数目元素
>>> for x, y in pairs:
        if x == y:
            same_count = same_count + 1
>>> same_count
2
```

**range**

```python
>>> range(5,8)  //包括 5 excluding 8  
>>> list(range(3))  // range() 
[0,1,2]
>>> for _ in range(3):  // _ 表示不再suit中使用的变量  自动从 0 开始
        print('Go Bears!')
```

### Sequence Processing

:::info
**List Comprehensions**
:::

```python
[<map expression> for <name> in <sequence expression> if <filter expression>]
# 注意是在【】中进行，生成新的 List 
>>> odds = [1, 3, 5, 7, 9]
>>> [x+1 for x in odds if ...]
[2, 4, 6, 8, 10]
# Aggregation
sum max min , etc
```

:::info
**Higher-Order Function**
:::

```python
# reduce 重复计算
from functools import reduce
reduce(fn_reduce,iterable,initial)
# map 
r = map(fn_map,iterable)
list(r)
# 
```

:::info
**Conventional Names**
:::

```python
>>> apply_to_all = lambda map_fn, s: list(map(map_fn, s))
>>> keep_if = lambda filter_fn, s: list(filter(filter_fn, s))
```

:::info
**Sequence Abstraction**
:::

```python
lists = [0,1,2,3,4,5,6,7]
# Membership
x in lists / not in
# Slicing
list[0:]
# Processing
1. sum(iterative[,start])
2. max(iterative[,key = function])
3. all(iterative)  -> bool()
```

### Trees

- Trees.  有一个 rootlabel 和 branches   它本身是一种用递归定义的数据结构
- 形式：[label , branches = [] ]   [1,[  [2 , [3]] , [4,[5]] , [6,[7]] ]]

尤其注意branches的格式问题
也可以使用字典形式表示tree这种数据结构

- 对 tree 的遍历经常用到  

```python
for b in branches(t):
```

若已知为二叉树，也可以不断分为 left right 两个节点

- `h = **[**helper(branch,height + 1) for branch in branches(tree)**]**` 这样的语句会导致之后所有的返回值形成很深层次的嵌套`**[[2], 1, [[[[5]]]]]**`**最好在每一层级都“解压”**`**max(t)**`这样之后返回的才是数值

#### Data abstraction of trees

- 此处的组件并不通过递归形成一个tree，只是单纯tree的component
- 注意 branches 的写法

```python
## the first level for abstraction
# constructor
>>> def tree(root_label, branches=[]):
        for branch in branches:
            assert is_tree(branch), 'branches must be trees'
        return [root_label] + list(branches)
# selector
>>> def label(tree):
        return tree[0]
>>> def branches(tree):
        return tree[1:]

## the second
>>> def is_tree(tree):
        if type(tree) != list or len(tree) < 1:
            return False
        for branch in branches(tree):
            if not is_tree(branch):
                return False
        return True
>>> def is_leaf(tree):
        return not branches(tree)
```

- partition的tree做法

```python
def partition_tree(n, m):
        """Return a partition tree of n using parts of up to m."""
        if n == 0:
            return tree(True)
        elif n < 0 or m == 0:
            return tree(False)
        else:
            left = partition_tree(n-m, m)
            right = partition_tree(n, m-1)
            return tree(m, [left, right])
# recursion tree in prefix order
def print_parts(tree, partition=[]):
    if is_leaf(tree):
        if label(tree):
            print(' + '.join(partition))
    else:
        left, right = branches(tree)
        m = str(label(tree))
        print_parts(left, partition + [m])
        print_parts(right, partition)
```

#### Excises and Application

- Add Tree
  - 考虑递归的 `Basic case` 和 `Recursive case`
  - **Hard :** 确认对应位置  
    - **Tip :** using the `zip` function

```python
zip(iterable1,iterable2,...):
 Returns a zip object, which is an iterator of tuples
 如果参数长度不一，取最短的
>>> t2
[1, [5, [6]], [9], [4, [8], [[1]]], [99]]
>>> t1 
[1, [5, [6]], [8], [9]]
>>> list(zip(t1,t2))
[(1, 1), ([5, [6]], [5, [6]]), ([8], [9]), ([9], [4, [8], [[1]]])]
```

- 形成新的Tree
- 仍然是对 rucursive 结构考虑不是很清楚. `tree : [1, [5], [6, [7]]]`, `branches` 中，每一个元素都代表一整个分支

```python
def add_tree(t1,t2):
    '''Return the addition tree of the two trees t1 and t2.
       Adding up the corresponding value, and making a tree.
       IF one branch is onlt in one tree, then it will be in the new tree
    >>> numbers = tree(1,
    ...                [tree(2,
    ...                      [tree(3),
    ...                       tree(4)]),
    ...                 tree(5,
    ...                      [tree(6,
    ...                            [tree(7)]),
    ...                       tree(8)])])
    >>> print_tree(add_trees(numbers, numbers))
    2
      4
        6
        8
      10
        12
          14
        16
    >>> print_tree(add_trees(tree(2), tree(3, [tree(4), tree(5)])))
    5
      4
      5
    >>> print_tree(add_trees(tree(2, [tree(3)]), tree(2, [tree(3), tree(4)])))
    4
      6
      4
    >>> print_tree(add_trees(tree(2, [tree(3, [tree(4), tree(5)])]), \
    tree(2, [tree(3, [tree(4)]), tree(5)])))
    4
      6
        8
        5
      5
    '''
    if is_leaf(t1) and is_leaf(t2):  
        return tree(label(t1) + label(t2))  
    elif is_leaf(t1):  
        return tree(label(t1) + label(t2), branches(t2))  
    elif is_leaf(t2):  
        return tree(label(t1) + label(t2), branches(t1))  
    else:  
        new_label = label(t1) + label(t2)  
        new_branches = [add_trees(b1, b2) for b1, b2 in zip(branches(t1), branches(t2))]  
        if len(branches(t1)) > len(branches(t2)):  
            new_branches += branches(t1)[len(branches(t2)):]  
        elif len(branches(t1)) < len(branches(t2)):  
            new_branches += branches(t2)[len(branches(t1)):]  
        return tree(new_label, new_branches)
```

-

### Linked Lists

- **定义**：与 **tree**类似，[ element ,  new_linked]

[ 2, [3, [4, 'empty']]]

-

```python
four = [1,[2,[3,[4,'empty']]]]

# constructor
empty = 'empty'

def link(label , rest):
    if is_link(rest):
        return [label,rest]
        
def first(s):
    assert is_link(s), "first only applies to linked lists."
    assert s != empty, "empty linked list has no first element."
    return s[0]
    
def rest(s):
    assert is_link(s), "first only applies to linked lists."
    assert s != empty, "empty linked list has no rest."
    return s[1]
    
# convenience
def is_link(s):
    return s == empty or (len(s) == 2 and is_link(s[1]))
    
def getitem_link(s,i):
    if i == 0:
        return first(s)
    else:
        return getitem_link( rest(s) ,i - 1)
        
def len_link(s):
    length = 0
    while s != empty:
     length += 1
        s = rest(s)
    return length

## 

## application
```

## · Data abstraction

### Abstraction barrier

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328872.png)

- 对功能进行不同的分层，其层级之间形成abstraction barrier
- 调用部分功能时不要使用过低层级，eg：add_rational( ) 中，使用 rational 、numer、denom函数作为component构建相关函数
- 其目的是为了尽可能减少修改代码时的工作量，即所谓 isolution

### Dictionary

:::info
**Basic operation**
:::

- `**创建方法**`

`**dict**(_**kwargs_)`****
`**dict**(mapping,_**kwargs_)`
`**dict**(iterable,_**kwargs_)`
`键值对  {a:1,b:2}`
`推导式  {x: x ** 2 for x in range(10)}`
`类型构造器  dict([(a,1),(b,2)])`

- `**methods**`
  - `**字典视图对象**`**动态变化，**不是 iterator 但可以通过函数产生`iter(dictview)`

`**keys()**`
`**items()**`
`**values()**`

`**popitem**()`
`**pop()**`
迭代方法：

1. 利用 `dic.items`产生一个键值对的 list `for i,j in dic.items()`
2.

```python
key -> value
dic = {'I':1,'A'：2,5:a} # 此处的a为已赋值的变量，或者'a'代表变量
>>> dic['I'] == 1
>>> dic.values()
>>> dic.key()
>>> items = dic.items()
>>> dict(items)
>>> dic.get('X',0)  # get 打印value ornot  print 0
```

:::info
**Dictionary comprehension and limitation**
:::

```python
>>> {x:x*x for x in range(10}
· key 不能重复
· key 不能是可变化的值/list/sequence
```

## · Mutable Data

- Mutable Data 用于表示动态变化的值
- py内置的numbers、string、tuple不能变化，sequence可以
- **default argument** **value** is part of a function value

```python
def f(s = []):
    s.append(5)
    return len(s)
>>> f()
1
>>> f()
2
```

### Object

- Objects are both **information and processes  (**bundling information and behavior together**)**
- Objects have **attributes,**we use dot to represent

**<expression>.<name>**这里的name相当于 object 的一种属性，只在 **.** 后有用

- **method   相当于**function-valued attribute
- **In python, all values are objects**

#### Sequence Object

```python
# operation on data 
# share and identity
''' = 并没有创建新的object 故而 suits 与 chinese 指向相同的object'''
chinese = ['coin', 'string', 'myriad']  # A list literal
suits = chinese                         # Two names refer to the same list

## 移除
suits.pop()             # Remove and return the final element
suits.remove('string')  # Remove the first element that equals the argument

## 增添
suits.append('cup')              # Add an element to the end
suits.extend(['sword', 'club'])  # Add all elements of a sequence to the end

## 更改  mutable
suits[2] = 'spade'  # Replace an element
suits[0:2] = ['heart', 'diamond']  # Replace a slice

### slicing 切片时不是mutable的
a = suits[0:2]

## 复制  
'使用constructor：list创建一个副本即一个新变量'
nested = list(suits)
nested[0] = suits  # 指向suits列表

## check
'identity is much stronger than equality'
'使用 is 或者 is not 判断指向的是否为同一对象'
>>> suits is nested[0]
True
```

```python
# comprehension

'创建新的list'
## slicing
suits[1:]

## complicated examples
'引用自身的list'
>>> t = [1,2,3]
>>> t[1:3] = [t]
[1,[...]]
'这里的[...]就是这个 list 本身 '
>>>t.extend(t)
[1,[...],1,[...]]
>>> t[1]
[1,[...],1,[...]]

>>> t = [[1,2],[3,4]]
>>> t[0].append(t[1:2])    # t[1:2] ->  [[3,4]]  
[[1,2,[[3,4]],[3,4]]
```

**需要注意一点：以 list 作为元素时，是以占位符形式展现的**

```python
a = [0,1,2,3,4,[5,6]]
b = a
c = b[:]

print(c is b)
print(c[5] is b[5])
```

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401212328873.png)

#### Tuples

- 元组 具有类似list的操作，但是元组本身不可以直接改变（unmutable）
- 可以包括任何类型的对象
- 可以对对象进行改变（mutable data）
- 创建，使用  **， （ ）**

```python
>>> 1, 2 + 3
(1, 5)
>>> ("the", 1, ("and", "only"))
('the', 1, ('and', 'only'))
>>> type( (10, 20) )
<class 'tuple'>

>>> ()    # 0 elements
()
>>> (10,) # 1 element
(10,)
```

#### Dictionary Object

Dictionaries do have some restrictions:

- A **key** of a dictionary **cannot be or contain a mutable value.**
- There can be **at most one value** for a given key.

```python
# 
##
'普通的改变或者增加可以通过赋值语句实现'

## methods：keys, values, and items all return iterable values.
>>> sum(dic.values())

'通过键值对创建dict'
>>> dict([(3, 9), (4, 16), (5, 25)])
{3: 9, 4: 16, 5: 25}

## methods
'get: 如果没有该键值对，返回 0 '
>>> numerals.get('V', 0)
5
```

#### String

- [Unicode,ASCII,UTF-8的区别-腾讯云开发者社区-腾讯云](https://cloud.tencent.com/developer/article/1441294)
:::info
**ASCII :** 一个字节  英文编码
**Unicode :**两个字节  所有编码统一
**UTF - 8 :**自动决定字节数

**TIP :**

- **内存**统一使用 **unicode** 编码
:::

### Local State

- **nonlocal statement** 必须使用在已经赋值后的变量前[** in nonlocal frame  **]

`no binging for nonlocal '' found`

- 一个变量**不能**先访问 `non-local frame`之后再在 `local frame` 中赋值

`name '' is parameter and nonlocal`

- 绑定的是第一个 `non-local frame` 中的name   【enclosing scope】
- 【**referential transparency**】expression -> 用表达式的值替换表达式之后不影响整个 program

【**violate ...**】mutable operation

- **Instances**：

```python
def make_withdraw(balance):
    def withdraw(amount):
        nonlocal balance
        if amount > balance:
            return 'Insufficient funds'
        balance = balance - amount
        return balance
    return withdraw
```

### Implementing on List

This part is going to introduce one way to creat mutable data structure by mutable function

- **Dispatch Function :** the message determines the behavior of the function
-

## · Object-Oriented Programming

## · Implementing Classes and Objects

## · Object Abstraction

#### Objects And Classes

- `instance attribute`/`fileds`/`instance variables`/`properties`
- `methods`**: functions** that operate on the object or perform object-specific computations are called methods
- `attribute`/`class variables`/`static variables`：difined without the range of methods.          It is **shared** by all the class and among all instances defined
- `instance attribute`**specific** attributes for one instance
  - `**区分**`对于 instance ， `object`访问对象时优先访问`instance attr`，未寻找到才访问`class attribute`也就是说，可以存在一个`attr`只存在于某个特定实例而不存在于`class`

#### Creating a class

```python
class Account:
# definitiate a new method
    def __init__(self, account_holder):
# self is bound to the newly defined class
        self.balance = 0
        self.holder = account_holder
    def deposit(self, amount):
        self.balance = self.balance + amount
        return self.balance
    def withdraw(self, amount):
        if amount > self.balance:
            return 'Insufficient funds'
        self.balance = self.balance - amount
        return self.balance
        
a = Account('Kirk')
# 两种不同调用 function 和 method 的方法
'根据class 和 instance 的不同，返回值也不同'
>>> Account.deposit(spock_account, 1001)  # The deposit function takes 2 arguments
1011
>>> spock_account.deposit(1000)           # The deposit method takes 1 argument
2011
```

```python
getattr(instance,attr)
'Return the value of calling it which is identical to the dot expression'
# the attr must be a string
getattr(a,'balance')

hasattr(instance,attr)
'''return True or False'''

```

- As an attribute of a **class**, a **method** is just a **function**, but as an **attribute of an instance**, it is a **bound method.   区别：**当`method`被调用时，self 将自动绑定这个`object`
- **Python's convention：** dictates that if an attribute name starts with an **underscore**, it should only be **accessed within methods of the class itself,** rather than by users of the class.

### Inheritance

- `is-a`类继承 `has-a`聚合
- 从父类继承所有attr，但是可以override

```python
>>> class CheckingAccount(Account):
    """A bank account that charges for withdrawals."""
    withdraw_charge = 1
    interest = 0.01
    def withdraw(self, amount):
        return Account.withdraw(self, amount + self.withdraw_charge)
```

#### Multiple Inheritance

- For non-ambigious case, it works nuturally.
- For ambigious case, for example, both the two have one same name, then the order matters

```python
class SavingsAccount(Account):
    deposit_charge = 2
    def deposit(self, amount):
        return Account.deposit(self, amount - self.deposit_charge)
class AsSeenOnTVAccount(CheckingAccount, SavingsAccount):
    def __init__(self, account_holder):
        self.holder = account_holder
        self.balance = 1           # A free dollar!

# one way to find out the order of inheritance
>>> [c.__name__ for c in AsSeenOnTVAccount.mro()]
['AsSeenOnTVAccount', 'CheckingAccount', 'SavingsAccount', 'Account', 'object']
```

## · Efficiency

## · Recursive Objects

## Chapter 4 : Data Processing

## Implicit Sequence

### Iterator

- **components**
  - **a mechanism **for** retrieving the next** element in the sequence being processed and
  - **a mechanism** for **signaling that the end**of the sequence has been reached no further elements remain
- Calling `**iter**` on an iterator will return that iterator, **not a copy**

```python
>>> next(iterator)
7
>>> next(iterator)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
>>> try:
        next(iterator)
    except StopIteration:
        print('No more values')
No more values
```

#### Build-in Iterator

- Taking an iterator and return an iterator
- `lazy processing`调用iterator function 不会直接计算结果，返回一个iterator，只有当使用某个数值时才会发生计算. 如：下例中，若之后再次调用`doubled`相关，将会出错，因为这个`iterator`已经到达尽头

```python
>>> def double_and_print(x):
        print('***', x, '=>', 2*x, '***')
        return 2*x
>>> s = range(3, 7)
>>> doubled = map(double_and_print, s)  # double_and_print not yet called
>>> next(doubled)                       # double_and_print called once
*** 3 => 6 ***
6
>>> next(doubled)                       # double_and_print called again
*** 4 => 8 ***
8
>>> list(doubled)                       # double_and_print called twice more
*** 5 => 10 ***
*** 6 => 12 ***
[10, 12]
```

`zip`
`map`
`reversed`

### Iterables

- Any value that can produce iterators is called an`_**iterable**_** value**`.
- 对于一些本身无序的结构，如字典和集合，Python 将会内置一个顺序，使得`iter``next`可以正常运行
- 但如果改动或删除了`key`，将会出现新顺序，之前产生的`iter`失效
- 在高版本py中字典已经有了顺序


### Generator

- is one type of **special iterator**
- returned by a special class of function called a _**generator function**_.
- 每次调用直到到达 `yield` 时`return` 一个 `generator`，并记录此次运行的 name 和 value，下一次从此次结束处重复操作

```python
>>> def letters_generator():
        current = 'a'
        while current <= 'd':
            yield current
            current = chr(ord(current)+1)
>>> for letter in letters_generator():
        print(letter)
a
b
c
d
```

- 产生可重复使用的 iterable （Creating Iterables with Yield）

```python
class LettersWithYield:
    def __init__(self, start='a', end='e'):
        self.start = start
        self.end = end
    def __iter__(self):
        next_letter = self.start
        while next_letter < self.end:
            yield next_letter
            next_letter = chr(ord(next_letter)+1)


class LetterIter:
    """An iterator over letters of the alphabet in ASCII order."""
    def __init__(self, start='a', end='e'):
        self.next_letter = start
        self.end = end
    def __next__(self):
        if self.next_letter == self.end:
            raise StopIteration
        letter = self.next_letter
        self.next_letter = chr(ord(letter)+1)
        return letter
```

## Library

### Standard Library

## Q & A

### 浮点数问题

- 保留位数

使用 round 函数  四舍五入类型的函数
如果有 0 存在自动舍去多余的0

```python
>>> round( 4.000 , 2 )
4.0
>>> round(4,2)
4
>>> round(float(4),2)
4.0
```

-

### 其他常用函数的细节

- max & min

```python
# 原型
max(iterable, *, default, key=None)
''' 返回第一个找到的max值
 iterable为空时返回default
    key为指定的 实际传入list.sort()的参数
'''

# 应用 
  '''按字典顺序比较'''
  ## 比较字符串  
>>> max('1', '9', '10', '100') # 返回多个字符串中最大的字符串
'9'
>>> max('asdxyz')
'z'
  ## 比较列表
>>> min(['8',4],['8',4,'2']) # 返回多个列表中最小的列表
['8', 4]
>>> min(('8',4, '3'),('8',4,'2')) # 返回多个元组中最小的元组
('8', 4, '2')
  ## 比较字典  注意 返回值为 键
>>> d = {'x':5, 'y':7, 'z':3}
>>> min(d) # 返回字典元素中的最小值，结果是最小的键
'x'
>>> min(d , key = lambda x:d[x])
'z'
```

- print函数

### 一些思考方式

- 分cases考虑递归问题  tree的想法  
