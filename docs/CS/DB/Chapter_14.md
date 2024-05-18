# Indexing

## Basic

![image-20240514211757292](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405142117441.png)

**Evaluation**

- Access Type
	- Point query: records with **a specified value** in the attribute
	- Range query: records with an attribute value **falling in a specified range of values**.

- Access time
- insertion time  包括找到插入位置、更新索引结构的时间
- Deletion time  包括找到删除项、更新索引结构的时间
- Space overhead  索引结构所占据的额外空间

## Ordered Indices

### Primary Index | 主索引  ||   Clustering index | 聚集索引

In a sequentially ordered file, the index whose search key specifies the sequential order of the file.

#### Dense Index | 稠密索引

> 可以是聚集或者非聚集



![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405151930600.png)

![image-20240515193225065](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405151932138.png)

- 左侧的部分都是`index entry`，包括一个索引键值和指针
- 它的`pointer`有三种情况（索引是否是`key`）
  - 直接指向对应search key的记录
  - 指向所有具有相同search key的指针，相当于是上图中的指针指向一个bucket，这个bucket含有所有指向相应记录的指针
  - 指向所有具有相同search key的第一条记录的指针，如上图

#### Sparse Index | 稀疏索引

> 必须是聚集索引，按顺序存放

Contains index records for only **some** search-key values.

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405142128126.png)

### Secondary Index | Non clustering Index

> 文件的索引跟物理存储顺序不一致

![image-20240515195153676](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405151951742.png)

- `index entry `**Index record points to a bucket that contains pointers to all the actual records with that particular search-key value.**
- 必须是稠密索引

### Multi Level index

- outer index – a sparse index of the basic index
- inner index – the basic index file

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405142130660.png" alt="image-20240514213005631" style="zoom:50%;" />

### Others

**Composite search key**

## B+ Tree Index

> **Paths: **all leaf in same level
>
> **Root: ** 
>
> - **non-Leaf.**  has at least 2 children.
> - **Leaf.**  If the root is a leaf (that is, there are no other nodes in the tree), it can have between 0 and (n–1) values.
>
> **Inner node: **Each node that is not a root or a leaf has between $\lceil n/2\rceil$ and n children.
>
> **Leaf: **A leaf node has between $\lceil (n–1)/2\rceil$and n–1 values

![image-20240515202419289](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152024377.png)

总体结构都是上面的

**Leaf Node**

$P_i指向记录,P_n指向下一个叶子$

**Non Leaf Node**

$P_i都指向它的Children$

!!! info "trick"
	Block_id entry
	Block_id + 绝对偏移的表示方法并不利于位置的记录
    

**支持查询方式** Point Query 和 Range Query 和 Scanning

因为叶子节点含有指向兄弟的指针；可能含有一个Scanning pointer，指向第一个Leaf

![image-20240515213816926](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152138001.png)

### Query

每一个节点都对应一个磁盘的块 block, 把这一块读入内存，之后可以获得这个节点.
**A node is generally the same size as  a disk block, typically 4 kilobytes**

!!! info "info"
	在DB中的B+ Tree下，inner node的值不一定在leaf出现。**（这种情况是在Deletion下发生）**

### Insert / Delete

![image-20240515205343897](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152053994.png)

**Deletion**

![image-20240515205542056](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152055165.png)

![image-20240515205604830](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152056927.png)

![image-20240515205649092](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152056194.png)

- Gold删除后仍然在root的索引中

### 计算

**height & size 估计**

`height`
$$
\\
最大高度：(不考虑根的"二叉"，只需要考虑每一层最少有多少个value)\\
\\
Height\leq \lceil log_{\lceil \frac{n}{2}\rceil}K \rceil
$$
![image-20240515210106622](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152101728.png)

- **Records per block**
  每一个node是一个块，一个块一般是4K大小(Block Size)，Block Size / Data Size
  **Blocks for storing**
  Records size / Records per block

- 要计算`fan-out`，也就是这个B+ Tree的分支，对于一个M叉的B+ Tree，它有 M+1 个指针，M个索引值。
  于是，计算方式就是  ($\frac{Block Size - 4}{index\ size+\ pointer\ size}$ +1 )

- **层数**

  > 根节点的level为1

  - Level 2 ：min = 2 * leaf value , max = 全满
  - Level 3 ：min = 2 * Inner value * leaf value
  - Level K(K > 1) :

  $$
  min = 2\ *\ (Inner\ Pointer)_{min}^{K-2}*(Leaf\ value)_{min}\\
  max = (Inner\ Pointer)_{max}^{K-1}*(Leaf\ value)_{max}
  $$

  

![image-20240515212708347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152127430.png)

`size`

- leaf的部分，要存放1000000个(N)数据，那么需要N / leaf values个叶子节点

- **最少的nodes**
  leaf : 1000000 / 186
- **最多的nodes**





###  Extension

#### 文件索引

![image-20240515214118641](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152141725.png)

- 存放的是记录本身而不是指向记录的指针

#### 辅助索引

> 在改变索引的时候，即使没有直接作用于这条记录，但他的索引也可能发生变化，这导致维护的代价相当高

Solution: **use search key of B+-tree file organization instead of record pointer in secondary index**

- Add record-id if B+-tree file organization search key is non-unique
- Extra traversal of file organization to locate record
  - Higher cost for queries, but node splits are cheap

#### 字符串

使用 **前缀压缩 | prefix encoding** 来对变长的数据进行索引

![image-20240515214556953](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152145013.png)

#### 批量加载与构建 | Bulk Loading and Bottom-Up Build

**Algorithm 1**

- sort entries first
- insert in sorted order
  - much improved I/O performance, **but most leaf nodes half full**

**Algorithm 2 | Bottom-up B+-tree construction**

- sort entries
- create tree layer-by-layer, starting with leaf level

## Hash | 散列

> A **bucket** is a unit of storage **containing one or more entries** (a bucketis typically a disk block).
>
> - we obtain the bucket of an entry from its search-key value using a hash function
>
> **Hash function** h is a function from the set of all search-key values K to the set of all bucket addresses B.
>
> ![image-20240515220143439](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152201477.png)

### Static hashing

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152206385.png" alt="image-20240515220655295" style="zoom: 33%;" />

**Bucket Overflow**

使用 **overflow bucket** 处理，形成溢出链

### Dynamic Hashing

- Periodic rehashing
- Linear Hashing
- Extendable Hashing

![image-20240515221211607](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152212691.png)

## Multiple-key access

> Use multiple indices for certain types of queries
>
> ![image-20240515215306274](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152153340.png)

```SQL
select ID
from instructor
where dept_name = “Finance” and salary = 80000
```

![image-20240515215434761](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152154832.png)

## Definition of Index

```sql
create index takes_pk on takes (ID,course_ID, year, semester, section) 
drop index takes_pk
```

- Indices on primary key created automatically by all databases

## Write-Optimized Indices

> Performance of B+-trees can be poor for **write-intensive workloads**
>
> - One I/O per leaf, assuming all internal nodes are in memory
> - With magnetic disks, < 100 inserts per second per disk
>
> - With flash memory, one page overwrite per insert
> 
> 闪存的update代价比较大

### Log Structured Merge (LSM) Tree

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152219300.png" alt="image-20240515221952236" style="zoom:33%;" />

- Size threshold for $𝐿_{𝑖+1}$ tree is 𝑘 times size threshold for $𝐿_𝑖$ tree
一个record在一个节点最多写K次

**插入**
- Records inserted first into in-memory tree (𝐿0 tree)
- When in-memory tree is full, records moved to disk (𝐿1 tree)
  B+-tree constructed using *bottom-up build* by merging existing 𝐿1 tree with records from 𝐿0 tree
  内存里的 B+ 树如果满了，就马上写到磁盘里去（可以连续写）
- When 𝐿1 tree exceeds some threshold, merge into $L_2$ tree
  And so on for more levels
  

这样我们把随机写变为了顺序写。但此时查找一个索引，就要遍历所有 B + Tree

**Stepped-merge index**

在每一级使用更多的B+ Tree 而不是像上面一样每次一棵树满就去merge到下一层

- Variant of LSM tree with multiple trees at each level
- Reduces write cost compared to LSM tree
- But queries are even more expensive
  - Bloom filters to avoid lookups in most trees

![image-20240515222158190](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152221255.png)

**删除操作**

不同于上面的查找和insert，删除通过`deletion entry`来实现
>Indicates which index entry is to be deleted. The process of inserting a deletion entry is identical to the process of insertinga normal index entry.

- When trees are merged, if we find a delete entry matching an originalentry, both are dropped.
- When lookups, find both original entry and the delete entry, and mustreturn only those entries that do not have matching delete entry

### Buffer Tree




## Bitmap Indices

> Bitmap indices are a special type of index designed for **efficient querying on multiple keys**
> not particularly useful for single attribute queries
>
> - **Applicable on attributes that take on a relatively small number of distinct values**
>   每一列不同的属性值不要太多

![image-20240515222525776](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152225849.png)

- 可以进行交并操作

![image-20240515222632062](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405152226132.png)

```

```









