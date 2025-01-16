---
tags:
  - class/CA
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# CA

[TOC]

>[!note]
>
> - [天外飞仙 - 知乎](https://www.zhihu.com/people/njugao-53/posts?page=1)
>
> - 期末各部分占比
>
>![b721faff8797ba5a5fe00d857c50c667](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412250951434.jpg)
>
> - **Ch1**
> 	- Great Ideas
> 	- CPU Performance
> 	- Amdahl`s law
> - **Ch 2 Memory**
> 	- *Memory Hierarchy*
> 	- ==Cache==
>![image-20241226163752072](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261637352.png)
> 		- 计算
> 		- Improve AMAT
> 		- TLB
> 		- virtual memory
> - **Ch 3 ILP**
> 	- Dependences
> 		- Data Dependence
> 		- Name Dependence
> 			- Anti-dependence
> 			- output-denpendence
> 		- Control Dependence
> 	- Hazzards
> 	- Dynamic scheduling
> 		- ScoreBoard 更慢，需要等待WAW
> 		- Tomosulo
> 		- With ROB version
> 	- ![image-20241226164459759](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261645010.png)
> - CH 5
> 	- DLP TLP
> 	- ==SIMD==
> 		- ==vector处理机==
> 			- 如何做向量的链接 link technology 和计算
> 			- 
> 	- Flynn
> 	- Loop-Level Parallellism
> 		- 跨迭代的相关不能做link  todo:togo:
> 	- MIMD
>![image-20241226165214993](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261652150.png)
> 		- Flynn中的范围
>![image-20241226165300749](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261653991.png)
> 			- NUMA
> 			- UMA
> 		- Cache cohenrence
> 			- protocol 状态转换会给
> 				- 

## Overview

![image-20241220153031094](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201530227.png)

![image-20241220153358951](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201533012.png)

![image-20241220153412906](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201534967.png)

>![image-20241220154908280](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201549361.png)
>
>![image-20241220154916902](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201549986.png)

![image-20250101185135167](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011851325.png)

## Pipelining

- `Latency`---the number of intervening cycles between an instruction that produces a result and an instruction that uses the result.
- `Initiation interval`---the number of cycles that must elapse between instructions issue to the same unit. 
	- For full pipelined units, initiation interval is 1. 
	- For unpipelined units, initiation interval is always the latency plus 1.

![image-20241230092851234](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412300928358.png)

![image-20241230103306361](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301033498.png)

### 控制竞争

最原始的版本

![image-20241229234740924](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412292347149.png)

提前到ID判断

![image-20241229234906136](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412292349287.png)

![image-20241230091827467](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412300918665.png)

![image-20241230092745703](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412300927851.png)

## Cache

- AMAT
	- 多级cache
	- miss rate
	- 

![image-20241022153457116](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221534291.png)

### 计算

![image-20241230111630790](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301116985.png)

- miss
	- instruction miss
	- data miss

### Miss Penalty Reduction

#### 多级缓存

#### Critical Word First

这是一个优化内存读取性能的技术。当 CPU 从内存中读取一个块（通常是一个缓存行）时，如果发生了缓存未命中（cache miss），而且 CPU 需要的只是这个块中的某个特定字，传统方法会从内存中将整个块依次读取到缓存中，然后再提供给 CPU。

“Critical Word First” 的策略是优先传输 CPU 当前所需要的那个字（critical word），而不是等待整个缓存行被传输完毕。这使得 CPU 可以尽快继续处理，而无需等待整个块加载完毕。这样可以减少缓存未命中带来的等待时间，提高系统的响应速度。

#### Early Restart

**例子**

假设某个缓存行由 16 个字组成（比如从 `0x1000` 到 `0x103F`），CPU 请求的字是 `0x1004`。在“Early Restart”下：

- 当内存控制器从内存开始加载这个缓存行时，一旦 `0x1000` 到 `0x1004` 的部分数据被加载到缓存，内存控制器就立即将这些已加载的数据交给 CPU。

#### Giving Priority to Read Misses over Writes

- If a system has a write buffer, writes can be delayed to come after reads. 
- The system must, however, be careful to check the write buffer to see if the value being read is about to be written. 

在缓存系统中，缓存需要处理读操作和写操作。当发生缓存未命中时，读操作（read miss）意味着 CPU 需要的数据当前不在缓存中，而写操作（write）则是将 CPU 产生的数据写入缓存或内存。在这两者发生冲突时，优先处理哪一种操作会影响系统的性能。

“Giving Priority to Read Misses over Writes” 是一种策略，即当系统检测到读未命中和写操作同时发生时，它会优先处理读未命中。原因是读操作通常对 CPU 的性能有更大影响，因为 CPU 需要读取数据来执行指令。如果读操作被延迟，CPU 就必须等待，而写操作一般可以稍后再执行。

**例子**

假设一个系统正在执行以下操作：

- CPU 请求从内存中读取一个数据，但该数据不在缓存中（读未命中）。
- 同时，缓存中还有一些待写入内存的数据（写操作）。

在这种情况下：

- 系统会优先处理读操作，尽快将读请求的数据从内存加载到缓存中，这样 CPU 就可以继续执行。
- 写操作被延迟，等到读操作完成后再处理。这种做法的目的是减少读操作的延迟，避免 CPU 停滞，提高系统性能。

#### Merging write Buffer

**基本思想**:

- 检查写缓冲区中是否已经存在与当前写入地址相同的条目。
- 如果找到匹配的条目，则将新数据合并到该条目中，而不是创建一个新的缓冲区条目。
- 合并可以是字级别或更高粒度（如多字写入）。

**优化效果**:

1. 减少写缓冲区中的条目数量，提高缓冲区的利用率。
2. 降低内存带宽需求，因为多次写入同一地址可以合并成一次写入。
3. 减少处理器因写缓冲区满而引发的停顿（stall）。

#### Victim Cache

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301438252.png" alt="image-20241230143853111" style="zoom:50%;" />

被替换的块先不马上踢掉，先去victim寻找

### Reduce miss rate

![image-20241230144020011](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301440228.png)

#### Larger Block Size

![image-20241230144426802](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301444019.png)

减少冷启动

#### Cache Size

增大

- hit time 增加
- cost增加

#### Higher Associativity

- higher associativity decreasing Conflict misses
- Complier Optimization
	- Loop
	- Matrix
	- Loop Fusion
	- Merging Array

#### Way Prediction and Pseudo-Associative Cache

- **Way Prediction** 通过增加预测位来预测下一次访问的缓存路径（way）。
- 在 **组相联缓存** 中，每次访问需要比较多个路径的数据标签，而 **Way Prediction** 通过预测位直接猜测数据可能存在的路径，大大减少了比较的次数。

**伪关联**

- **Pseudo-Associative Cache** 是一种优化直接映射缓存的技术，类似于将直接映射缓存扩展为两路组相联缓存。
- 通过检查优先路径的缓存行，如果未命中，再尝试备用路径，从而减少冲突未命中。

缺点：

**伪命中的延迟**：

- 如果数据存在于另一个分区（半缓存 B），访问需要额外的 1-2 个周期延迟。

**CPU流水线复杂性**：

- 缓存访问时间不再固定为 1 个周期，可能是 1 个周期（快速命中）或 2-3 个周期（伪命中）。
- 流水线设计变得困难，需要处理可变延迟。

**更适合 L2 缓存**：

- 由于 L2 缓存通常不直接绑定到处理器，因此可以接受稍高的访问延迟。
- 不适合对时延敏感的 L1 缓存。

#### Compiler Optimizations

- Instructions
	- 指令重排序
	- Profiling to look at conflicts(using tools they developed)
- Data
	- Merging Arrays: improve spatial locality by single array of compound elements vs. 2 arrays
		对于有关系的两个数组，比如一个val 和 key可以放到同一个struct中，相邻存储
	- Loop Interchange: change nesting of loops to access data in order stored in memory
	- **Loop Fusion**: Combine 2 independent loops that have same looping and some variables overlap
		把不同的循环块融合起来
	- Blocking: Improve temporal locality by accessing “blocks” of data repeatedly vs. going down whole columns or rows

### Reduce the miss penalty and miss rate via parallelism

- Nonblocking Caches
	- 碰到 cache miss 不阻塞等待处理
	- The cache to continues to supply hits while processing read misses ( **hit under miss , hit under multiple miss** ). 
	
	- **Hit Under Miss**：在处理缓存未命中时，如果发生了另一个缓存命中，缓存可以继续服务新的命中请求。
	
		**Hit Under Multiple Miss**：在处理多个缓存未命中的情况下，仍然可以服务命中请求。
	
		**Miss Under Miss**：允许多个未命中请求并行进行，即处理第一个未命中时，可以同时处理其他未命中。
	
- Hardware Prefetching of Instructions and data
	- **reduces compulsory misses** 
	- 

- Compiler-controlled prefetch
  
  - The compiler inserts prefetch instructions to request the data before they are needed 
  - Binding prefetch
  - Non-Binding prefetch
  

​			

### Reduce the time to hit in the cache. 

- **Small and Simple Caches** 使用小而简单的cache
	- Direct-mapped is faster than set associative for both reads and writes. 
	- Fitting the cache on the chip with the CPU is also very important for fast access times. 
- **Avoiding Address Translation during Indexing of the Cache**
	- 物理缓存 cache存放虚拟地址
	- 虚拟缓存
- **pipelined Cache Access**
	- 对缓存的访问流水化
	- 流水化缓存写入允许在**当前写操作进行标签检查**的同时，完成**上一个写操作的数据写入**。
	- 减少了缓存写操作的整体延迟。

**Trace Cache**

- 用于存储指令执行的动态轨迹，而不是静态的顺序指令。这种设计可以更高效地利用指令缓存，尤其是在分支预测准确的情况下，能够显著减少分支跳转带来的性能损失。
- 如果下次访问相同的分支预测路径，可以直接从缓存中获取整个轨迹，无需逐条取指。

## Memory

- bandwidth
- 虚拟内存访问
- 

organizing memory to improve bandwidth

- Main memory is usually made from DRAM while caches use SRAM.

### Improving Performance

- 和传输的lantency / miss penalty 相关的数据
	- `Block size` 一次要取出一个block size
	- `Memory bus width` 取出一个block size 大小的块需要按照什么样的总线宽度传输上去
	- 方式
		- `wider` -> 影响 Block Size 要传多少次
		- `interleaved`  送地址的时间 + access time per word + 通过 bus 传输的时间

#### Wider Main Memory

![image-20241230165630695](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301656869.png)

#### simple Interleaved Memory

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410291411064.png" alt="image-20241029141107912" style="zoom:33%;" />

![image-20241230165654877](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301656039.png)

#### Independent Memory Banks

### Memory Tech

- Access time ----- time between when a read is requested and when the desired word arrives
- Cycle time ----- minimum time between requests to memory. One reason that cycle time is greater than access time is that the memory needs the address lines to be stable between accesses.

[内存基础 - HobbitQia的笔记本](https://note.hobbitqia.cc/Logic/logic07/#ram)

![image-20250101131112789](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011311048.png)

![image-20250101130236905](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011302170.png)

![image-20250101131033310](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011310543.png)

![image-20250101131041712](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011310885.png)

![image-20250101140227264](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011402510.png)

## ILP

- True dependence - RAW
- Output dependence - WAW
	- Name dependence
- anti-dependence - WAR
	- Name dependence

==数据依赖==

**指示潜在冒险可能性**：程序中指令的依赖性直接决定了可能会发生的冲突。

**决定结果计算顺序**：依赖性确保指令按照正确的顺序执行。例如，必须先完成加法，才能进行基于加法结果的减法。

**限制可利用的并行性**：如果数据依赖性太强，则指令之间的并行性较低，硬件优化效果受限。

==ILP==

- HW/SW must preserve program order
	- Control Dependence 不一定需要被严格保留
	- 但必须保证：
		1. 异常行为（Exception Behavior）
			- 指令执行顺序的改变不能引入新的异常
			- 例如：提前执行可能触发非法操作的指令是不可接受的
		2. 数据流正确性（Data Flow Correctness）
			- 指令产生的数据必须正确，不能因依赖关系的破坏而影响结果

### loop unrolling

>[!example]
>![image-20241220161023355](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201610441.png)![image-20241220162056484](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201620561.png) 

### Dynamic Scheduling 

- 乱序执行和完成
- Enables out-of-order execution and allows out-of-order completion
- in-order issue
- 原来的ID变为两个阶段
	**Issue（发射）**：这一阶段负责解码指令并检查**结构性危害**。如果硬件资源足够并且没有资源冲突，指令可以继续进入下一个阶段。

	**例子**： 假设有一条指令要求访问浮点单元，而同时其他指令也想访问这个单元。如果此时没有足够的硬件资源处理两条指令，就会发生结构性危害，导致其中一条指令被暂停。

	**Read Operands（读取操作数）**：这一阶段等待指令的操作数准备好，直到没有数据依赖关系（即没有数据危害）。一旦数据可用，就会读取寄存器或内存中的操作数。

	**例子**： 在上一段代码的例子中，`SUB R4, R1, R5` 指令依赖于 `ADD R1, R2, R3` 指令中的 R1。在读取操作数阶段，处理器将等待直到 R1 的值从前一条指令中更新，并准备好供下一条指令使用。

#### Score Board

- [【计算机体系结构】记分牌ScoreBoard - 知乎](https://zhuanlan.zhihu.com/p/496078836)
- 按序发射
- 乱序完成

![image-20241220164313472](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201643574.png)

- **Issue 阶段**：通过检查功能单元的可用性和避免WAW危害，确保指令能顺利发射。
- **Read Operands 阶段**：通过延迟操作数的读取直到操作数准备好，解决RAW危害。
- **Execution 阶段**：执行指令并通知记分板释放资源。
- **Write Back 阶段**：确保没有WAR危害，通过检查写回寄存器的依赖关系来避免错误。

![image-20241220165018172](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201650595.png)

ScoreBoard的重点在于三个表，以及各个阶段的进入条件

1. Instruction Status 指令处于哪个阶段
2. Functional Unit Status - Ri Rk 
3. Register result Status 要写入的寄存器是否被占用以及被哪一个占用 

**各个阶段**

1. IS: 解决结构冲突和WAW
	1. 指令对应的功能部件空闲，且指令要写的目标寄存器没有别的指令将要写
2. RO
	1. 指令对应的源寄存器能否获取到相应的值，要求现在检测到的 Rj Rk 为 yes(准备就绪但还没有读取)
3. EX  不需要考虑其他事情
4. WB 
	1. 防止WAR发生
	2. 检测**写操作的目的寄存器和前面指令的源寄存器**关系，如果该目的寄存器Di 和 前面某个源寄存器 Si相同，且Si对应的Ri值为Yes（准备就绪但还未读取）需要等待其读取之后再写回
	3. 写回之前记得看一下前面是否存在读的还没完成的

#### Tomasulo

![image-20241220174812781](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201748872.png)

通过**公共数据总线（Common Data Bus, CDB）广播到所有的功能单元。这种设计允许功能单元之间进行直接的结果转发**，从而避免了传统寄存器访问的瓶颈。

- **从预留站到功能单元**：操作数来自于预留站，而不是寄存器，这样可以减少寄存器访问的冲突。
- **CDB的作用**：CDB将指令的执行结果广播到系统中的所有功能单元。通过这种方式，如果其他指令需要这些结果，它们可以立即从CDB接收，而无需访问寄存器文件。这样可以减少指令之间的延迟，并提高执行效率。

![image-20241220185736687](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412201857822.png)

- 等到`Write`的时候（完成`Write`的下一个周期依赖的指令才能够运行）才会广播而不是计算完的下一个周期
- 如何处理Loop的情况
	- :book: ​TODO 

### 投机 | speculation

![image-20241221200425393](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412212004490.png)

- 按序提交，通过 ROB（Reorder Buffer）进行排队
	- 增加一个`Commit`阶段
- 对于RAW的等待，不是必须等到Commit才能使用，只要前一条指令完成了WB，下一条指令就可以使用对应的寄存器值
	- `CDB`将oprand传给`ROB`
- Register renaming is done **via reorder buffer** instead of reservation station

![image-20241221195750365](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211957579.png)

- Issue—get instruction from FP Op Queue
	- If reservation station and **reorder buffer slot free**, issue instr & send operands & reorder buffer no. for destination (this stage sometimes called “dispatch”) , update control entries “in use”.发射时，操作数和目标的重排序缓冲区编号被发送，并更新控制条目的“使用中”状态。
- Execution—如果两个操作数都准备好了，开始执行。如果没有准备好，指令将等待公共数据总线（CDB）传送的结果。执行过程涉及检测RAW（读后写）数据依赖。
- Write result — 执行完成后，结果通过CDB广播到所有等待的功能单元（FUs）和重排序缓冲区，并标记相应的保留站为可用。
- Commit — 当指令在重排序缓冲区的头部且结果已准备好时，将结果写入寄存器或内存，并从重排序缓冲区移除该指令。若发生分支预测错误，则会刷新重排序缓冲区，通常称为“毕业”（graduation）。

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211931355.png)

当一个 **Load (LD)** 指令紧跟在一个 **Store (ST)** 指令之后时，需要判断两者是否相关，即是否存在 **存储器引发的 RAW hazard**。以下是详细的解释：

------

**例子：**

```riscv
ST  0(R2), R5
LD  R6, 0(R3)
```

**1. 是否存在相关性 (RAW Hazard)?**

- 如果 `0(R2)` 与 `0(R3)` 的地址相同，则 Load 指令可能会读取 Store 指令尚未写入的值，存在 RAW hazard。
- 如果地址不同，则两者无数据相关性，Load 可直接开始。

**2. 是否可以提前开始 Load?**

- Load 指令的执行依赖于以下条件：
	- Store 的地址是否已计算完成。
	- 如果 Store 的地址与 Load 地址不同，Load 可提前执行。
	- 如果 Store 地址未计算完成（例如 R2 由一个复杂操作如除法决定），需等待地址计算完成后再检查地址冲突。

### Dynamic Hardware Prediction

- [知乎文章](https://zhuanlan.zhihu.com/p/490749315)

>[!note]
>
> - Taken
> 	- 不会执行if，不符合条件
> - Not Taken
> 	- 将继续执行if

**下面是两位预测的两种cases**

![image-20241220235311896](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412202353035.png)

![image-20241221183644441](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211836572.png)

#### Correlating predictor

- (2,2) predictor: 2-bit global, 2-bit local
	- **Global** 相当于一个移位寄存器，用于索引
	- **Local** 记录当前分支的状态，就是上面的类型

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211903809.png" alt="image-20241221190302728" style="zoom:50%;" />

![image-20241221190713104](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211907238.png)

- 根据当前的global确定要找的分支，根据分支看预测值是否正确，如果真实值为0则指向的分支-1真实值为1则+1
	![image-20241221192353388](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412211923491.png)

- 一个有4k项的(2, 2)相关预测器，其所有预测位所占的总空间为 32k 比特
- ![image-20250101163259294](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011632484.png)

### Superscalar / VLIW

![image-20241221201848303](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412212018475.png)

#### Superscalar | 超标量

- n-issue 多核实现多流出
	- 额外的硬件
	- 性能提升n倍
- 用到的部件不同，比如`EX`

multi-issue

1. `beq`之类的跳转是单发射的

- Static scheduling
	- 指令按序发射
- Dynamic scheduling
	- Pipeline: Run this step in half a clock cycle, so that two instructions can be processed in one clock cycle.
	- Widen issue logic: Build the logic necessary to handle two instructions at once, including any possible dependences between the instructions.

#### VLIW | 超长指令字

- 一般是在`EX`段，拆分成不同的功能使用不同的部件
- 编译器很重要

 ![image-20241221201025665](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412212010817.png)

## DLP and TLP

- **Data level parallelism**
	- Vector Processor
	- GPU
- **Thread level Parallelism**
	- SMP/DSM
	- Cache coherence
	- Synchronization

![image-20241223165649566](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412231656725.png)

![image-20241226221243616](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412262212797.png)

- UMA（统一内存架构）：所有处理器共享一个统一的内存空间，访问内存的延迟相对较低。理想情况下，所有处理器对内存的访问时间相同。
- NUMA（非统一内存架构）：每个处理器有自己本地的内存区域，但可以访问其他处理器的内存。访问本地内存时，延迟较低；访问远程内存时，延迟较高。
	- DSM：在DSM中，地址空间由多个私有的（独立的）地址空间组成。每个计算机（节点）都有自己的本地地址空间，处理器不能直接访问其他节点的内存，而是通过网络进行通信。
	- 

### Multithreading

![image-20241225192015858](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251920972.png)

![image-20241225192148568](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251921658.png)

- 

### DLP

#### Vector

> **Vector Processors : **
>
> 1. hardware does not have to check for data hazards 
>   1. 由编译器直接完成了指令的优化
> 2. Each result independent of previous result 向量之间没有关系
> 	1. high clock rate
> 	2. 编译器保证了没有数据依赖，不需要硬件检查data hazard
> 3. Vector instructions that access memory have a known access pattern. 知道内存访问的方式，可以直接预取
> 	1. highly interleaved memory
> 	2. 将访问 memory 的时间均摊到N个元素上面
> 	3. 甚至不需要data cache
>
> **缺点**
>
> - Start up time

#### 分类

![image-20241223171918302](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412231719419.png)

**向量内存-内存架构（VMMA）**

- 特点：

	所有向量操作（如加法、乘法等）都直接在主存中进行，操作数从内存中加载，结果写回内存。

	- 操作：加载内存→执行运算→存储回内存加载内存
	- 内存带宽要求更高：require **greater main memory bandwidth**
	- overlap更难，要在内存地址上做依赖的检查：**Must check dependencies on memory addresses**
	- 更大的startup latency

**向量寄存器架构（Vector Register Architecture, VRA）**

- 特点：

	向量操作仅在向量寄存器中完成，只有加载（load）和存储（store）操作才会与主存交互。

	- 操作：从内存加载到寄存器→在寄存器中运算→将结果存回内存从内存加载到寄存器 

#### Cray-1

![image-20241225194435354](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251944451.png)

- No Data Caches
- No Virtual Memory
- Vector Registers

Vector Optimization

1. Vector chaining 前递
	![image-20241225195555668](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251955779.png)
2. Mask Vector
	根据Mask值决定取哪些
3. 稀疏矩阵

#### SIMD

- No mask registers
- 

#### GPU

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412252014216.png" alt="image-20241225201407088" style="zoom:50%;" />

- **CPU is the host, GPU is the device（CPU 是主机，GPU 是设备）**
- **CUDA 线程** 是 CUDA 中的基本执行单元。每个线程执行相同的代码，但处理不同的数据。通过对线程的合理调度，可以充分利用 GPU 的并行计算能力。
- CUDA 使用的编程模型是 **SIMT（Single Instruction, Multiple Thread）**，即 **单指令多线程**
	- 在这个模型中，所有线程执行相同的指令，但它们处理不同的数据。换句话说，所有线程并行执行同一段代码（单指令），但每个线程处理的数据是不同的。

**Thread and block**

- **A thread is associated with each data element** 线程的数量和数据的数量是直接相关
- **线程块（Thread Block）** 是 CUDA 程序中的一个重要概念。一个线程块是由多个线程组成的。每个线程块内部的线程可以相互通信和共享数据。线程块是 CUDA 并行计算中的基本执行单元。
	- 线程块内部的线程是可以并行执行的，但不同线程块之间的线程不能直接通信
- **Grid：**线程块不仅是组织线程的单位，多个线程块可以被组织成一个 **网格（Grid）**。一个网格由多个线程块组成，网格可以是二维的或三维的，具体取决于任务的需求。
- **线程管理由硬件处理**：GPU 硬件负责管理线程的调度、同步和资源分配，应用程序和操作系统无需介入 GPU 内部的线程管理

**和vector machine的不同**

- **使用多线程来隐藏内存延迟**，而vector使用chain
- 没有标量处理器

**相同**

- 

如果有循环依赖，迭代之间的执行顺序就变得重要，从而限制了并行化的可能性。

![image-20241225203346092](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412252033192.png)

![image-20250101173756525](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501011737681.png)

### TLP

#### Coherence

- Simple write-invalidate protocol
- Snooping Protocol
	- 不同的策略
		1. ==write invalidate==
			![image-20241224135529843](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412241355965.png)
			1. **Write to shared data:**  an invalidate is sent to all caches which snoop and invalidate any copies 广播一个信号
			2. **Read Miss**: 这种情况发生 Read miss
				1. **Write-through**: memory is always up-to-date
				2. **Write-back:** snoop in caches to find most recent copy
		2. ==broadcast update==
			1. 

- Directory-Based Schemes
	- Scales better than Snooping
	
	- 在这种没有总线且不广播的系统中，通常涉及到以下几个术语：
	
		**2.1. Local Node（本地节点）**
	
		- **定义**：本地节点是指==发起请求==的处理器所在的节点。也就是当处理器需要访问某个内存位置时，发起请求的节点即为本地节点。
		- **角色**：本地节点需要向其他节点请求数据，或者响应其他节点的请求。
	
		**2.2. Home Node（主节点）**
	
		- **定义**：主节点是指==存储特定内存地址==的数据所在的节点。每个内存位置都有一个与之对应的主节点，负责管理该内存块的存取请求。
		- **角色**：主节点处理访问该内存块的请求，决定是否将数据提供给本地节点，或是否更新数据的状态。
	
		**2.3. Remote Node（远程节点）**
	
		- **定义**：远程节点是指==某个内存块的副本==存在的节点。该节点可能缓存了内存块的一个副本，并且该副本可能是**独占的（Exclusive或共享的（Shared）**。
		- **角色**：当本地节点请求内存块时，如果远程节点拥有该块的副本，远程节点可能需要与本地节点进行数据同步。

#### Syncronization

## hw 待看

![image-20241226165645609](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261656766.png)

![image-20241226165654272](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261656446.png)

![image-20241226165700223](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261657410.png)

![image-20241226165704506](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261657714.png)

![image-20241226165714379](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261657549.png)

![image-20241226165719784](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261657973.png)

![image-20241226165724261](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412261657439.png)
