# Main Memory

>对应教材 Part 4 Memory Management

## BackGrounds

- Main memory and the registers built into each processing core are the only general-purpose storage that the CPU can access directly.
- A pair of **base** and limit **registers** define the **logical address space**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410231852458.png" alt="image-20241023185233268" style="zoom: 33%;" />

### Address Binding

>就是将不同的地址空间进行mapping

>[!note]不同类型的地址
>
> - Symbolic Address: Addresses in the source program are generally symbolic (such as the variable count). 符号地址 
>
> - Relocatable Addresses: A compiler typically binds these symbolic addresses to relocatable addresses (such as “14 bytes from the beginning of this module”).  像是一种local address之后可以转为global address
> - **Absolute Addresses**: The linker or loader binds the relocatable addresses to absolute addresses (such as 74014).

- **Compile time（编译时刻）**:  If memory location known a priori, absolute code can be generated; must recompile code if starting location changes
- **Load time（装入时刻）**:  Must generate relocatable code if memory location is not known at compile time
- **Execution time（执行时刻）**:  Binding delayed until run time if the process can be moved during its execution from one memory segment to another.  Need hardware support for address maps (e.g., base and limit registers)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410231859992.png" alt="image-20241023185946907" style="zoom:33%;" />

### Logical & Physical Address

- Logical and physical addresses are the same in compile-time and load-time address-binding schemes;
- Logical (virtual) and physical addresses differ in execution-time address-binding scheme

**MMU**

![image-20241023145150595](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410231451719.png)

### Dynamic Loading & Dynamic Linking

| 特性         | **Dynamic Loading (动态加载)**   | **Dynamic Linking (动态链接)**             |
| ------------ | -------------------------------- | ------------------------------------------ |
| **加载时间** | 在程序运行时按需加载，手动控制   | 在程序启动时自动加载                       |
| **使用场景** | 适合需要条件性加载的模块，如插件 | 适合常用的共享库，如操作系统的标准库       |
| **内存占用** | 占用较少内存，只有在需要时才加载 | 相对固定，占用内存更多                     |
| **更新库**   | 更新库时需要重新加载库           | 可以直接更新库，无需重新编译程序           |
| **代码大小** | 程序代码较小，库按需加载         | 程序代码较小，库共享，适合多个程序共享使用 |

|              | 无需OS帮助                       | 需要OS帮助                                 |

#### **动态加载的特点**

- 模块在程序运行时按需加载。
- 通常使用一些函数来手动加载模块（如 `dlopen` 在 Linux 中，`LoadLibrary` 在 Windows 中）。
- 适合加载一些只在特定条件下使用的功能模块，减少初始加载时间和内存占用。

#### **动态链接的特点**

**Dynamically linked libraries** (**DLLs**) are system libraries that are linked to user programs when the programs are run

- 共享库在程序运行时加载并链接。
- 程序与共享库的接口在编译时绑定，但具体的库代码在运行时加载。
- 常用于共享库（如 `.dll`、`.so` 文件），减少可执行文件的体积。
- 更新库版本时不需要重新编译整个程序，只需确保库接口不变。

## Contiguous Allocation

### Protection 

 dispatcher loads the relocation and limit registers with the correct values as part of the context switch

![image-20241023151937007](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410231519113.png)

### Allocation

按照动态分配

![	](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232248044.png)

- First-fit:  Allocate the first hole that is big enough
- Best-fit:  Allocate the smallest hole that is big enough; must search entire list, unless ordered by size  Produces the smallest leftover hole
- Worst-fit:  Allocate the largest hole; must also search entire list  Produces the largest leftover hole

### Fragmentation

**External **  holes

- **Compaction** is possible only if relocation is dynamic, and is done at execution time

**Internal** 有时会使用block size进行memory的分配，分配到的实际内存大小大于进程需要的内存大小

## Paging

- Divide **physical memory** into fixed-sized blocks called **frames** (size is power of 2, between 512 bytes and 8,192 bytes)
- Divide **logical memory** into blocks of same size called **pages**

### Page Table

- The page number is used as an index into a **per-process** **page table**
- 大小不一定
- PTE ：Page Table Entry

![image-20241025225510881](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410252255051.png)

### Hardware Support

- Page table is kept in main memory
	- 所以指令需要进行两次Memory访问，一次获得物理地址，一次获得Data/Instruction
- **Page-table base register (PTBR)** points to the page table
- **Page-table length register (PTLR)** indicates size of the page table

**TLB | associative memory**

- To be able to execute the search within a pipeline step, however, the TLB must be kept small. It is typically between 32 and 1,024 entries in size.
- 支持parallel search 
- **address-space identifiers (ASIDs) ** ： 在TLB中额外的信息，可以用来保护内存
	- 比如，记录读写权限。比如，对于下面提到的sharing page，需要依赖操作系统确保它是Read-only的

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410252323684.png" alt="image-20241025232355583" style="zoom: 25%;" />

- 一个进程很少使用它的所有地址

### Sharing Pages

- One copy of read-only (reentrant) code shared among processes (i.e., text editors, compilers, window systems).
- Shared code must appear in same location in the logical address space of all processes

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410252336791.png" alt="image-20241025233629706" style="zoom: 33%;" />

## Page Table

### Hierarchical Page Tables

- [操作系统中的多级分页 - GeeksforGeeks](https://www.geeksforgeeks.org/multilevel-paging-in-operating-system/)
- [How Do Multi-Level Page Tables Save Memory Space? | Baeldung on Computer Science](https://www.baeldung.com/cs/multi-level-page-tables)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410252348321.png" alt="image-20241025234849237" style="zoom: 33%;" />
