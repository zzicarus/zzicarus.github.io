# 查询处理

## Basic Step

![image-20240523091317582](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405230913806.png)

- **Parsing** and **Translation**

    - Translate the query into **its internal form**. This is then **translated into relational algebra.**
    - Parser checks syntax, verifies relations  解析器

    - **Optimization**
    - Amongst all equivalent evaluation plans **choose the one with lowest cost.** 

- **Evaluation**

    - The **query-execution engine** takes a **query-evaluation plan**, executes that plan, and returns the answers to the query.

An **evaluation plan** defines exactly what algorithm is used for each operation, and how the execution of the operations is coordinated.

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405230917997.png" alt="image-20240523091730860" style="zoom:33%;" />

## Measures of Query Cost

- Resource Consumption

![image-20240523092041613](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405230920786.png)

- We often use worst case estimates, assuming only the minimum amount of memory needed for the operation is available

## Selection Operation | External Sort-Merge

https://note.hobbitqia.cc/DB/db11/#selection-operation

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251119700.png" alt="image-20240525111932603" style="zoom: 80%;" />

## Sorting 

> 数据库主要考虑需要外排的情况

We may build an index on the relation, and then use the index to read the relation in sorted order. May lead to one disk block access for each tuple.

### External Sort-Merge

- Build Runs 得到 $\lceil{\frac{B_r}{M}}\rceil$ Runs  需要$2B_r$次Transfer  ，$2\lceil{\frac{B_r}{M}}\rceil$次Seek（这里应该是物理存储临近
- Merge Runs  归并次数 $\lceil{\log_{\lfloor{\frac{M}{B_b}-1}\rfloor}{B_r/M}}\rceil$ 除了最后一次归并，其余每次都是$2B_r$次Transfer
    Seek：每一次$2\lceil{\frac{B_r}{B_b}}\rceil$​
- $B_b$把$B_b$个缓冲块分配给 **每个** 归并段

**Cost of Transfer**
$$
2 *B_r* \lceil{\log_{\lfloor{\frac{M}{B_b}-1}\rfloor}{B_r/M}}\rceil  + 2B_r-B_r
$$
**Cost of Seek**
$$
2\lceil{\frac{B_r}{B_b}}\rceil*\lceil{\log_{\lfloor{\frac{M}{B_b}-1}\rfloor}{B_r/M}}\rceil+2\lceil{\frac{B_r}{M}}\rceil - \lceil{\frac{B_r}{B_b}}\rceil\\
=\lceil{\frac{B_r}{B_b}}\rceil*(Merge-1)+build\ Seek
$$

## Join Operation 

### Nested-loop join

![image-20240525114950588](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251149689.png)

**cost**

![image-20240525115244962](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251152053.png)

这里有一个隐含的假设：内层的数据可以通过一次seek获取全部

- Transfer 
- Seek  外层需要seek $b_r$ times，内层其实是$n_r*b_s$



### Block nested-loop join

![image-20240525115701344](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251157427.png)

尽可能把小的放在外层

**Improvement**

对外层使用更多的缓冲块

![image-20240525115820333](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251158410.png)

### Indexed nested-loop join

![image-20240525120313621](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251203724.png)

• Where *c* is the cost of traversing index and fetching all  matching *s* tuples for one tuple of *r*

• *c* can be estimated as cost of a single selection on *s* using the  join condition.

### Merge-Join

- Can be used only for equi-joins and natural joins

![image-20240523192825321](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405231928410.png)

- 直接对辅助索引的值排序代价太大了
- 先把有序关系和B+ Tree的叶子进行Merge
- 按照物理地址对上述结果排序，使之能够更加方便地进行物理访问
- 进行Merge，用真实物理地址替换

![image-20240525120619474](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405251206556.png)

- 按照地址排序，使得地址连续，方便从一个Block中取出

### Hash-join

- 用同一个哈希函数进行划分  分别进行一次完整的读入写回
- 为每个$S_i$​构造一个散列索引（内存中），这个散列函数必须与之前的不同
    - 小的表要能放在内存中
- 用$R_i$中的每一个tuple去探查

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232239307.png" alt="image-20240523223923207" style="zoom: 33%;" />

![image-20240523224445909](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232244979.png)

![image-20240523224140435](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232241512.png)

- 这里使用的散列函数必须与之前使用的H不同

![image-20240523230126575](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232301630.png)



#### 递归划分 | recursive partitioning

> 没有足够的缓冲块支撑一次完成所有的partition

多次产生更小的划分。每一趟的散列函数都不同，不断重复输入的分裂过程直到构造用输入关系的每个划分都能被内存容纳为止
$$
M>b_s/M+1\\ \text{缓冲区大小大于每个partition的大小 + 一个输出块}\\
M>\sqrt {b_s}
$$


#### 溢出处理 | hash-table overflow

> 散列索引大于主存

**skewed**  划分不均匀  if some partitions have significantly more  tuples than some others

**fudge factor** 避让因子  使得每个划分的期望大小比内存容量略小，增加的划分个数称之为避让银子

- **溢出分解 | resolution**   构造阶段，$s_i$​太大，用另一个hash func进行进一步划分；同时$r_i$必须进行同样的划分

- **溢出避免 | avoidance**  在构造阶段进行谨慎的划分
     partition build relation into many partitions, **then combine them**

#### cost

![image-20240523232851347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232328437.png)

!!! example "example"
	![image-20240523234114405](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232341606.png)

#### 混合散列连接  | Hybrid hash-join

![image-20240523234732122](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405232347325.png)

把一个$S_0$存放在内存中，之后读入$R_i$，对于$R_0$，就只需要读入之后直接去和$s_0$“连接”，之后不需要写回，直接丢弃

#### 复杂连接

$ \Pi_{T.branch_name} ( (\Pi_{branch_name, assets}(\rho_T(branch))) \bowtie_{T.assets > S.assets} (\Pi_{assets} (\sigma_{branch_city = 'Brooklyn'}(\rho_S(branch))))) $

$\Pi_{}$

## other operation

### Project

### 

## **Evaluation of Expressions**

### Materialized | 物化

- 从最底层开始
- 需要存储临时结果

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240907340.png) 

### pipeline | 流水线

**demand driven**

- pull
- 状态的维护依赖于算子 operator，`open() next() close()`

![image-20240524091117044](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240911221.png)

**producer driven**

- push 从底层往上push

![image-20240524091145791](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240911977.png)

**Blocking operations | 阻塞操作**: cannot generate any output until all input is consumed

**Pipeline stages**: 

- All operations in a stage run concurrently
- A stage can start only after preceding stages have completed  execution

![image-20240524091526277](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240915417.png)

**Double-pipeline**

![image-20240524091806308](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240918556.png)

## 加速Memory中的查询过程

![image-20240524092659753](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240926981.png)

![image-20240524092643279](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240926547.png)