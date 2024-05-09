# Chapter 7 Relational Database Design

## Features of Good Relational Design

**不规范的关系模式**

![image-20240417171423179](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171714330.png)

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171742487.png)

**函数依赖 | functional dependency**

- 无损连接的分解
  分解 之后 至少有一个公共属性，**且是其中一个关系的` key`**(不是`primary`)

![image-20240417220300169](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172203223.png)

- **lossy** **decomposition**

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171721162.png)

- 可以根据自然连接后能否恢复来判断（有可能会变多/少）

## Functional Dependency

![image-20240417173643198](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171736288.png)

![image-20240417174115459](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171741535.png)

**Trivial case**

![image-20240417174033016](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404171740061.png)

- 没有实际的信息存在
- 通常情况下，我们隐含这样的假设：这个函数依赖不是Trivial的（非平凡的）

### **Closure(闭包)** 

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172021770.png)

#### 公理 | Armstrong`s Axioms

![image-20240417202212761](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172022807.png)

> **Example**
>
> ![image-20240417203418867](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172034926.png)

#### 推论

![image-20240417203515667](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172035706.png)

- **消去律**   消去某一边的公共属性

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172037780.png)

#### 属性的闭包

- 就是某个属性A可以决定其他哪些属性，这些属性就是A的闭包

![image-20240417204205381](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172042460.png)

```mermaid
graph LR
A --> B
B-->C
B-->D
```

**<u>Uses</u>**

![image-20240417205219151](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172052211.png)

#### **Canonical Cover（正则覆盖）**

- 化简，使得不存在多余的属性和函数依赖

![image-20240417205621149](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172056222.png)

> Example
>
> 第一种方法往往是计算程序使用的，人工使用这种方法并不高效
>
> ![image-20240417210033405](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172100464.png)
>
> ![image-20240417210019484](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172100534.png)
>
> ??? example "example"
>     ![image-20240417210343263](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172103326.png)

### Boyce-Codd Normal Form  |  BCNF

- 任何一条函数依赖要么是平凡的，要么左边是key  ==  任何一条非平凡的左边都是key

![image-20240417212740282](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172127343.png)

![image-20240417211430276](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172114352.png)

??? example "example"
    ![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172123576.png)

### **Dependency Preservation**

**定义**

- 不需要在分解后的$R_i$之间建立新的关联（通过自然连接重新建立属性间的联系）就可以得到所有的`DF（Dependency Func）`

![image-20240417215323742](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172153784.png)

??? example "example"
    ![image-20240417215505778](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172155840.png)
    $(F_1 \cup F_2)^+ <>F^+$

??? example  "execise"
    ![image-20240417220707427](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172207505.png)

