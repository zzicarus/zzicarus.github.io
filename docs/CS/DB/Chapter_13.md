# Data Storage Structures

## File Organization

> Magnetic disks as well as SSDs are **block structured devices**, that is, **data are read or written in units of a block(数据传输和存储分配的基本单元，通常是4-8KB)**. In contrast, databases deal with **records**, which are usually **much smaller than a block** (although in some cases records may have attributes that are very large).

- The database is stored as **a collection of files**. 
- Each file is a **sequence of records**. 
- A record is a **sequence of fields.**

### Fixed Length Records

![image-20240509190603413](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091906520.png)

### Variable Length

**要解决的问题**

- 如何表示一个变长的属性？并且能够轻易地获取？
- 如何在Block中存储变长的record？

![image-20240509192415843](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091924926.png)

**Slotted page （分槽页）**

![image-20240509192903431](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091929510.png)

## Organization of Records in Files

![image-20240509193235079](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091932166.png)

### Heap

- Records usually **do not move once allocated**
- Important to be able to efficiently find free space within file

**Free-space map (自由空间图)**

![image-20240509193611151](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091936224.png)

### Sequential File Organization

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091816296.png" alt="image-20240509181640193" style="zoom:50%;" />

- **Deletion** Using the pointer
- **Insertion** locate the position where the record is to be inserted
- **Reorganize** 使之重新物理有序存储

### Multitable Clustering File Organization

- 对相同的信息聚类；把不同的关系放在同一个表中
- Results in variable size records
- Can add **pointer chains to link records** of a particular relation

![image-20240509182347022](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091823104.png)

把一个department的instructor聚集在一起

### Partitioning

![image-20240509182745847](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091827939.png)

## Data Dictionary Storage

- 有助于语义检查

![image-20240509183253687](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091832771.png)

![image-20240509183619704](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091836790.png)

## Buffer

- **Blocks** are units of both storage allocation and data transfer
- **Buffer (缓冲区)** – portion of main memory available to store copies of disk blocks，但是在磁盘上的拷贝可能旧于缓冲区的
- **Buffer manager (缓冲区管理器)** – subsystem responsible for allocating buffer space in main memory.

**流程**

![image-20240509194854556](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091948633.png)

- System Call
  - in the buffer
  - not in the buffer
    - buffer is full
      - The replaced block is updated -> write back to disk
      - not , deleted, and replaced
    - buffer is not full

**pinned Block**

- **Pin** done before reading/writing data from a block
- **Unpin** done when read /write is complete
- **Multiple concurrent** pin/unpin operations possible
- Keep a **pin count**, buffer block can be evicted only if pin count = 0

### 缓冲区策略

#### LRU

> 从buffer中去掉最近最少用到的

!!! example "example"
	![image-20240509184324109](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405091843159.png)

对于要“扔掉”的数据，要判断是否已经修改过（buffer中的数据可能是数据库中的数据修改后的数据）。

​	

??? example "Clock: An approximation of LRU"
	[介绍](https://www.geeksforgeeks.org/lru-approximation-second-chance-algorithm/)

## Column-Oriented Storage

