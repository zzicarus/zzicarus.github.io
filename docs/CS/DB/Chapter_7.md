# Chapter 7 **Relational Database Design**

## Features of Good Relational Design

**不规范的关系模式**

> 同时也是要去decompose一个关系模式的原因

![image-20240417171423179](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151294.png)

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151388.png)

**函数依赖 | functional dependency**

```mermaid
graph
    2[candidate key]
    3[primary key]
    subgraph "super key"
    2
    2 -- one -->3
    end
```

- 无损连接的定义
  自然连接之后等于原组合

- 无损连接的分解

  分解 之后 至少有一个**公共属性**，**且是其中一个关系的` key`**(不是`primary`)
  
  这里是一个充分条件，而不是必要的：
  
  $证明的思路\\ R_1\cap R_2\to R_1 \\or \\ R_1\cap R_2\to R_2$​

![image-20240417220300169](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151535.png)

- **lossy** **decomposition**

  > 原因在于name属性不是一个候补键，不能决定其他属性

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151645.png)

- 可以根据自然连接后能否恢复来判断（有可能会变多/少）

## Functional Dependency

> 就是一种 constraint 

![image-20240417173643198](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151804.png)

![image-20240417174115459](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151020.png)

**Trivial case**

![image-20240417174033016](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151050.png)

- 没有实际的信息存在
- 通常情况下，我们隐含这样的假设：这个函数依赖不是Trivial的（非平凡的）

### Closure | 闭包

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151340.png)

#### 公理 | Armstrong`s Axioms

![image-20240417202212761](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151386.png)

- **推论**

![image-20240417203515667](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151567.png)
$$
1 \ \ \  \alpha \to \beta,\alpha\to\gamma \Rightarrow \alpha\to\alpha\beta,\alpha\beta\to\beta\gamma\Rightarrow\alpha\to\beta\gamma \\
2 \ \ \ apply\ tansitive\ law \\
3 \ \ \  apply\ tansitive\ law \\
$$


- **消去律**   消去某一边的公共属性

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151645.png)

> Example
>
> ![image-20240417203418867](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151753.png)



#### 属性的闭包

- 就是某个属性A可以决定其他哪些属性，这些属性就是A的闭包

![image-20240417204205381](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151997.png)

```mermaid
graph LR
A --> B
B-->C
B-->D
```

!!! info "uses"
	![image-20240417205219151](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151030.png)
	- 用于计算函数依赖 F 的闭包
	![image-20240424131656647](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404241317775.png)

#### **Canonical Cover | 正则覆盖**

- 化简，使得不存在多余的属性和函数依赖

![image-20240417205621149](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151319.png)

![image-20240616151649350](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406161516574.png)

- **Extraneous Attributes(无关属性)**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151444.png" style="zoom:50%;" />

> Example
>
> 第一种方法往往是计算程序使用的，人工使用这种方法并不高效
>
> ![image-20240417210033405](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151532.png)
>
> ![image-20240417210019484](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172100534.png)
>
> ??? example "example"
> 	![image-20240417210343263](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172103326.png)

## **Boyce-**Codd **Normal Form**  |  BCNF

- 任何一条函数依赖要么是平凡的，要么左边是key  ==  任何一条非平凡的左边都是`super key`

!!! warning "Warning"
	不是指$\alpha\to\beta 中的\alpha$是key的一部分，而是它本身就可以决定其他所有

- **转换为BCNF**
  - 把违反定义的Func拿出来，保持无损去分解


![image-20240417212740282](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172127343.png)

![image-20240417211430276](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172114352.png)

??? example "example"
	![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151203.png)

### How good is BCNF

![image-20240424140935976](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404241409050.png)

- 是BCNF但是仍然存在问题 <= 存在多值依赖且还有其他属性
- 使用 4-NF， 见 [多值依赖](## Multivalued Dependencies)

## **Dependency Preservation**

**定义**

- 不需要在分解后的$R_i$之间建立新的关联（通过自然连接重新建立属性间的联系）就可以得到所有的`DF（Dependency Func）`

![image-20240417215323742](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151718.png)

??? example "example"
	![image-20240417215505778](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151699.png)
	$(F_1 \cup F_2)^+ <>F^+$

??? example  "execise"
	![image-20240417220707427](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404172207505.png)
	![image-20240424134702063](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151636.png)
	- BCNF分解的时候不需要去管函数依赖的问题

## Third Normal Form

!!! info "定义"
	![image-20240418103242415](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151685.png)

**算法**

![image-20240424135832366](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151032.png)

- 生成正则覆盖

- 对所有的函数依赖生成关系模式

- 检测是否有关系模式包含`candidate key`，**一定要注意自始至终没有在函数依赖中出现的属性！**

!!! example "example"
$$
schema(A,B,C,D,E,G)
\\A\to BCD
\\BC\to DE
\\B\to D
\\D\to A
\\G这个属性没有在上述函数依赖中出现
$$

> Q1 : 求BCNF
>
> 通过求A、BC、B、D的闭包，可以发现他们都相同(ABCDE)，这个时候一定不要想当然的认为他们满足BCNF的条件，**题中的FG是孤立的元素**
>
> $R_1=(A,B,C,D)\ left = AEG$
> 由于$A^+=ABCDE,所有这里有函数依赖A\to E成立$
> $R_2=(A,E),R_3=(A,G)$


![image-20240424140558232](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151134.png)

## **Multivalued Dependencies**

**definition**

![image-20240424141641463](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151487.png)

![image-20240424141536402](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151801.png)

> 函数依赖是多值依赖的特殊形式

### 4 NF

![image-20240424141812366](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151880.png)

- 平凡的多值依赖
- α是`super key`

!!! example "ER graph"
	![image-20240424142601117](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151061.png)

## Process

1. 设计ER Graph，由ER图转为关系模式，不需要再去normalize
2. 不设计，之后再去normalize

**引入冗余，保持性能**

![image-20240424142936843](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091151179.png)
