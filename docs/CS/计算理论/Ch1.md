---
tags:
  - doing
  - class/计算理论
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# Sets Relation and Languages

## Sets

- Power Set
- Partition

## Relation & Function

- Ordered Pair (a, b)
- 笛卡尔积 A $×$ B
- Domain Range 
- **Function** 
	- Injective  : one-to-one function
	- Surjective : onto function
	- Bijective : one-to-one correspondence 一一对应
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409141022532.png)
- Special Type
	- Graph & Matrix 可以相互转化
- **Property of relation**
	- Reflective
	- Transitive
	- Symmetric
	- Antisymmetric

>[!info] 
>自反性要考虑所有的元素，如果针对一个 single 的自反，整个 Relation 是不具有自反性的
>
>对称和反对称都只考虑部分元素，针对 pair $(A,B)\subseteq R \land {A\neq}B$
>所以这两个属性可以同时满足（只有对角线存在元素）

- Equivalence Relation
满足自反性，传递性，对称性的关系. 可以看到会有很多 cluster
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409141100819.png)

- Equivalence Class
$[x]=\{y\in A:y\ R\ x\}$
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409141100377.png)
- Partition 一个等价关系的等价类，就是它的天然划分
- Partial Order 偏序关系 $\leq$
	- Reflexive
	- Transitive
	- Antisymmetric 

>[!example] 
>正整数的除法

>[!info] 

- Total Order
	- 增加了一个 strongly connected 的条件，$\forall a,b,either\ a\leq b,or\ b\leq a$，不会再存在多个 cluster

## Finite & Infinite

- Equinumerous 等势
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409141113870.png)
- 不存在 card 在自然数和实数集中间的 set
- Cantor \`s Theorem

>Card (A) <= Card (P (A)) 对于所有 A 成立

### 证明等势的思路

- 图像  dovetailing 证明可以被自然数表示
- Bijection 寻找一一对应的函数
- Two injection 证明 $|A|\geq|B|,|B|\geq|A|$
