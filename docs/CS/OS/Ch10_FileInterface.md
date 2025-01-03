# File System

## Interface

- **File Concept**
	- Contiguous logical address space
	- 文件属性存储在`directory structure`(在disk中)
- **File Operations**
	- Create
	- Truncate  除了file len 其他属性都不变
	- Open/Close
		- ==Open-file table==
			- Per-process table
				- 当前的文件指针
				- 访问权限
			- System-wide table 存放一些进程无关的文件信息
				- Open count
					- how many processes have the file open
				- Disk Location
- **Access Methods**
	- Sequential-access 直线访问，否则reset
	-  direct/relative access
- ==**Directory Structure**==
	- 目录本质上是一个特殊的文件（Linux 中），把filename映射到FCB
	- 类别
		- 单级
		- 两级
		- Tree-Structured
		- ==Acyclic-Graph==
			- ==soft link==
			- ==hard link==
		- general-graph directories
- **File-System Mounting**
	- Mounting Point
- **File Sharing**
	- 
- **Protection**
	- 最普通的实现方法：为每个文件和目录关联一个访问控制列表 ACL

the operating system uses two levels of internal tables: a per-process table and a system-wide table.

![image-20241218104413422](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412181044535.png)

### link

硬链接是对一个已存在文件的引用，实际上，硬链接和原文件是等价的。它们共享相同的 inode（索引节点），也就是说，硬链接和原文件指向的是同一份数据。硬链接没有自己的文件内容，它只是原文件的一种新的访问路径。

特点：

- **共享 inode**：硬链接和原文件共享相同的 inode 节点，因此它们的文件内容是完全一样的。无论是通过原文件名还是硬链接名来访问，都指向相同的文件数据。
- **不能跨文件系统**：硬链接不能跨越不同的文件系统。如果原文件和硬链接位于不同的文件系统中，无法创建硬链接。
- **增加链接计数**：每个文件都有一个链接计数（link count），它表示指向该文件的硬链接数。每创建一个硬链接，链接计数会增加。链接计数为 0 时，文件才会被真正删除。
- **不能对目录创建**：为了避免文件系统中的循环结构，硬链接不能用于目录（除了超级用户特权下的某些特殊情况）。这也是避免文件系统中出现死循环的机制。
- **删除的影响**：当你删除硬链接或原文件时，文件的数据并不会立即被删除，只有当链接计数为 0 时，文件的数据才会被从磁盘中清除。

| 特性               | 硬链接                      | 软链接                                                 |
| ------------------ | --------------------------- | ------------------------------------------------------ |
| **指向目标的方式** | 指向相同的 inode            | 指向文件路径                                           |
| **共享 inode**     | 是                          | 否（具有自己的inode不过信息是linked file的）           |
| **跨文件系统**     | 否                          | 是                                                     |
| **指向目录**       | 否（通常）                  | 是                                                     |
| **删除后的行为**   | 只有链接计数为 0 时删除文件 | 删除软链接不会影响原文件，原文件删除时，软链接变为悬挂 |
| **创建文件类型**   | 文件名与 inode 相同         | 创建一个独立文件，包含目标路径                         |
| **文件大小**       | 与原文件大小相同            | 很小，仅存储路径                                       |

### mounting

- **挂载点（Mount Point）**：这是一个操作系统目录，它充当了访问外部存储设备的入口。挂载点是一个空目录，设备的文件系统将通过挂载操作与该目录相关联。例如，常见的挂载点包括 `/mnt`、`/media`、`/home` 等。
- **挂载操作（Mount）**：将存储设备（如硬盘、U盘）上的文件系统连接到操作系统的目录结构中的过程。挂载后，操作系统就能像访问本地文件一样访问外部存储设备中的文件。

```bash
# 挂载文件系统
mount /dev/sda1 /mnt
```

这里，`/dev/sda1` 是存储设备（例如硬盘）的设备文件，`/mnt` 是挂载点目录。执行此命令后，`/dev/sda1` 上的文件系统将通过 `/mnt` 路径访问。													

## Implementation

- **File-System Structure**
	- Logical storage unit
	- Collection of related information
	- ==**Data Structure**==
		- **Disk Structures**
			- Boot control block (per volume)引导控制块
			- Volume control block per volume (superblock in Unix) 卷控制块
			- Directory structure per file system 每个文件系统的目录结构，比如存储对应的文件名和inode的号码
			- Per-file FCB (inode in Unix)
		- **In-memory structures**
			- In-memory mount table  挂载表
			- Directory cache for recently accessed directories   目录的cache
			- System-wide open-file table
			- Per-process open-file table
- **层次结构**
	- **File organization 级别**
		- VFS
- File-System Implementation
	- 
- Directory Implementation
	- Linear
	- Hash Table
- ==**Allocation Methods** 需要计算！==
	- 连续(contiguous)
		- 变种： Extent-Based
	- 链接(linked)
		- No random access, poor reliability
		- 变种： FAT | File-Allocation Table 的使用
	- 索引(indexed)
		- 使用一个block作为`index block`
			- 如果一个太小，使用一个index block的链表==注意这个的计算，先确定在哪个index block中==
			- ==linked scheme==
			- ==n-level index==
- Free-Space Management 

	- Bit map bit[i] = 1，空闲
		- **Must be kept on disk**
		- The copy in memory and disk may differ
		- 为了比较好地维护这两份拷贝的同一
			- 先set disk中的bit[i]
			- deallocate memory
			- 最后set mem中的bit[i]

	- Linked List
	- Grouping

- Efficiency and Performance

	> ==The page cache== uses **virtual memory techniques** to cache file data as pages rather than as file-system-oriented blocks. Caching file data using virtual addresses is far more efficient than caching through physical disk blocks, as accesses interface with virtual memory rather than the file system

	- Without Unified Buffer
		![image-20241224153133508](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412241531645.png)
		- 要访问一个文件有两种形式，如果使用两个cache，在进行routine I/O 时需要将buffer cache的内容复制到page buffer，造成double buffer
			1. Memory-mapped
			2. 正常I/O

	- Unified Buffer


### 流程

![image-20241223225237076](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412232252244.png)

![image-20241223225619197](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412232256301.png)

![image-20241223225702936](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412232257042.png)

![image-20241223225717415](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412232257559.png)

